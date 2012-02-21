
#include "CLoadState.h"

#include "CPrintFont.h"
#include "CSGD_TextureManager.h"
#include "CSGD_DirectInput.h"
#include "CGame.h"
#include "CGamePlayState.h"

CLoadState::CLoadState()
{
	m_pPF = 0;
	m_fRotation = 0.0f;
}

CLoadState::~CLoadState()
{

}

CLoadState* CLoadState::GetInstance()
{
	static CLoadState instance;
	return &instance;
}

void CLoadState::Enter()
{
	m_fRotation = 0.0f;
	m_pPF = new CPrintFont(CSGD_TextureManager::GetInstance()->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0)));
	m_nOuroboroID = CSGD_TextureManager::GetInstance()->LoadTexture( "resource\\LoadingOuroboros.png" );
	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture( "resource\\ZM LoadScreen.png" );
}

bool CLoadState::Input()
{
	if( CSGD_DirectInput::GetInstance()->CheckBufferedKeysEx() != NULL )
	{
		CGame::GetInstance()->ClearStates();
		CGame::GetInstance()->AddState( CGamePlayState::GetInstance() );
	}

	return true;
}

void CLoadState::Update( float fElapsedTime )
{
	m_fRotation -= 3.14*fElapsedTime;
}

void CLoadState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBGImageID, 0, 0 );
	CSGD_TextureManager::GetInstance()->Draw(m_nOuroboroID,690,490, 0.4f,0.4f,NULL,128,128,m_fRotation);
	//char szScore[32] = {0};
	//sprintf( szScore, "Loading :%d", 100 );
	//m_pPF->Print( szScore, 200, 200, 1.0f, D3DCOLOR_XRGB(255, 255, 255) );

	//m_pPF->PrintCentered( "Press Space to Continue", CGame::GetInstance()->GetScreenWidth() / 2, CGame::GetInstance()->GetScreenHeight() - 50, 1.0f, D3DCOLOR_XRGB(255, 255, 255) );
}

void CLoadState::Exit()
{
	delete m_pPF;

	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nBGImageID );
	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nOuroboroID );
}

bool CLoadState::HandleEnter()
{
	return true;
}