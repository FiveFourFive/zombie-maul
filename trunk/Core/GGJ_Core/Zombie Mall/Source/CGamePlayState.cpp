#include "CGamePlayState.h"

#include "CObjectManager.h"

#include "CSGD_Direct3D.h"
#include "CSGD_DirectInput.h"
#include "CSGD_TextureManager.h"
#include "CSGD_FModManager.h"
#include "AnimationManager.h"

#include "CStopWatch.h"
#include "CPrintFont.h"

#include "CGame.h"
#include "CMainMenuState.h"
#include "CPlayer.h"
#include "CHuman.h"

#include "CCamera.h"

#include "SGD_Math.h"
#include "CBullet.h"

#include <shlobj.h>
#include <direct.h>
#include "CEnemy.h"
#include "CHuman.h"
#include "Guard.h"

#include "CCollisionRect.h"
#include "CEndGameState.h"

#define TAU 6.283f

CGamePlayState::CGamePlayState(void)
{
	m_pD3D = NULL;
	m_pTM =	NULL;
	m_pFM =	NULL;
	m_pDI =	NULL;
	m_pOM =	NULL;
	m_pOF =	NULL;
	m_pMS = NULL;
	m_pPF = NULL;
	m_pES = NULL;

}

CGamePlayState::CGamePlayState(const CGamePlayState&)
{

}

CGamePlayState& CGamePlayState::operator=(const CGamePlayState&)
{
	return *this;
}

CGamePlayState* CGamePlayState::GetInstance(void)
{
	static CGamePlayState instance;
	return &instance;
}

