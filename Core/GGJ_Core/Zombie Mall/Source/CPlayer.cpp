#include "CPlayer.h"
#include "CSGD_FModManager.h"
#include "CMessage.h"
#include "CMessageSystem.h"
#include "AnimationManager.h"
#include "CSGD_DirectInput.h"
#include "CCamera.h"
#include "CSGD_Direct3D.h"
#include "CHuman.h"
#include "CGamePlayState.h"
#include "CGame.h"

CPlayer::CPlayer()
{
	m_pFM = CSGD_FModManager::GetInstance();
	//m_nWalkSound = m_pFM->LoadSound("resource/sounds/robogun3.wav");

	this->m_pDI = CSGD_DirectInput::GetInstance();

	m_fInDelay = 0.0f;
	this->SetRotation(0.0f);
	m_nType = OBJECT_PLAYER;

	m_nCollisionWithStaticObjectsSphere.m_fRadius = 32.0f;

	m_pVoice = new CVoices();
	m_pAttackQuotes = new CVoices();
	m_pDmgQuotes = new CVoices();

	m_fTimeBetweenPuns = 0;
	m_fDelayTillNextPun = (float)(std::rand() % (PUN_TIME_RANGE_MAX - PUN_TIME_RANGE_MIN) + PUN_TIME_RANGE_MIN);

	// vvv Load in voices here vvv
	// Chatter
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter01.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter02.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter03.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter04.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter05.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter06.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter07.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter08.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter09.wav");
	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZChatter10.wav");

	// Attacking
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack01.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack02.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack03.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack04.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack05.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack06.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack07.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack08.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack09.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack10.wav");
	m_pAttackQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZAttack11.wav");


	// Damaged
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage01.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage02.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage03.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage04.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage05.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage06.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage07.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage08.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage09.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage10.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage11.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage12.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage13.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage14.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage15.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage16.wav");
	m_pDmgQuotes->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/ZDamage17.wav");


	// Walking
	m_nWalkSound = m_pFM->LoadSound("Resource/Sounds/ZM Audio/WalkLoop.wav", FMOD_LOOP_NORMAL);
	m_pFM->SetVolume(m_nWalkSound, (float)(CGame::GetInstance()->getSoundBVolume() / 100.0f));
	m_pFM->SetPan(m_nWalkSound, (float)(CGame::GetInstance()->getPanning() / 100.0f));
	m_pFM->PlaySoundA(m_nWalkSound);
}

CPlayer::~CPlayer(void)
{
	m_pFM->StopSound(m_nWalkSound);

	delete m_pVoice;
	delete m_pAttackQuotes;
	delete m_pDmgQuotes;
}

void CPlayer::Input(float fElapsedTime)
{
	SHORT x = 0,y = 0;
	//m_pController->CheckJOYSTICKL(x,y);
	tVector2D Vec;
	//SetSpeed(0);
	Vec.fX = 0;
	Vec.fY = 0;
	//SetRot( 0.0f );
	float fRot = 0.0f;
	/*if(m_fInDelay >= 0.005f)
	{*/
	if(this->m_pDI->KeyDown(DIK_D) || this->m_pDI->KeyDown(DIK_RIGHT))
		{
			fRot += 3.14f * fElapsedTime;
			this->SetRotation(this->GetRotation() + 3.14f * fElapsedTime);
			SetRot( GetRot() + 3.14f * fElapsedTime );
			m_fInDelay = 0.0f;
		}
	if(this->m_pDI->KeyDown(DIK_A) || this->m_pDI->KeyDown(DIK_LEFT))
		{
			fRot -= 3.14f * fElapsedTime;
			this->SetRotation(this->GetRotation() - 3.14f * fElapsedTime);
			SetRot( GetRot() - 3.14f * fElapsedTime );
			m_fInDelay = 0.0f;
		}
	//}
	if(GetRot() > 0.0f || GetRot() < 0.0f)
	{
		Vec = this->GetLook();
		Vec = Vector2DRotate( Vec, fRot );
		this->SetLook(Vec);
		
	}
	//CMessageSystem::GetInstance()->SendMsg(new CCreatePlayerBulletMessage(this));
}

