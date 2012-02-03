/////////////////////////////////////////////////////////
//	File Name : "CXboxInput.cpp"
//	Author Name : Wade Shwallon
//  Created On: 6-17-2011
//	Purpose : To contain the functionality of gamepad input
/////////////////////////////////////////////////////////


#include "CXboxInput.h"
#include <fstream>
using namespace std;
CXboxInput::CXboxInput(INT PlayerNum)
{
	m_xBufferState.Gamepad.wButtons = 0;
	m_xState.Gamepad.wButtons = 0;
	m_nPlayerNum = PlayerNum -1;
	m_sJoystickThresholdX = 16000;
	m_sJoystickThresholdY = 16000;
	m_bTriggerThreshold = 5;
	m_fInputDelayTriggers = 0.0f;
	m_fInputDelayJoysticks = 0.0f;
	m_fInputDelayButtons = 0.0f;
	m_fTimeTriggers = 0.0f;
	m_fTimeJoysticks = 0.0f;
	m_fTimeButtons = 0.0f;
	m_nMaxHistory = 3;
	m_nCurrentHistory = 0;
	m_nNumCombos = 2;
	m_nCurrNumCombos = 0;
	m_pxStatePrevious = new XINPUT_STATE[m_nMaxHistory];
	m_pxStateCombos = new XINPUT_STATE*[m_nNumCombos];
	for(int i = 0; i < m_nMaxHistory; i++)
	{
		m_pxStatePrevious[i].Gamepad.wButtons = 0; 
		m_pxStatePrevious[i].Gamepad.bLeftTrigger = 0;
		m_pxStatePrevious[i].Gamepad.bRightTrigger = 0;
		m_pxStatePrevious[i].Gamepad.sThumbLX = 0;
		m_pxStatePrevious[i].Gamepad.sThumbLY = 0;
		m_pxStatePrevious[i].Gamepad.sThumbRX = 0;
		m_pxStatePrevious[i].Gamepad.sThumbRY = 0;
	}
	XInputEnable(true);
}

void CXboxInput::ReadCombos(char* szFileName)
{
	ifstream in;
	in.open(szFileName,ios_base::in);

	if(in.is_open())
	{
		if(in.good())
		{
			in >> m_nNumCombos;
			in.ignore(INT_MAX,'\n');

			XINPUT_STATE* combo = new XINPUT_STATE[m_nNumCombos];
			for(int i = 0; i < m_nNumCombos; i++)
			{
				//XINPUT_STATE currcomb;
				//BYTE byteval;
				//SHORT shortval;

			}


		}
		
	}


	in.close();

}
void CXboxInput::InitPrevious(INT maxHistory)
{
	if(maxHistory <= MINMAXHISTORY || maxHistory > MAXMAXHISTORY)
		return;
	if(m_pxStatePrevious)
		delete[] m_pxStatePrevious;
	m_nMaxHistory = maxHistory;
	m_pxStatePrevious = new XINPUT_STATE[m_nMaxHistory];
	for(int i = 0; i < m_nMaxHistory; i++)
	{
		m_pxStatePrevious[i].Gamepad.wButtons = 0; 
		m_pxStatePrevious[i].Gamepad.bLeftTrigger = 0;
		m_pxStatePrevious[i].Gamepad.bRightTrigger = 0;
		m_pxStatePrevious[i].Gamepad.sThumbLX = 0;
		m_pxStatePrevious[i].Gamepad.sThumbLY = 0;
		m_pxStatePrevious[i].Gamepad.sThumbRX = 0;
		m_pxStatePrevious[i].Gamepad.sThumbRY = 0;
	}
}
void CXboxInput::InitCombo(INT size, XINPUT_STATE* combo)
{
	m_pxStateCombos[m_nCurrNumCombos] = new XINPUT_STATE[size];
	for(int i = 0; i < size; i++)
	{
		m_pxStateCombos[m_nCurrNumCombos][i] = combo[i];
	}
}