void CGamePlayState::Enter(void)
{
	RECT lowerhalf = { 200, 500, 600, 540};
	RECT regular_load = { 200, 500, 201, 540};
	int offset = 0;

	m_pD3D	=	CSGD_Direct3D::GetInstance();

	m_pTM	=	CSGD_TextureManager::GetInstance();
	m_pFM	=	CSGD_FModManager::GetInstance();
	m_pDI	=	CSGD_DirectInput::GetInstance();
	m_pOM	=	CObjectManager::GetInstance();
	m_pOF	=	CObjectFactory<string, CBase>::GetInstance();
	m_pMS	=	CMessageSystem::GetInstance ();
	m_pES = CEventSystem::GetInstance ();

	
	m_pMS->InitMessageSystem (MessageProc);

	SetScore( 0 );
	SetGameTime( 120.0f );
	SetPauseTimer( 0.0f ); 

	m_pMS->SendMsg (new CCreateLevelMessage());
	m_pMS->ProcessMessages ();

//	m_pController1 = CGame::GetInstance()->GetController1();
	//m_pController2 = CGame::GetInstance()->GetController2();
	m_pPF = new CPrintFont(m_pTM->LoadTexture("resource/Font.png",D3DCOLOR_XRGB(0, 0, 0)));

	// Initlize Images
	m_nBGImageID = m_pTM->LoadTexture( "resource\\DefaultPlayMap.png" );
	m_nMinimapID = m_pTM->LoadTexture("resource\\GUIMiniMap.png");

	// Initialize BGM
	m_nIntroID = m_pFM->LoadSound("resource/sounds/zm_bg2.mp3");
	m_pFM->SetVolume(m_nIntroID, (float)(CGame::GetInstance()->getSoundAVolume() / 100.0f));
	m_pFM->SetPan(m_nIntroID, (float)(CGame::GetInstance()->getPanning() / 100.0f));
	//m_pFM->SetVolume(m_nIntroID,100);
	m_pFM->PlaySoundA(m_nIntroID);
	CGame::GetInstance()->ResetInputDelay();

	int id = m_pTM->LoadTexture( "resource\\delayicon.png" );
	CPlayer* pPlayer = new CPlayer();
	//pPlayer->SetImageID( id );
	pPlayer->SetAnimID( AnimManager::GetInstance()->LoadAnimation( "resource\\Player.xml" ) );
	AnimManager::GetInstance()->SetAnimation( pPlayer->GetAnimID(), "Player Walking" );
	AnimManager::GetInstance()->PlayAnimation( pPlayer->GetAnimID() );

	pPlayer->SetPosX( 800.0f );
	pPlayer->SetPosY( 700.0f );

	pPlayer->SetWidth( 64 );
	pPlayer->SetHeight( 64 );

	pPlayer->SetDirX( 0.0f );
	pPlayer->SetDirY( -1.0f );

	pPlayer->SetSpeed( 300.0f );

	player = pPlayer;
	player->AddRef();
	m_pOM->AddObject( pPlayer );
	pPlayer->Release();
	m_bSpawnSideX = true;
	m_bSpawnSideY = false;
	m_fSpawnTime = 0.0f;
	
	m_nLeftGuiID = m_pTM->LoadTexture( "resource\\GUIHeaderLeft.png" );
	m_nRightGuiID = m_pTM->LoadTexture( "resource\\GUIHeaderRight.png" );

	Capsule* Bench1 = new Capsule(tVector2D(600, 200), tVector2D(600, 280), 30.0f);
	Capsule* Bench2 = new Capsule(tVector2D(645, 405), tVector2D(720, 405), 30.0f);
	Capsule* Bench3 = new Capsule(tVector2D(900, 405), tVector2D(980, 405), 30.0f);
	Capsule* Bench4 = new Capsule(tVector2D(1013, 200), tVector2D(1013, 280), 30.0f);

	Capsule* HotdogStand1 = new Capsule(tVector2D(767,188), tVector2D(767,265), 45.0f);
	Capsule* HotdogStand2 = new Capsule(tVector2D(767,265), tVector2D(855,250), 45.0f);


	Capsule* WallLeft = new Capsule(tVector2D(540, 880), tVector2D(1050, 880), 40.0f);
	Capsule* WallLeft1 = new Capsule(tVector2D(540, 880), tVector2D(540, 1175), 40.0f);
	Capsule* WallLeft2 = new Capsule(tVector2D(1050, 880), tVector2D(1050, 1175), 40.0f);

	// World WALLS
	Capsule* MapWall = new Capsule(tVector2D(165,10), tVector2D(1420, 10), 40.0f);
	Capsule* MapWall1 = new Capsule(tVector2D(165, 10), tVector2D(165,1000), 40.0f);
	Capsule* MapWall2 = new Capsule(tVector2D(165, 1020), tVector2D(10, 1020), 40.0f);
	Capsule* MapWall3 = new Capsule( tVector2D(10, 1020), tVector2D( 10, 1230), 40.0f);
	Capsule* MapWall4 = new Capsule( tVector2D(10, 1220), tVector2D( 1595, 1220), 35.0f);
	Capsule* MapWall5 = new Capsule( tVector2D( 1420, 10), tVector2D(1420, 1020), 40.0f);
	Capsule* MapWall6 = new Capsule( tVector2D( 1420, 1020), tVector2D(1595, 1020), 40.0f);
	Capsule* MapWall7 = new Capsule( tVector2D( 1595, 1020), tVector2D(1595, 1230), 40.0f);

	m_StoreWalls.push_back(WallLeft);
	m_StoreWalls.push_back(WallLeft1);
	m_StoreWalls.push_back(WallLeft2);
	m_StoreWalls.push_back(Bench1);
	m_StoreWalls.push_back(Bench2);
	m_StoreWalls.push_back(Bench3);
	m_StoreWalls.push_back(Bench4);
	m_StoreWalls.push_back(HotdogStand1);
	m_StoreWalls.push_back(HotdogStand2);
	m_StoreWalls.push_back(MapWall);
	m_StoreWalls.push_back(MapWall1);
	m_StoreWalls.push_back(MapWall2);
	m_StoreWalls.push_back(MapWall3);
	m_StoreWalls.push_back(MapWall4);
	m_StoreWalls.push_back(MapWall5);
	m_StoreWalls.push_back(MapWall6);
	m_StoreWalls.push_back(MapWall7);

	InitializeGuardVoices();
}

void CGamePlayState::Exit(void)
{
	player->Release();
	AnimManager::DeleteInstance();

	m_pES->ClearEvents ();
	m_pES->ShutdownEventSystem ();

	m_pFM->StopSound( m_nIntroID );
	m_pFM->UnloadSound( m_nIntroID );

	for( unsigned int i = 0; i < m_StoreWalls.size(); i++)
	{
		delete m_StoreWalls[i];
	}
	m_StoreWalls.clear();

	delete m_pPF;
	if(m_pOF)
	{
		m_pOF->ShutDownFactory();
		m_pOF = NULL;
	}
	if(m_pOM)
	{
		m_pOM->RemoveAllObjects();
		m_pOM = NULL;
		m_pOM->DeleteInstance();
	}

	delete guardVoice1;
	delete guardVoice2;
	delete guardVoice3;
}

