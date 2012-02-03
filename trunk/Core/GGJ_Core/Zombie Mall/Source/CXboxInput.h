/////////////////////////////////////////////////////////
//	File Name : "CXboxInput.h"
//	Author Name : Wade Shwallon
//  Created On: 6-17-2011
//	Purpose : To contain the functionality of gamepad input
/////////////////////////////////////////////////////////


#ifndef _CXBOXINPUT_H
#define _CXBOXINPUT_H
#include <Windows.h>
#include <XInput.h>
#include "CStopWatch.h"
#pragma comment(lib, "xinput.lib")
#define MAXMAXHISTORY 100
#define MINMAXHISTORY 0
#define MINCOMBO 3
/////////////////////////////
//_FLOAT128
/////////////////////////////
// TODO 
// read combos from file
// changeable combos
enum Keys{ XBOX_A = 0,XBOX_B,XBOX_X,XBOX_Y,XBOX_UP,XBOX_DOWN,XBOX_LEFT,XBOX_RIGHT,XBOX_L_BUMPER,XBOX_R_BUMPER,
	XBOX_L_TRIGGER,XBOX_R_TRIGGER,XBOX_BACK,XBOX_START};
 
class CXboxInput
{
private:
	XINPUT_STATE m_xState;
	XINPUT_STATE m_xBufferState;
	XINPUT_STATE* m_pxStatePrevious;
	XINPUT_STATE** m_pxStateCombos;
	INT m_nNumCombos;
	INT m_nMaxHistory;
	INT m_nCurrentHistory;
	INT m_nCurrNumCombos;
	float m_fInputDelayTriggers;
	float m_fInputDelayJoysticks;
	float m_fInputDelayButtons;
	float m_fTimeTriggers;
	float m_fTimeJoysticks;
	float m_fTimeButtons;
	INT m_nBufferedBits;
	BYTE m_nPlayerNum;
	BYTE m_bTriggerThreshold;
	SHORT m_sJoystickThresholdX;
	SHORT m_sJoystickThresholdY;

	
	float m_fLeftTriggerTime,m_fRightTriggerTime,m_fLeftBumperTime,
		  m_fRightBumperTime,m_fXTime,m_fYTime,m_fBTime,m_fATime;


	// move to combo class
	//


	//

public:

	CXboxInput(INT PlayerNum);
	XINPUT_STATE ReadInputState(void);
	XINPUT_STATE GetState(void) { return m_xState; }
	float getATime() { return m_fATime; }
	float getBTime() { return m_fBTime; }
	float getXTime() { return m_fXTime; }
	float getYTime() { return m_fYTime; }
	float getBumperLTime() { return m_fLeftBumperTime; }
	float getBumperRTime() { return m_fRightBumperTime; }
	float getTriggerLTime() { return m_fLeftTriggerTime; }
	float getTriggerRTime() { return m_fRightTriggerTime; }
	void InitPrevious(INT maxHistory);
	void InitCombo(INT size, XINPUT_STATE* combo);
	void Update(float fElapsedTime);
	bool Connected(void);
	void Vibrate(WORD left = 0, WORD right = 0);
	void SetJoystickThresholds(SHORT xThreshold, SHORT yThreshold);
	void SetTriggerThreshold(BYTE Threshold);
	bool CheckButtonDelay(void);
	bool CheckTriggerDelay(void);
	bool CheckJoystickDelay(void);

	// these functions check to see if the button 
	// is pressed down
	bool CheckA(void);
	bool CheckX(void);
	bool CheckB(void);
	bool CheckY(void);
	bool CheckSTART(void);
	bool CheckBACK(void);
	bool CheckBUMPERL(void);
	bool CheckBUMPERR(void);
	bool CheckTRIGGERL(BYTE &dOut);
	bool CheckTRIGGERR(BYTE &dOut);

	// these joystick checks will return true if 
	// any direction is being pressed
	bool CheckJOYSTICKL(SHORT &dx, SHORT &dy);
	bool CheckJOYSTICKR(SHORT &dx, SHORT &dy);

	bool CheckJoystickLUP(void);
	bool CheckJoystickLDOWN(void);
	bool CheckJoystickLLEFT(void);
	bool CheckJoystickLRIGHT(void);
	bool CheckJoystickRUP(void);
	bool CheckJoystickRDOWN(void);
	bool CheckJoystickRLEFT(void);
	bool CheckJoystickRRIGHT(void);
	bool CheckDPADUP(void);
	bool CheckDPADDOWN(void);
	bool CheckDPADLEFT(void);
	bool CheckDPADRIGHT(void);

	// these functiosn check to see if the button
	// is pressed and was previously not pressed
	bool CheckABuffered(void);
	bool CheckXBuffered(void);
	bool CheckBBuffered(void);
	bool CheckYBuffered(void);
	bool CheckSTARTBuffered(void);
	bool CheckBACKBuffered(void);
	bool CheckBUMPERLBuffered(void);
	bool CheckBUMPERRBuffered(void);
	bool CheckTRIGGERLBuffered(BYTE &dOut);
	bool CheckTRIGGERRBuffered(BYTE &dOut);
	bool CheckJoystickLUPBuffered(void);
	bool CheckJoystickLDOWNBuffered(void);
	bool CheckJoystickLLEFTBuffered(void);
	bool CheckJoystickLRIGHTBuffered(void);
	bool CheckJoystickRUPBuffered(void);
	bool CheckJoystickRDOWNBuffered(void);
	bool CheckJoystickRLEFTBuffered(void);
	bool CheckJoystickRRIGHTBuffered(void);
	bool CheckDPADUPBuffered(void);
	bool CheckDPADDOWNBuffered(void);
	bool CheckDPADLEFTBuffered(void);
	bool CheckDPADRIGHTBuffered(void);

	void ReadCombos(char* szFileName);
};

#endif