#include "CHuman.h"
#include "CSGD_TextureManager.h"

#include "AnimationManager.h"
#include "CCamera.h"
#include "CSGD_DirectInput.h"
#include "CSGD_Direct3D.h"
#include "CGamePlayState.h"

CHuman::CHuman(void)
{
	IsUndead = false;
	m_nAnimID = -1;
	m_nCollisionWithStaticObjectsSphere.m_Center = tVector2D(0.0f,0.0f);
	m_nCollisionWithStaticObjectsSphere.m_fRadius = 32.0f;
	m_nType = OBJECT_HUMAN;
}

CHuman::~CHuman(void)
{


}


void CHuman::Update(float fElapsedTime)
{
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
}

void CHuman::ComputeMovement(float fElapsedTime)
{
	//m_fStopDelay -= fElapsedTime;
	///*SetVelX(0);
	//SetVelY(0);*/
	///*if(m_fStopDelay <= 0)
	//{*/
	//tVector2D vec;
	//
	//if(m_fMoveTime <= 0.0f)
	//{
	//	m_fMoveTime = ((rand() % 200) / 100) + 0.5f;
	//	m_fRandRot = ((rand() % 1256) - 628) / 100;
	//}
	//	//m_fStopDelay = float(rand() % 100) / 100.0f + 0.5f;
	//if(m_fRandRot >= 0.01f)
	//{
	//	m_fRandRot -= 0.9f*fElapsedTime;
	//	vec = this->GetLook();
	//	vec = Vector2DRotate(vec,0.9f*fElapsedTime);
	//	this->SetLook(vec);
	//}
	//else if(m_fRandRot <= -0.01f)
	//{
	//	m_fRandRot += 0.09f*fElapsedTime;
	//	vec = this->GetLook();
	//	vec = Vector2DRotate(vec,-0.9f*fElapsedTime);
	//	this->SetLook(vec);
	//}



	//	int dir1 = rand() % 100;
	//	int dir2 = rand() % 100;
	//	if(dir1 > 50)
	//	{
	//		// move in x direction
	//		SetVelY(0);
	//		SetVelX(-50);
	//		if(dir2 > 50)
	//			SetVelX(50);
	//	}
	//	else
	//	{
	//		// move in y direction
	//		SetVelX(0);
	//		SetVelY(-50);
	//		if(dir2 > 50)
	//			SetVelY(50);

	//	}

	//}
}

void CHuman::Render(void)
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

type CHuman::CheckCollision(IBaseInterface* pBase)
{
	return CBase::CheckCollision(pBase);
}

void CHuman::HandleEvent(CEvent* pEvent)
{

}