bool CGamePlayState::Input()
{
	//if(CGame::GetInstance()->ControllerInput())
	//{
	//	//m_pController1->ReadInputState();
	//	XINPUT_STATE xState = m_pController1->GetState();
	//	BYTE rTrig = xState.Gamepad.bRightTrigger;
	//	float x = xState.Gamepad.sThumbLX;
	//	float y = xState.Gamepad.sThumbLY;

	//	if(CGame::GetInstance()->GetInputDelay() >= 0.15f)
	//	{
	//		CGame::GetInstance()->ResetInputDelay();
	//		/*if(xState.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	//		{
	//			CGame::GetInstance()->AddState(CPauseMenuState::GetInstance());
	//			CPauseMenuState::GetInstance()->SetController(m_pController1);
	//			return true;
	//		}*/
	//		
	//	}

	//	if(CGame::GetInstance()->GetThumbDelay() >= 0.15f)
	//	{
	//		CGame::GetInstance()->ResetThumbDelay();
	//	}
	//}
	//else
	{

		
			if(m_pDI->KeyPressed(DIK_RETURN))
			{
			
			}
			else if(m_pDI->KeyPressed(DIK_ESCAPE))
			{
				CGame::GetInstance()->ChangeState(CMainMenuState::GetInstance());
			}
		
	}
	return true;
}

void CGamePlayState::Update(float fElapsedTime)
{
	/*
	if( m_pDI->KeyDown( DIK_UP ) )
	{
		CCamera::GetInstance()->SetPosY( CCamera::GetInstance()->GetPosY() - 100.0f * fElapsedTime );
	}
	else if( m_pDI->KeyDown( DIK_DOWN ) )
	{
		CCamera::GetInstance()->SetPosY( CCamera::GetInstance()->GetPosY() + 100.0f * fElapsedTime );
	}

	if( m_pDI->KeyDown( DIK_LEFT ) )
	{
		CCamera::GetInstance()->SetPosX( CCamera::GetInstance()->GetPosX() - 100.0f * fElapsedTime );
	}
	else if( m_pDI->KeyDown( DIK_RIGHT ) )
	{
		CCamera::GetInstance()->SetPosX( CCamera::GetInstance()->GetPosX() + 100.0f * fElapsedTime );
	}
	*/

	m_fSpawnTime += fElapsedTime;
	if(player->GetPosX() < 800)
	{
		m_bSpawnSideX = true;
	}
	else
		m_bSpawnSideX = false;
	if(player->GetPosY() < 600)
	{
		m_bSpawnSideY = true;
	}
	else
		m_bSpawnSideY = false;
	

	// spawn right side
	if(m_fSpawnTime >= 3.0f)
	{
		if (std::rand() % 100 < 79)
			SpawnHuman();
		else
			SpawnGuard();
	}



	CCamera::GetInstance()->SetPosX( player->GetCenterPosX() - (CCamera::GetInstance()->GetCamWidth() / 2) );
	CCamera::GetInstance()->SetPosY( player->GetCenterPosY() - (CCamera::GetInstance()->GetCamHeight() / 2) );

	int width = 1600;
	int height = 1200;

	if(CCamera::GetInstance()->GetPosX() < 0)
	{
		CCamera::GetInstance()->SetPosX(0);
	}
	else if(CCamera::GetInstance()->GetPosX()+CCamera::GetInstance()->GetCamWidth() > width)
	{
		CCamera::GetInstance()->SetPosX((float)width - CCamera::GetInstance()->GetCamWidth());
	}
	if(CCamera::GetInstance()->GetPosY() < 0)
	{
		CCamera::GetInstance()->SetPosY(0);
	}

	else if(CCamera::GetInstance()->GetPosY()+CCamera::GetInstance()->GetCamHeight() > height)
	{
		CCamera::GetInstance()->SetPosY((float)height - CCamera::GetInstance()->GetCamHeight());
	}

	AnimManager::GetInstance()->Update( fElapsedTime );

	if(!m_pFM->IsSoundPlaying(m_nIntroID))
		m_pFM->PlaySoundA(m_nIntroID);

	m_pFM->Update();
	m_pOM->UpdateObjects(fElapsedTime);

	for( unsigned int i = 0; i < m_StoreWalls.size(); i++)
	{
		Capsule* temp = m_StoreWalls[i];
		tVector2D ClosestPoint = ClosestPointOnALine(temp->GetStartPoint(), temp->GetEndPoint(), tVector2D( player->GetPosX(), player->GetPosY()));

		// Create a circle based on clsoest point with capsule radius
		Circle testCircle;
		testCircle.m_Center = ClosestPoint;
		testCircle.m_fRadius = temp->GetRadius();

		if( player->GetSphere()->CheckCollision(testCircle) )
		{
			tVector2D sphere2_to_1 = player->GetSphere()->m_Center - testCircle.m_Center;
			sphere2_to_1 = Vector2DNormalize(sphere2_to_1);
			float dist = player->GetSphere()->m_fRadius + testCircle.m_fRadius;
			tVector2D scaler = (sphere2_to_1 * (dist * 0.01f));
			tVector2D newpos = player->GetSphere()->m_Center + scaler;

			player->SetPosX(newpos.fX);
			player->SetPosY(newpos.fY);
		}
	}

	m_pES->ProcessEvents ();
	m_pMS->ProcessMessages ();

	if( GetPausedTimer() <= 0.0f )
	{
		LoseGameTime( fElapsedTime );
	}
	else
	{
		SetPauseTimer( GetPausedTimer() - fElapsedTime );
	}

	if( GetGameTime() <= 0.0f )
	{
		CGame::GetInstance()->ChangeState( CEndGameState::GetInstance() );
	}

}