void CXboxInput::Update(float fElapsedTime)
{
	m_fTimeTriggers += fElapsedTime;
	m_fTimeJoysticks += fElapsedTime;
	m_fTimeButtons +=  fElapsedTime;
	m_xBufferState = m_xState;
	m_xState = ReadInputState();
	if( m_pxStatePrevious != NULL
		|| m_xState.Gamepad.wButtons != 0
		|| CheckJoystickLUPBuffered()
		|| CheckJoystickLDOWNBuffered()
		|| CheckJoystickLLEFTBuffered()
		|| CheckJoystickLRIGHTBuffered()
		|| CheckJoystickRUPBuffered()
		|| CheckJoystickRDOWNBuffered()
		|| CheckJoystickRLEFTBuffered()
		|| CheckJoystickRRIGHTBuffered()
		|| CheckABuffered()
		|| CheckBBuffered()
		|| CheckXBuffered()
		|| CheckYBuffered())
	{
		for(INT i = m_nMaxHistory-1; i > 0; i--)
		{
			m_pxStatePrevious[i] = m_pxStatePrevious[i-1];
		}
		m_pxStatePrevious[0] = m_xState;
	
	}
	BYTE out;
	if(CheckA())
		m_fATime += fElapsedTime;
	else
		m_fATime = 0.0f;
	if(CheckB())
		m_fBTime += fElapsedTime;
	else
		m_fBTime = 0.0f;
	if(CheckX())
		m_fXTime += fElapsedTime;
	else
		m_fXTime = 0.0f;
	if(CheckY())
		m_fYTime += fElapsedTime;
	else
		m_fYTime = 0.0f;
	if(CheckTRIGGERL(out))
		m_fLeftTriggerTime += fElapsedTime;
	else
		m_fLeftTriggerTime = 0.0f;
	if(CheckTRIGGERR(out))
		m_fRightTriggerTime += fElapsedTime;
	else
		m_fRightTriggerTime = 0.0f;
	if(CheckBUMPERL())
		m_fLeftBumperTime += fElapsedTime;
	else
		m_fLeftBumperTime = 0.0f;
	if(CheckBUMPERR())
		m_fRightBumperTime += fElapsedTime;
	else
		m_fRightBumperTime = 0.0f;


}

XINPUT_STATE CXboxInput::ReadInputState(void)
{
	ZeroMemory(&m_xState, sizeof(XINPUT_STATE));

	XInputGetState(m_nPlayerNum, &m_xState);

	return m_xState;
}

void CXboxInput::Vibrate(WORD left, WORD right)
{
	XINPUT_VIBRATION Vibrate;

	ZeroMemory(&Vibrate, sizeof(XINPUT_VIBRATION));
	Vibrate.wLeftMotorSpeed = left;
	Vibrate.wRightMotorSpeed = right;

	XInputSetState(m_nPlayerNum, &Vibrate);

}

bool CXboxInput::Connected(void)
{
	ZeroMemory(&m_xState, sizeof(XINPUT_STATE));

	DWORD con = XInputGetState(m_nPlayerNum, &m_xState);
	
	if(con == ERROR_SUCCESS)
		return true;
	else
		return false;
}
void CXboxInput::SetJoystickThresholds(SHORT xThreshold, SHORT yThreshold)
{
	m_sJoystickThresholdX = xThreshold;
	m_sJoystickThresholdY = yThreshold;
}
void CXboxInput::SetTriggerThreshold(BYTE Threshold)
{
	m_bTriggerThreshold = Threshold;
}


bool CXboxInput::CheckButtonDelay(void)
{
	return (bool)(m_fTimeButtons >= m_fInputDelayButtons);
}
bool CXboxInput::CheckJoystickDelay(void)
{
	return (bool)(m_fTimeJoysticks >= m_fInputDelayJoysticks);
}
bool CXboxInput::CheckTriggerDelay(void)
{
	return (bool)(m_fTimeTriggers >= m_fInputDelayTriggers);
}

bool CXboxInput::CheckA(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
}
bool CXboxInput::CheckABuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_A) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_A)));
}
bool CXboxInput::CheckX(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
}
bool CXboxInput::CheckXBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_X) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_X)));
}
bool CXboxInput::CheckB(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
}
bool CXboxInput::CheckBBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_B) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_B)));
}
bool CXboxInput::CheckY(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
}
bool CXboxInput::CheckYBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)));
}

bool CXboxInput::CheckSTART(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
}
bool CXboxInput::CheckBACK(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
}
bool CXboxInput::CheckSTARTBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_START) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_START)));
}
bool CXboxInput::CheckBACKBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)));
}

