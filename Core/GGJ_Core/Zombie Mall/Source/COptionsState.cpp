#include "COptionsState.h"
#include "CMainMenuState.h"
#include "CAudioState.h"
#include "CGame.h"

#include "CSGD_TextureManager.h"
#include "CSGD_FModManager.h"
#include "CSGD_DirectInput.h"
#include "CPrintFont.h"
#include "CSGD_Direct3D.h"

enum Options { AUDIO, EXIT, NUM_STATES};

COptionsState::COptionsState()
{
	m_pTM = NULL;
	m_pFM = NULL;
	m_pDI = NULL;
	m_pPF = NULL;

}

COptionsState::~COptionsState()
{

}

COptionsState::COptionsState( const COptionsState&)
{

}

COptionsState& COptionsState::operator = (const COptionsState&)
{
	return *this;
}

COptionsState* COptionsState::GetInstance()
{
	static COptionsState instance;
	return &instance;
}

void COptionsState::Enter()
{
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFM = CSGD_FModManager::GetInstance();
	m_pDI = CSGD_DirectInput::GetInstance();

	m_nFontID = m_pTM->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0));
	m_pPF = new CPrintFont(m_nFontID);
	m_nBGImageID = m_pTM->LoadTexture("resource/ZMOptionsScreen.png",D3DCOLOR_XRGB(0, 0, 0));
	m_nMenuMove = CGame::GetInstance()->GetMenuMoveID();
	m_nMenuSelection = CGame::GetInstance()->GetMenuSelectID();
	m_nMenuCancel = CGame::GetInstance()->GetMenuCancelID();
}

void COptionsState::Exit()
{
	//m_pFM->UnloadSound(m_nBackgroundMusicID);
	m_pTM->UnloadTexture(m_nBGImageID);
	m_pTM->UnloadTexture(m_nFontID);
	delete m_pPF;
}

bool COptionsState::Input(void)
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
		return this->HandleEnter();
	}
	return true;

}

void COptionsState::Update(float fElapsedTime)
{
	m_pFM->Update();
}

void COptionsState::Render(void)
{
	//CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	//RECT r = { 0, 0, 800, 600 };
	//CSGD_Direct3D::GetInstance()->DrawRect(r, 0,0,0);
	m_pTM->Draw(m_nBGImageID,0,0,0.8f,0.75f);


	m_pPF->Print("AUDIO",300,350,0.5f,D3DCOLOR_XRGB(200, 0, 0));
//	m_pPF->Print("CONTROLS",300,250,0.5f,D3DCOLOR_XRGB(200, 0, 0));
	m_pPF->Print("EXIT",300,400,0.5f,D3DCOLOR_XRGB(200, 0, 0));
	switch(m_nSelection)
		{
		case AUDIO:			
			m_pPF->Print("AUDIO",300,350,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			break;
//		case CONTROLS:
	//		m_pPF->Print("CONTROLS",300,250,0.5f,D3DCOLOR_XRGB(0, 255, 0));	
	//		break;
		case EXIT:
			m_pPF->Print("EXIT",300,400,0.5f,D3DCOLOR_XRGB(0, 255, 0));
			break;
		}
}

bool COptionsState::HandleEnter(void)
{
	switch(m_nSelection)
		{
		case AUDIO:
			m_pFM->PlaySoundA(m_nMenuSelection);
			CGame::GetInstance()->AddState(CAudioState::GetInstance());
			break;
	//	case CONTROLS:
	//		m_pFM->PlaySoundA(m_nMenuSelection);
	//		break;
		case EXIT:
			m_pFM->PlaySoundA(m_nMenuCancel);
			CGame::GetInstance()->RemoveState();
		}
	return true;
}