void CGamePlayState::SpawnHuman(void)
{
	m_fSpawnTime = 0.0f;
	CHuman* newhuman = new CHuman();
	newhuman->SetSpeed(120);
	newhuman->SetAnimID( AnimManager::GetInstance()->LoadAnimation( "resource\\Person.xml" ) );
	AnimManager::GetInstance()->SetAnimation( newhuman->GetAnimID(), "Person Walking" );
	AnimManager::GetInstance()->PlayAnimation( newhuman->GetAnimID() );
	
	newhuman->SetWidth( 64 );
	newhuman->SetHeight( 64 );

	newhuman->SetDirX( 0.0f );
	newhuman->SetDirY( -1.0f );
	newhuman->SetRotation(0.0f);

	if(m_bSpawnSideX)
		newhuman->SetPosX(1300);
	else
		newhuman->SetPosX(300);
		
	if(m_bSpawnSideY)
		newhuman->SetPosY(1100);
	else
		newhuman->SetPosY(100);
	this->m_pOM->AddObject(newhuman);
	newhuman->Release();
}

void CGamePlayState::SpawnGuard(void)
{
	m_fSpawnTime = 0.0f;
	CGuard* newguard = new CGuard();
	newguard->SetpPlayer(player);
	newguard->SetSpeed(250);
	newguard->SetAnimID( AnimManager::GetInstance()->LoadAnimation( "resource\\Guard.xml" ) );
	AnimManager::GetInstance()->SetAnimation( newguard->GetAnimID(), "Guard Walking" );
	AnimManager::GetInstance()->PlayAnimation( newguard->GetAnimID() );
	
	newguard->SetWidth( 64 );
	newguard->SetHeight( 64 );

	newguard->SetDirX( 0.0f );
	newguard->SetDirY( -1.0f );
	newguard->SetRotation(0.0f);

	int raNum = std::rand() % 3;

	if ( raNum == 0 )
		newguard->TakeBackYourLegs(guardVoice1);
	else if ( raNum == 1 )
		newguard->TakeBackYourLegs(guardVoice2);
	else
		newguard->TakeBackYourLegs(guardVoice3);


	if(m_bSpawnSideX)
		newguard->SetPosX(1300);
	else
		newguard->SetPosX(300);
		
	if(m_bSpawnSideY)
		newguard->SetPosY(1100);
	else
		newguard->SetPosY(100);
	this->m_pOM->AddObject(newguard);
	newguard->Release();
}

void CGamePlayState::Render(void)
{
	RECT r = { (LONG)CCamera::GetInstance()->GetPosX(),
		(LONG)CCamera::GetInstance()->GetPosY(),
		r.left + (LONG)CCamera::GetInstance()->GetCamWidth(),
		r.top + (LONG)CCamera::GetInstance()->GetCamHeight() };

	m_pTM->Draw( m_nBGImageID, 0, 0, 1.0f, 1.0f, &r );
	m_pOM->RenderObjects();
	RenderMinimap();

	RenderHUD();
}

