
#include "CEndGameState.h"

#include "CPrintFont.h"
#include "CSGD_TextureManager.h"
#include "CSGD_DirectInput.h"
#include "CGame.h"
#include "CMainMenuState.h"
#include "CGamePlayState.h"

CEndGameState::CEndGameState()
{
	m_pPF = 0;
}

CEndGameState::~CEndGameState()
{

}

CEndGameState* CEndGameState::GetInstance()
{
	static CEndGameState instance;
	return &instance;
}

void CEndGameState::Enter()
{
	m_pPF = new CPrintFont(CSGD_TextureManager::GetInstance()->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0)));

	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture( "resource\\EndScreen.jpg" );
}

bool CEndGameState::Input()
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_SPACE ) )
	{
		CGame::GetInstance()->ClearStates();
		CGame::GetInstance()->AddState( CMainMenuState::GetInstance() );
	}

	return true;
}

void CEndGameState::Update( float fElapsedTime )
{

}

void CEndGameState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBGImageID, 0, 0 );

	char szScore[32] = {0};
	sprintf_s( szScore, "Final Score:%d", CGamePlayState::GetInstance()->GetScore() );
	m_pPF->Print( szScore, 200, 200, 1.0f, D3DCOLOR_XRGB(255, 255, 255) );
}

void CEndGameState::Exit()
{
	delete m_pPF;

	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nBGImageID );
}

bool CEndGameState::HandleEnter()
{
	return true;
}