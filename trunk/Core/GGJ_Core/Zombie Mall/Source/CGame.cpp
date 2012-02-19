
/////////////////////////////////////////////////////////
//	File Name : "CGame.cpp"
//	Author Name : Wade Shwallon
//	Purpose :  contains all game related code
/////////////////////////////////////////////////////////

#include "CGame.h"
#include "CSGD_Direct3D.h"
#include "CSGD_TextureManager.h"
#include "CSGD_FModManager.h"
#include "CMainMenuState.h"
//#include "COptionState.h"
#include "CSGD_DirectInput.h"
#include "CPlayer.h"
#include <ctime>
//#include <XInput.h>
#include "CCamera.h"
#include "tinyxml.h"

CGame::CGame()
{
	m_pD3D				=	NULL;
	m_pTM				=	NULL;
	m_pFM				=	NULL;
	m_pDI				=	NULL;
	m_pGameState		=	NULL;
	m_pMainMenuState	=	NULL;
	m_pController1 = NULL;
	m_pController2 = NULL;
	m_bController = false;

	m_fElapsedTime		=	0;
	m_ScreenWidth	= 800;
	m_ScreenHeight	= 600;
}

CGame::~CGame()
{

}

CGame::CGame(const CGame& game)
{

}

CGame& CGame::operator =(const CGame& game)
{
	return *this;
}

CGame* CGame::GetInstance()
{
	static CGame instance;
	return &instance;
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	// Get pointers to singletons
	m_pD3D	=	CSGD_Direct3D::GetInstance();
	m_pTM	=	CSGD_TextureManager::GetInstance();
	m_pFM	=	CSGD_FModManager::GetInstance();
	m_pDI	=	CSGD_DirectInput::GetInstance();

	// Controllers
//	m_pController1 = new CXboxInput(1);
	//m_pController2 = new CXboxInput(2);

	CCamera::GetInstance()->SetCamWidth( nScreenWidth );
	CCamera::GetInstance()->SetCamHeight( nScreenHeight );

//	m_bController = m_pController1->Connected();
	m_fInputDelay = 1.0f;
	m_fThumbDelay = 1.0f;

	// Initialize Singletons
	m_pD3D->InitDirect3D(hWnd, nScreenWidth, nScreenHeight, bIsWindowed, false);
	m_pTM->InitTextureManager( m_pD3D->GetDirect3DDevice(), m_pD3D->GetSprite());
	m_pFM->InitFModManager(hWnd);
	m_pDI->InitDirectInput(hWnd, hInstance, DI_KEYBOARD /*| DI_MOUSE*/, 0);


	// Seed the random before user made states are initialized
	srand((unsigned int)time(0));

	// Load the resources in first before the Main Menu calls on the sounds
	Load("resource/AudioSettings.xml");

	// Initialize States
	m_pMainMenuState = CMainMenuState::GetInstance();
	this->AddState(m_pMainMenuState);
	//this->AddState(COptionState::GetInstance());
	// Set GameState
	//ChangeState(CMainMenuState::GetInstance());

	/*m_nSoundAVolume = 0.10f;
	m_nSoundBVolume = 0.8f;
	m_panning = 0.0f;*/
	m_stopWatch.Start();

	// Initialize Sounds
	m_nMenuMove = m_pFM->LoadSound( "resource/sounds/Menu_Move.wav");
	m_pFM->SetVolume(m_nMenuMove, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));

	m_nMenuSelection = m_pFM->LoadSound( "resource/sounds/Menu_Accept.wav");
	m_pFM->SetVolume(m_nMenuSelection, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));

	m_nMenuCancel = m_pFM->LoadSound("resource/sounds/Menu_Cancel.wav");
	m_pFM->SetVolume(m_nMenuCancel, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));
}

bool CGame::Main()
{
	////////////////////////////////////////
	//GameTime
	m_fElapsedTime = (float)m_stopWatch.GetElapsedTime();
	m_stopWatch.Reset();
	////////////////////////////////////////


	// Input
	if( Input() == false )
	{
		return false;
	}

	// Update
	Update(m_fElapsedTime);

	// Render
	Render();

	return true;
}

