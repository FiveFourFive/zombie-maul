
#include "CCreditsState.h"

#include "CPrintFont.h"
#include "CSGD_TextureManager.h"
#include "CSGD_DirectInput.h"
#include "CGame.h"
#include "CMainMenuState.h"
#include "CGamePlayState.h"

CCreditsState::CCreditsState()
{
	m_pPF = 0;
	m_nStartingY = -300;
	m_nEndingY = 200;
	m_vNames.push_back( "Credits" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Programmers" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Ren Davis" );
	m_vNames.push_back( "Kelsey Ishmael" );
	m_vNames.push_back( "Wade Shwallon" );
	m_vNames.push_back( "Andy Madruga" );
	m_vNames.push_back( "Charlie Prouse" );
	m_vNames.push_back( "Roger Prouse" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Artists" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Stacey Miller" );
	m_vNames.push_back( "Jesse Williams" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Audio Engineer" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Jesse Williams" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Special Thanks" );
	m_vNames.push_back( "" );
	m_vNames.push_back( "Zach Gurley" );
	m_vNames.push_back( "Jeff Chilson" );
	m_pYPos = new float[m_vNames.size()];
}

CCreditsState::~CCreditsState()
{
	delete[] m_pYPos;
}

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState instance;
	return &instance;
}

void CCreditsState::Enter()
{
	m_pPF = new CPrintFont(CSGD_TextureManager::GetInstance()->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0)));

	m_nBGImageID = CSGD_TextureManager::GetInstance()->LoadTexture( "resource\\ZMCreditsScreen.png" );

	for(int i = 0; i < m_vNames.size(); i++)
	{
		m_pYPos[i] = 600.0f + 50.0f*(float)i;
	}
}

bool CCreditsState::Input()
{
	if( CSGD_DirectInput::GetInstance()->CheckKeys() != NULL )
	{
		CGame::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
	}

	return true;
}

void CCreditsState::Update( float fElapsedTime )
{
	for(int i = 0; i < m_vNames.size(); i++)
	{
		m_pYPos[i] -= 40.0f * fElapsedTime;
	}
}

void CCreditsState::Render()
{
	CSGD_TextureManager::GetInstance()->Draw( m_nBGImageID, 0, 0 ,0.8f,0.75f);

	for( std::vector<std::string>::size_type i = 0; i < m_vNames.size(); ++i )
	{
		
		if(m_pYPos[i] >= m_nEndingY)
			m_pPF->Print( m_vNames[i].c_str(), 200, (int)m_pYPos[i], 0.8f, D3DCOLOR_XRGB(0, 0, 0) );
	}

	m_pPF->PrintCentered( "Press Any Key to Continue", CGame::GetInstance()->GetScreenWidth() / 2, CGame::GetInstance()->GetScreenHeight() - 50, 1.0f, D3DCOLOR_XRGB(255, 255, 255) );
}

void CCreditsState::Exit()
{
	delete m_pPF;

	CSGD_TextureManager::GetInstance()->UnloadTexture( m_nBGImageID );
}

bool CCreditsState::HandleEnter()
{
	return true;
}