bool CXboxInput::CheckJOYSTICKL(SHORT &dx, SHORT &dy)
{
	dx = m_xState.Gamepad.sThumbLX;
	dy = m_xState.Gamepad.sThumbLY;
	return CheckJoystickLUP() || CheckJoystickLDOWN() || CheckJoystickLLEFT() || CheckJoystickLRIGHT();
}
bool CXboxInput::CheckJOYSTICKR(SHORT &dx, SHORT &dy)
{
	dx = m_xState.Gamepad.sThumbRX;
	dy = m_xState.Gamepad.sThumbRY;
	return CheckJoystickRUP() || CheckJoystickRDOWN() || CheckJoystickRLEFT() || CheckJoystickRRIGHT();
}
bool CXboxInput::CheckBUMPERL(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
}
bool CXboxInput::CheckBUMPERLBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)));
}
bool CXboxInput::CheckBUMPERR(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
}
bool CXboxInput::CheckBUMPERRBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)));
}
bool CXboxInput::CheckTRIGGERL(BYTE &dOut)
{
	dOut = m_xState.Gamepad.bLeftTrigger;
	return dOut > m_bTriggerThreshold;
}
bool CXboxInput::CheckTRIGGERLBuffered(BYTE &dOut)
{
	dOut = m_xState.Gamepad.bLeftTrigger;
	return ((dOut > m_bTriggerThreshold) && (!(m_xBufferState.Gamepad.bLeftTrigger > m_bTriggerThreshold)));
}
bool CXboxInput::CheckTRIGGERR(BYTE &dOut)
{
	dOut = m_xState.Gamepad.bRightTrigger;
	return dOut > m_bTriggerThreshold;
}
bool CXboxInput::CheckTRIGGERRBuffered(BYTE &dOut)
{
	dOut = m_xState.Gamepad.bRightTrigger;
	return ((dOut > m_bTriggerThreshold) && (!(m_xBufferState.Gamepad.bRightTrigger > m_bTriggerThreshold)));
}
// LEFT STICK
bool CXboxInput::CheckJoystickLUP(void)
{
	return (m_xState.Gamepad.sThumbLY > m_sJoystickThresholdY);
}
bool CXboxInput::CheckJoystickLUPBuffered(void)
{
	return ((m_xState.Gamepad.sThumbLY > m_sJoystickThresholdY) && (!(m_xBufferState.Gamepad.sThumbLY > m_sJoystickThresholdY)));
}
bool CXboxInput::CheckJoystickLDOWN(void)
{
	return (m_xState.Gamepad.sThumbLY < -m_sJoystickThresholdY);
}
bool CXboxInput::CheckJoystickLDOWNBuffered(void)
{
	return ((m_xState.Gamepad.sThumbLY < -m_sJoystickThresholdY) && (!(m_xBufferState.Gamepad.sThumbLY < -m_sJoystickThresholdY)));
}
bool CXboxInput::CheckJoystickLLEFT(void)
{
	return (m_xState.Gamepad.sThumbLX < -m_sJoystickThresholdX);
}
bool CXboxInput::CheckJoystickLLEFTBuffered(void)
{
	return ((m_xState.Gamepad.sThumbLX < -m_sJoystickThresholdX) && (!(m_xBufferState.Gamepad.sThumbLX < - m_sJoystickThresholdX)));
}
bool CXboxInput::CheckJoystickLRIGHT(void)
{
	return (m_xState.Gamepad.sThumbLX > m_sJoystickThresholdX);
}
bool CXboxInput::CheckJoystickLRIGHTBuffered(void)
{
	return ((m_xState.Gamepad.sThumbLX > m_sJoystickThresholdX) && (!(m_xBufferState.Gamepad.sThumbLX > m_sJoystickThresholdX)));
}
// RIGHT STICK
bool CXboxInput::CheckJoystickRUP(void)
{
	return (m_xState.Gamepad.sThumbRY > m_sJoystickThresholdY);
}
bool CXboxInput::CheckJoystickRUPBuffered(void)
{
	return ((m_xState.Gamepad.sThumbRY > m_sJoystickThresholdY) && (!(m_xBufferState.Gamepad.sThumbRY > m_sJoystickThresholdY)));
}
bool CXboxInput::CheckJoystickRDOWN(void)
{
	return (m_xState.Gamepad.sThumbRY < -m_sJoystickThresholdY);
}
bool CXboxInput::CheckJoystickRDOWNBuffered(void)
{
	return ((m_xState.Gamepad.sThumbRY < -m_sJoystickThresholdY) && (!(m_xBufferState.Gamepad.sThumbRY < -m_sJoystickThresholdY)));
}
bool CXboxInput::CheckJoystickRLEFT(void)
{
	return (m_xState.Gamepad.sThumbRX < -m_sJoystickThresholdX);
}
bool CXboxInput::CheckJoystickRLEFTBuffered(void)
{
	return ((m_xState.Gamepad.sThumbRX < -m_sJoystickThresholdX) && (!(m_xBufferState.Gamepad.sThumbRX < -m_sJoystickThresholdX)));
}
bool CXboxInput::CheckJoystickRRIGHT(void)
{
	return (m_xState.Gamepad.sThumbRX > m_sJoystickThresholdX);
}
bool CXboxInput::CheckJoystickRRIGHTBuffered(void)
{
	return ((m_xState.Gamepad.sThumbRX > m_sJoystickThresholdX) && (!(m_xBufferState.Gamepad.sThumbRX > m_sJoystickThresholdX)));
}

// DPAD
bool CXboxInput::CheckDPADUP(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
}
bool CXboxInput::CheckDPADUPBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)));
}
bool CXboxInput::CheckDPADDOWN(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
}
bool CXboxInput::CheckDPADDOWNBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)));
}
bool CXboxInput::CheckDPADLEFT(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
}
bool CXboxInput::CheckDPADLEFTBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)));
}
bool CXboxInput::CheckDPADRIGHT(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
}
bool CXboxInput::CheckDPADRIGHTBuffered(void)
{
	return ((m_xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) && (!(m_xBufferState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)));
}