bool CGame::Input()
{
	static bool windowed = true;
	m_pDI->ReadDevices();


	////xState.Gamepad.wButtons |= XINPUT_GAMEPAD_X;
	//if(m_bController)
	//{
	//	m_pController1->ReadInputState();
	////	m_pController2->ReadInputState();

	//	XINPUT_STATE xState = m_pController1->GetState();
	//	BYTE rTrig = xState.Gamepad.bRightTrigger;

	//	if(xState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	//	{
	//		windowed = !windowed;
	//		m_pD3D->ChangeDisplayParam(m_ScreenWidth, m_ScreenHeight, windowed);
	//		return true;
	//	}
	//	if(xState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
	//	{
	//		CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
	//	}
	//}
	//else
	{
		if(((m_pDI->KeyDown(DIK_LALT) && m_pDI->KeyDown(DIK_RETURN))))
		{
			windowed = !windowed;
			m_pD3D->ChangeDisplayParam(m_ScreenWidth, m_ScreenHeight, windowed);
			return true;
		}

		if (((m_pDI->KeyDown(DIK_RALT) && m_pDI->KeyDown(DIK_RETURN))))
		{
			windowed = !windowed;
			m_pD3D->ChangeDisplayParam(m_ScreenWidth, m_ScreenHeight, windowed);
			return true;
		}
	}

	return m_vGameStates.back()->Input();
}

void CGame::Update(float fElapsedTime)
{
#ifdef _DEBUG
	if( fElapsedTime > 0.0025f )
		fElapsedTime = 0.0025f;
#endif
	m_fInputDelay += fElapsedTime;
	m_fThumbDelay += fElapsedTime;
	m_vGameStates.back()->Update(fElapsedTime);
}

void CGame::Render()
{
	m_pD3D->Clear(0, 0, 0);
	m_pD3D->DeviceBegin();
	m_pD3D->SpriteBegin();
	for(unsigned int i = 0; i < m_vGameStates.size(); i++)
		m_vGameStates[i]->Render();
	m_pD3D->SpriteEnd();
	m_pD3D->DeviceEnd();
	m_pD3D->Present();

}

void CGame::ChangeState(IGameState* state)
{
	if(m_vGameStates.back())
	{
		m_vGameStates.back()->Exit();
		m_vGameStates.pop_back();
	}

	m_vGameStates.push_back(state);

	if(m_vGameStates.back())
		m_vGameStates.back()->Enter();

}

void CGame::AddState(IGameState* state)
{
	m_vGameStates.push_back(state);
	m_vGameStates.back()->Enter();
}

void CGame::RemoveState()
{
	m_vGameStates.back()->Exit();
	m_vGameStates.pop_back();

}

void CGame::ClearStates()
{
	for( std::vector<IGameState*>::size_type curState = 0; curState < m_vGameStates.size(); ++curState )
	{
		RemoveState();
	}
}

void CGame::Shutdown()
{
	delete m_pController1;
	delete m_pController2;
	for(unsigned int i = 0; i < m_vGameStates.size(); i++)
	{
		m_vGameStates.back()->Exit();
		m_vGameStates.pop_back();
	}

	m_pFM->UnloadSound(m_nMenuMove);
	m_pFM->UnloadSound(m_nMenuSelection);
	m_pFM->UnloadSound(m_nMenuCancel);

	// Shutdown in opposite order
	if(m_pDI)
	{
		m_pDI->ShutdownDirectInput();
		m_pDI = NULL;
	}

	if(m_pFM)
	{
		m_pFM->ShutdownFModManager();
		m_pFM = NULL;
	}

	if(m_pTM)
	{
		m_pTM->ShutdownTextureManager();
		m_pTM = NULL;
	}

	if(m_pD3D)
	{
		m_pD3D->ShutdownDirect3D();
		m_pD3D = NULL;
	}


}

int CGame::getSoundAVolume()
{
	return m_nSoundAVolume;
}
int CGame::getSoundBVolume()
{
	return m_nSoundBVolume;
}

void CGame::SetSoundAVolume(int newvol)
{
	m_nSoundAVolume = newvol;
}
void CGame::SetSoundBVolume(int newvol)
{
	m_nSoundBVolume = newvol;
}

int CGame::getPanning()
{
	return m_panning;
}


void CGame::SetPanning(int left)
{
	m_panning = left;
}

CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer1;
}
void CGame::SetPlayer(CPlayer* player)
{
	m_pPlayer1 = player;
}

bool CGame::Load(const char* szFileName)
{
	TiXmlDocument doc;

	if(doc.LoadFile(szFileName) == false)
		return false;

	TiXmlElement* pRoot = doc.RootElement();
	if( !pRoot)
		return false;

	TiXmlElement* Settings = pRoot->FirstChildElement("user_settings");
	if( Settings )
	{
		int music = 0;
		int sfx = 0;
		int panning = 0;

		if( Settings->Attribute("music_volume", &music))
			SetSoundAVolume(music);
		if( Settings->Attribute("sfx_volume", &sfx))
			SetSoundBVolume(sfx);
		if( Settings->Attribute("panning", &panning))
			SetPanning(panning);
		
	}

	return true;
}