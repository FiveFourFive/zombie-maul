#include "CEnemy.h"
#include "CGame.h"
#include "CPlayer.h"
#include <ctime>

#include "CSGD_TextureManager.h"

CEnemy::CEnemy(void)
{
	/*m_bMovement = true;
	SetPosX(100);
	SetPosY(100);
	tVector2D vec;
	vec.fX = 0;
	vec.fY = 0;
	SetLook(vec);
	SetSpeed(700);
	m_fMovementDelay = 0.5f;
	m_fMovementTime = 0;*/

	SetPosX(400);
	SetPosY(30);
	m_fMoveTime = 0;
	m_fStopDelay = 0;
	tVector2D look = tVector2D(0.0f, -1.0f);
	SetLook(look);
	m_fRandRot = 0.0f;
	SetSpeed(130);

	m_nType = type::OBJECT_NONE;
}

CEnemy::~CEnemy(void)
{

}

void CEnemy::Update(float fElapsedTime)
{
	/*m_fMovementTime += fElapsedTime;
	m_fMovementIncreaseDelay += fElapsedTime;
	if(m_fMovementIncreaseDelay > 1.0f && m_fMovementDelay >= 0.01f)
	{
		m_fMovementIncreaseDelay = 0;
		m_fMovementDelay -= 0.01f;
	}
	tVector2D Vec;
	Vec.fX = 0;
	Vec.fY = 0;
	SetLook(Vec);
	if(m_fMovementTime >= m_fMovementDelay)
	{
		ComputeMovement();
		m_bMovement = !m_bMovement;
		m_fMovementTime = 0;
	}*/

	m_fMoveTime -= fElapsedTime;
	ComputeMovement(fElapsedTime);

	CBase::Update(fElapsedTime);

}

void CEnemy::Render(void)
{
	CBase::Render();

}

void CEnemy::ComputeMovement(float fElapsedTime)
{
	/*short playerPosX = CGame::GetInstance()->GetPlayer()->GetCenterPosX();
	short playerPosY = CGame::GetInstance()->GetPlayer()->GetCenterPosY();

	short pathxorig = GetCenterPosX()-playerPosX;
	short pathyorig = GetCenterPosY() -playerPosY;

	tVector2D Vec;*/
	/*short pathx = 0;
	short pathy = 0;
	if(abs(pathxorig) > abs(pathxorig))
	{
		
		if(pathxorig > 0)
			pathx = 1;
		else
			pathx = -1;
	}
	else
	{
		
		if(pathxorig > 0)
			pathy = -1;
		else
			pathy = 1;
	}*/
	
	//if(m_bMovement)
	//	{
	//if(pathxorig != 0)
	//{
	//	
	//	//	m_bMovement = !m_bMovement;
	//	if(pathxorig < 0)
	//		Vec.fX = pathxorig/pathxorig;
	//	else
	//		Vec.fX = pathxorig/pathxorig * -1;
	//	}
	//	else
	//		Vec.fX = 0;
	//}
	//if(!m_bMovement)
	//	{
	//if(pathyorig != 0)
	//{
	//	
	//	//	m_bMovement = !m_bMovement;
	//	if(pathyorig < 0)
	//		Vec.fY = pathyorig/pathyorig;
	//	else
	//		Vec.fY = pathyorig/pathyorig * -1;
	//	}
	//	else
	//		Vec.fY = 0;
	//}
	//
	//Vec.fX *= rand() % 4 + 40;
	//Vec.fY *= rand() % 4 + 40;
	//SetLook(Vec);

	// Updates movement to wander
	m_fStopDelay -= fElapsedTime;
	tVector2D vec;
	
	if(m_fMoveTime <= 0.0f)
	{
		m_fMoveTime = ((rand() % 200) / 100.0f) + 0.5f;
		m_fRandRot = (float)((rand() % 1256) - 628) / 100.0f;
	}
	if(m_fRandRot >= 0.01f)
	{
		m_fRandRot -= 0.9f*fElapsedTime;
		this->SetRotation(this->GetRotation() + 0.9f*fElapsedTime);
		vec = this->GetLook();
		vec = Vector2DRotate(vec,0.9f*fElapsedTime);
	//	SetRot(GetRot() - AngleBetweenVectors(GetLook(), vec));
		this->SetLook(vec);
	}
	else if(m_fRandRot <= -0.01f)
	{
		m_fRandRot += 0.09f*fElapsedTime;
		this->SetRotation(this->GetRotation() - 0.9f*fElapsedTime);
		vec = this->GetLook();
		vec = Vector2DRotate(vec,-0.9f*fElapsedTime);
		//SetRot(GetRot() + AngleBetweenVectors(GetLook(), vec));
		this->SetLook(vec);
	}
}

type CEnemy::CheckCollision(IBaseInterface* pBase)
{

	return type::OBJECT_NONE;
}

void CEnemy::HandleEvent(CEvent* pEvent)
{

}