void CGamePlayState::RenderMinimap()
{
	m_pTM->Draw(m_nMinimapID,600,425,0.7f,0.7f);
	
	//CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	//RECT r = { 600 + player->GetPosX() * 0.108f,
	//	452 + player->GetPosY() * 0.104f,
	//	r.left + 2,
	//	r.top + 2 };

	//m_pD3D->DrawRect(r,255,0,0);
	m_pOM->DrawObjects();

}

void CGamePlayState::RenderHUD()
{
	m_pTM->Draw( m_nLeftGuiID, 0, 0 );
	m_pTM->Draw( m_nRightGuiID, CCamera::GetInstance()->GetCamWidth() - m_pTM->GetTextureWidth( m_nRightGuiID ), 0 );

	char szScore[32] = {0};
	sprintf_s( szScore, "Score:%d", GetScore() );
	m_pPF->Print( szScore, 0, 0, 1.0f, D3DCOLOR_XRGB(0, 0, 0) );

	char szTime[32] = {0};
	sprintf_s( szTime, "Time:%.0f", GetGameTime() );
	m_pPF->Print( szTime, CCamera::GetInstance()->GetCamWidth() - m_pTM->GetTextureWidth( m_nRightGuiID ) + 50, 0, 1.0f, D3DCOLOR_XRGB(0, 0, 0) );
}

bool CGamePlayState::HandleEnter(void)
{
	return true;
}

void CGamePlayState::MessageProc(CBaseMessage* pMsg)
{
	switch(pMsg->GetMsgID())
	{
	//case MSG_CREATE_PLAYER_BULLET:
	//	{

	//		CCreatePlayerBulletMessage* pCBM = (CCreatePlayerBulletMessage*)pMsg;

	//		CGamePlayState* pGame = CGamePlayState::GetInstance();
	//		CBullet* pBullet = new CBullet();
	//		//CBullet* pBullet = (CBullet*)pGame->m_pOF->CreateObject("CBullet");
	//		//CBullet* pBullet = new CBullet();
	//		CPlayer* pPlayer = pCBM->GetPlayer();
	//		char x,y;
	//		//pPlayer->GetShoot(x,y);
	//		pBullet->SetPosX(pPlayer->GetPosX());
	//		pBullet->SetPosY(pPlayer->GetPosY());
	//		pBullet->SetDir(x,y);
	//		float rot;
	//		if(x < 0)
	//		{
	//			rot = 270.0f/360.0f*TAU;
	//			if(y < 0)
	//			{
	//				rot = 315.0f/360.0f*TAU;
	//			}
	//			else if(y > 0)
	//			{
	//				rot = 225.0f/360.0f*TAU;
	//			}
	//			
	//		}
	//		else if(x > 0)
	//		{
	//			rot = 90.0f/360.0f*TAU;
	//			if(y < 0)
	//			{
	//				rot = 45.0f/360.0f*TAU;
	//			}
	//			else if(y > 0)
	//			{
	//				rot = 135.0f/360.0f*TAU;
	//			}
	//			
	//		}
	//		else
	//		{
	//			if(y < 0)
	//			{
	//				rot = 0.0f;
	//			}
	//			else if(y > 0)
	//			{
	//				rot = 180.0f/360.0f*TAU;
	//			}
	//		}
	//		pBullet->SetRot(rot);
	//		pGame->m_pOM->AddObject(pBullet);

	//		break;
	//	}
	//case MSG_DESTROY_BULLET:
	//	{
	//		//CDestroyBulletMessage* pM = (CDestroyBulletMessage*)pMsg;
	//		//CBullet* tempbullet = pM->GetBullet();
	//		//CGamePlayState* pGame = CGamePlayState::GetInstance();
	//		//pGame->m_pOM->RemoveObject(tempbullet);
	//		break;
	//	}
	}
}

void CGamePlayState::InitializeGuardVoices()
{
	guardVoice1 = new CVoices();
	guardVoice2 = new CVoices();
	guardVoice3 = new CVoices();

	// Guard Voice 1
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_01.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_02.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_03.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_04.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_05.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_06.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_07.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_08.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_09.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_10.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_11.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_12.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_13.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_14.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_15.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_16.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_17.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_18.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_19.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_20.wav");
	guardVoice1->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_21.wav");

	// Guard Voice 2
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_01.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_02.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_03.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_04.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_05.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_06.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_07.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_08.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_09.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_10.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_11.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_12.wav");
	guardVoice2->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_13.wav");

	// Guard Voice 3
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_01.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_02.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_03.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_04.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_05.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_06.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_07.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_08.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_09.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_10.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_11.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_12.wav");
	guardVoice3->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_13.wav");
}