void CPlayer::Update(float fElapsedTime)
{
	m_fInDelay += fElapsedTime;

	// I ADDED THIS FOR THE VOICE STUFF
	m_fTimeBetweenPuns += fElapsedTime;
	if (m_fTimeBetweenPuns > m_fDelayTillNextPun)
	{
		if ( !m_pFM->IsSoundPlaying(m_pAttackQuotes->GetLastPlayed()) &&
			 !m_pFM->IsSoundPlaying(m_pDmgQuotes->GetLastPlayed()) )
		{
			m_fTimeBetweenPuns = 0;
			m_fDelayTillNextPun = (float)(std::rand() % (PUN_TIME_RANGE_MAX - PUN_TIME_RANGE_MIN) + PUN_TIME_RANGE_MIN);
		
			m_pVoice->PlayRandomClip();
		}
	}
	
	//////////////////////////////////

	Input( fElapsedTime );
	/*if(this->GetSpeed() > 0 && !this->m_pFM->IsSoundPlaying(m_nWalkSound))
	{
		this->m_pFM->PlaySound(m_nWalkSound);
	}*/
	
	m_nCollisionWithStaticObjectsSphere.m_Center = tVector2D(GetPosX(), GetPosY());
	CBase::Update(fElapsedTime);
}
void CPlayer::Render(void)
{
	AnimManager::GetInstance()->Render( m_nAnimID, 
		(int)(GetPosX() - CCamera::GetInstance()->GetPosX()), (int)(GetPosY() - CCamera::GetInstance()->GetPosY()) , 
		1.0f, 1.0f, GetRot() );
}

type CPlayer::CheckCollision(IBaseInterface* pBase)
{
	// I CHANGED THIS FOR ATTACK VOICE
	type collide = CBase::CheckCollision( pBase );

	switch (collide)
	{
	case type::OBJECT_HUMAN:
		{
			CHuman* pHuman = (CHuman*)pBase;

			pHuman->SetIsUndead( true );
			AnimManager::GetInstance()->SetAnimation( pHuman->GetAnimID(), "Zombie Walking" );

			// Add Points
			CGamePlayState::GetInstance()->AddScore( 1 );

			CGamePlayState::GetInstance()->SetPauseTimer( 2.0f );

			pHuman->SetType( OBJECT_ZOMBIE );

			// ATTACK VOICES
			if ( !m_pFM->IsSoundPlaying(m_pVoice->GetLastPlayed()) &&
				 !m_pFM->IsSoundPlaying(m_pDmgQuotes->GetLastPlayed()) )
			{
				m_pAttackQuotes->PlayRandomClip();
			}
		}break;

	case type::OBJECT_ZOMBIE:
		{
			if( CGamePlayState::GetInstance()->GetPausedTimer() <= 0.0f )
			{
				// Player loses time
				CGamePlayState::GetInstance()->LoseGameTime( 5.0f * CGame::GetInstance()->GetElapsedTime() );
			}

			// Damage Quotes
			if ( !m_pFM->IsSoundPlaying(m_pVoice->GetLastPlayed()) &&
				 !m_pFM->IsSoundPlaying(m_pAttackQuotes->GetLastPlayed()) )
			{
				m_pDmgQuotes->PlayRandomClip();
			}
		}break;

	case type::OBJECT_GUARD:
		{
			if( CGamePlayState::GetInstance()->GetPausedTimer() <= 0.0f )
			{
				// Player loses time
				CGamePlayState::GetInstance()->LoseGameTime( 5.0f * CGame::GetInstance()->GetElapsedTime() );
			}

			// Damage Quotes
			if ( !m_pFM->IsSoundPlaying(m_pVoice->GetLastPlayed()) &&
				 !m_pFM->IsSoundPlaying(m_pAttackQuotes->GetLastPlayed()) )
			{
				m_pDmgQuotes->PlayRandomClip();
			}
		}break;
	};

	return collide;
}

void CPlayer::HandleEvent(CEvent* pEvent)
{

}