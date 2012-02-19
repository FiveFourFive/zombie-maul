#include "Guard.h"
#include "CSGD_TextureManager.h"

#include "AnimationManager.h"
#include "CCamera.h"
#include "CSGD_DirectInput.h"
#include "CSGD_Direct3D.h"
#include "CGamePlayState.h"
#include "CPlayer.h"

CGuard::CGuard(void)
{
	IsUndead = false;
	m_nAnimID = -1;
	m_nCollisionWithStaticObjectsSphere.m_Center = tVector2D(0.0f,0.0f);
	m_nCollisionWithStaticObjectsSphere.m_fRadius = 32.0f;
	m_nType = type::OBJECT_GUARD;

	//int raNum = std::rand() % 3;

	//m_pVoice = new CVoices();

	//if (raNum == 0)
	//{
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_01.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_02.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_03.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_04.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_05.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_06.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_07.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_08.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_09.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_10.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_11.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_12.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_13.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_14.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_15.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_16.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_17.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_18.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_19.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_20.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G1_21.wav");
	//}
	//else if (raNum == 1)
	//{
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_01.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_02.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_03.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_04.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_05.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_06.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_07.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_08.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_09.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_10.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_11.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_12.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G2_13.wav");
	//}
	//else
	//{
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_01.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_02.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_03.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_04.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_05.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_06.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_07.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_08.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_09.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_10.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_11.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_12.wav");
	//	m_pVoice->AddVoice("Resource/Sounds/ZM Audio/Vocalizations/G3_13.wav");
	//}

	//m_pVoice->PlayRandomClip();
}


CGuard::~CGuard(void)
{
	//delete m_pVoice;
	m_pVoice = NULL;
}

void CGuard::Update(float fElapsedTime)
{

	if(CheckForPlayer())
	{
		ComputeMovement(fElapsedTime);
		this->addTime(fElapsedTime);
		CBase::Update(fElapsedTime);
	}
	else
		CEnemy::Update( fElapsedTime );

	m_nCollisionWithStaticObjectsSphere.m_Center = tVector2D(GetPosX(), GetPosY());


	for( unsigned int i = 0; i < CGamePlayState::GetInstance()->m_StoreWalls.size(); i++)
	{
		Capsule* temp = CGamePlayState::GetInstance()->m_StoreWalls[i];
		tVector2D ClosestPoint = ClosestPointOnALine(temp->GetStartPoint(), temp->GetEndPoint(), tVector2D( GetPosX(), GetPosY()));

		// Create a circle based on clsoest point with capsule radius
		Circle testCircle;
		testCircle.m_Center = ClosestPoint;
		testCircle.m_fRadius = temp->GetRadius();

		if( GetSphere()->CheckCollision(testCircle) )
		{
			tVector2D sphere2_to_1 = GetSphere()->m_Center - testCircle.m_Center;
			sphere2_to_1 = Vector2DNormalize(sphere2_to_1);
			float dist = GetSphere()->m_fRadius + testCircle.m_fRadius;
			tVector2D scaler = (sphere2_to_1 * (dist * 0.01f));
			tVector2D newpos = GetSphere()->m_Center + scaler;

			SetPosX(newpos.fX);
			SetPosY(newpos.fY);
		}
	}

	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_1))
	{
		IsUndead = true;
		AnimManager::GetInstance()->SetAnimation( GetAnimID(), "Zombie Walking" );
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_2))
	{
		IsUndead = false;
		AnimManager::GetInstance()->SetAnimation( GetAnimID(), "Person Walking" );
	}
}
bool CGuard::CheckForPlayer(void)
{
	float myradius = 500;

	float distance = (pPlayer->GetPosX() - this->GetPosX())*(pPlayer->GetPosX() - this->GetPosX()) + 
					(pPlayer->GetPosY() - this->GetPosY())*(pPlayer->GetPosY() - this->GetPosY());
	float r = myradius;
	r = r*r;
	if(distance < r)
		return true;

	return false;

}
void CGuard::HuntPlayer(void)
{

}
void CGuard::ComputeMovement(float fElapsedTime)
{
	tVector2D myvec;
	myvec.fX = this->GetLook().fX;
	myvec.fY = this->GetLook().fY;

	tVector2D playervec;
	playervec.fX = pPlayer->GetPosX() - this->GetPosX();
	playervec.fY = pPlayer->GetPosY() - this->GetPosY();

	tVector2D rightvec = Vector2DRotate(myvec,1.57f);



	float dot = DotProduct(rightvec,playervec);
	
	if(Steering(myvec,playervec) > 0) // clockwise
	{
		/*myvec = Vector2DRotate(myvec,3.14*fElapsedTime);
		this->SetRotation(this->GetRotation() + 3.14*fElapsedTime);
		this->SetLook(myvec);*/
		myvec = Vector2DRotate(myvec,0.9f*fElapsedTime);
		this->SetRotation(this->GetRotation() + 0.9f*fElapsedTime);
		this->SetLook(myvec);
	}
	else
	{
		/*myvec = Vector2DRotate(myvec,-3.14*fElapsedTime);
		this->SetRotation(this->GetRotation() - 3.14*fElapsedTime);
		this->SetLook(myvec);*/
		myvec = Vector2DRotate(myvec,(-0.9f)*fElapsedTime);
		this->SetRotation(this->GetRotation() + (-0.9f)*fElapsedTime);
		this->SetLook(myvec);
	}
	
}

void CGuard::Render(void)
{
	/*if( IsUndead )
	{
		//CCamera* cam = CCamera::GetInstance();
		//RECT r = { (int)GetCenterPosX() - cam->GetPosX(), (int)GetCenterPosY() - cam->GetPosY() , r.left + GetWidth(), r.top + GetHeight()};
		//CSGD_Direct3D::GetInstance()->DrawRect(r, 255, 0, 0);
	}
	else*/
	{
		AnimManager::GetInstance()->Render( m_nAnimID, 
			(int)(GetPosX() - CCamera::GetInstance()->GetPosX()), (int)(GetPosY() - CCamera::GetInstance()->GetPosY()) , 
			1.0f, 1.0f, this->GetRotation() );
	}
}

type CGuard::CheckCollision(IBaseInterface* pBase)
{
	return CBase::CheckCollision(pBase);
}

void CGuard::HandleEvent(CEvent* pEvent)
{

}

void CGuard::TakeBackYourLegs(CVoices* pVoice)
{
	m_pVoice = pVoice;

	// Called on initialization, so go ahead and say something
	m_pVoice->PlayRandomClip();
}