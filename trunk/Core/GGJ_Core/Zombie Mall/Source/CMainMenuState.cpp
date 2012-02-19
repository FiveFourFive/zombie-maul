
#include "CMainMenuState.h"
#include "CPrintFont.h"
#include "CSGD_TextureManager.h"
#include "CSGD_FModManager.h"
#include "CSGD_DirectInput.h"
#include "CGame.h"
#include "CGamePlayState.h"
#include "CLoadState.h"
#include "COptionsState.h"
#include "CCreditsState.h"

enum menu {PLAY, OPTIONS, CREDITS, EXIT, NUM_STATES};

CMainMenuState::CMainMenuState(void)
{
	m_pPF = NULL;
	m_pTM = NULL;
	m_pFM = NULL;
	m_pDI = NULL;
	m_pController1 = NULL;
	m_pController2 = NULL;
}
CMainMenuState::~CMainMenuState(void)
{
	
}

CMainMenuState::CMainMenuState(const CMainMenuState&)
{

}

CMainMenuState& CMainMenuState::operator=(const CMainMenuState&)
{
	return *this;
}

CMainMenuState* CMainMenuState::GetInstance(void)
{
	static CMainMenuState instance;
	return &instance;
}

void CMainMenuState::Enter(void)
{
	m_pDI = CSGD_DirectInput::GetInstance();

	m_pTM = CSGD_TextureManager::GetInstance();
	
	m_pController1 = CGame::GetInstance()->GetController1();
	m_pController2 = CGame::GetInstance()->GetController2();


	m_nFontID = m_pTM->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0));
	m_pPF = new CPrintFont(m_nFontID);
	
	m_nBGImageID = m_pTM->LoadTexture("resource/MenuBG1.png", D3DCOLOR_XRGB(255,255,255));

	m_pFM = CSGD_FModManager::GetInstance();

	m_nMenuPlayID = m_pTM->LoadTexture("resource/MenuPlay.png", D3DCOLOR_XRGB(255,255,255));
	m_nMenuOptionsID = m_pTM->LoadTexture("resource/MenuOptions.png", D3DCOLOR_XRGB(255,255,255));
	m_nMenuCreditsID = m_pTM->LoadTexture("resource/MenuCredits.png", D3DCOLOR_XRGB(255,255,255));
	m_nMenuExitID = m_pTM->LoadTexture("resource/MenuExit.png", D3DCOLOR_XRGB(255,255,255));
	m_nMenuPointerID = m_pTM->LoadTexture("resource/MenuPointer.png", D3DCOLOR_XRGB(255,255,255));


	m_nBackgroundMusicID = m_pFM->LoadSound("resource/sounds/ElevatorTheme.wav", FMOD_LOOP_NORMAL);
	m_pFM->SetVolume(m_nBackgroundMusicID, (float)(CGame::GetInstance()->getSoundAVolume() / 100.0f));

	m_pFM->PlaySoundA(m_nBackgroundMusicID);

	m_nMenuMove = m_pFM->LoadSound( "resource/sounds/Menu_Move.wav");
	m_pFM->SetVolume(m_nMenuMove, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));

	m_nMenuSelect = m_pFM->LoadSound( "resource/sounds/Menu_Accept.wav");
	m_pFM->SetVolume(m_nMenuSelect, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));
}

void CMainMenuState::Exit(void)
{
	m_pFM->StopSound(m_nBackgroundMusicID);
	m_pFM->UnloadSound(m_nBackgroundMusicID);
	
	m_pTM->UnloadTexture(m_nFontID);
	delete m_pPF;
}

bool CMainMenuState::Input(void)
{	
	if(m_pDI->KeyPressed(DIK_UP))
	{
		m_nSelection--;
		if(m_nSelection < 0)
			m_nSelection = (NUM_STATES - 1);

		m_pFM->PlaySoundA(m_nMenuMove);
	}

	if(m_pDI->KeyPressed(DIK_DOWN))
	{
		m_nSelection++;
		if(m_nSelection > (NUM_STATES - 1))
			m_nSelection = 0;
		m_pFM->PlaySoundA(m_nMenuMove);

	}
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		m_pFM->PlaySoundA(m_nMenuSelect);
		return this->HandleEnter();
	}
	return true;
}

void CMainMenuState::Update(float fElapsedTime)
{
	m_pFM->Update();
}

void CMainMenuState::Render(void)
{
	m_pTM->Draw(m_nBGImageID, 0, -30, 0.8f, 0.75f);

	switch(m_nSelection)
		{
		case PLAY:			
			m_pTM->Draw( m_nMenuPointerID, 45, 300, 0.4f, 0.4f);
			m_pTM->Draw(m_nMenuPlayID, 240, 290, 0.8f, 0.8f);
			m_pTM->Draw( m_nMenuOptionsID, 290, 390, 0.6f, 0.6f);
			m_pTM->Draw( m_nMenuCreditsID, 280, 460, 0.6f, 0.6f);
			m_pTM->Draw( m_nMenuExitID, 340, 520, 0.5f, 0.5f);
			break;
		case OPTIONS:
			m_pTM->Draw( m_nMenuPointerID, -3, 380, 0.4f, 0.4f);
			m_pTM->Draw(m_nMenuPlayID, 290, 295, 0.5f, 0.5f);
			m_pTM->Draw( m_nMenuOptionsID, 190, 350, 1.0f, 1.0f);
			m_pTM->Draw( m_nMenuCreditsID, 280, 460, 0.6f, 0.6f);
			m_pTM->Draw( m_nMenuExitID, 340, 520, 0.5f, 0.5f);

			break;
		case CREDITS:
			m_pTM->Draw( m_nMenuPointerID, 10, 430, 0.4f, 0.4f);
			m_pTM->Draw(m_nMenuPlayID, 290, 295, 0.5f, 0.5f);
			m_pTM->Draw( m_nMenuOptionsID, 280, 355, 0.6f, 0.6f);
			m_pTM->Draw( m_nMenuCreditsID, 210, 425, 1.0f, 1.0f);
			m_pTM->Draw( m_nMenuExitID, 340, 520, 0.5f, 0.5f);
			break;
		case EXIT:
			m_pTM->Draw( m_nMenuPointerID, 40, 500, 0.4f, 0.4f);
			m_pTM->Draw(m_nMenuPlayID, 290, 295, 0.5f, 0.5f);
			m_pTM->Draw( m_nMenuOptionsID, 280, 355, 0.6f, 0.6f);
			m_pTM->Draw( m_nMenuCreditsID, 280, 440, 0.6f, 0.6f);
			m_pTM->Draw( m_nMenuExitID, 270, 500, 0.7f, 0.7f);
			break;
		}
}

bool CMainMenuState::HandleEnter(void)
{
		switch(m_nSelection)
		{
		case PLAY:			
			CGame::GetInstance()->ChangeState(CLoadState::GetInstance());
			break;
		case OPTIONS:
			CGame::GetInstance()->AddState(COptionsState::GetInstance());
			break;
		case CREDITS:
			CGame::GetInstance()->ChangeState(CCreditsState::GetInstance());
			break;
		case EXIT:
			return false;
		}
	return true;
}



