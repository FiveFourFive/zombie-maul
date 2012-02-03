/////////////////////////////////////////////////////////
//	File Name	: "CBase.cpp"
//	Author Name : Wade Shwallon
//	Purpose		: Contains base functionality for game objects
/////////////////////////////////////////////////////////

#include "CBase.h"
#include "CSGD_TextureManager.h"
//#include "SGD Wrappers\CSGD_FModManager.h"
#include "CGame.h"
#include "CSGD_Direct3D.h"
#include "CCamera.h"
#include "SimpleWorldClamp.h"

bool Circle::CheckCollision( Circle& test )
{
	tVector2D dist;
	dist.fX = test.m_Center.fX - this->m_Center.fX;
	dist.fY = test.m_Center.fY - this->m_Center.fY;

	// ERROR CHECK -- IF THEY ARE SHARING THE SAME EXACT POSITION, SKIP THIS COLLISION
	if (dist.fX == 0.0f && dist.fY == 0.0f)
		return false;

	if( DotProduct( dist, dist ) <= (test.m_fRadius + this->m_fRadius) * (test.m_fRadius + this->m_fRadius) )
	{
		dist = Vector2DNormalize( dist );
		this->m_Center = test.m_Center - (dist * (this->m_fRadius + test.m_fRadius));

		return true;
	}

	return false;
}

CBase::CBase()
{
	m_uiRefCount = 1; // start with a ref to yourself!!
	SetPosX(0);
	SetPosY(0);
	SetRot(0.0f);
	SetImageID(-1);
	SetWidth(100);
	SetHeight(150);
	//m_nExplosionID = CSGD_FModManager::GetInstance()->LoadSound("resource/sound/Explosion.mp3");
	//CSGD_FModManager::GetInstance()->SetVolume(m_nExplosionID,CGame::getInstance()->getSoundAVolume());
	m_nName[32];
	m_nType = type::OBJECT_NONE;
	m_fSpeed = 0.0f;
	m_fTotalRot = 3.14f;
	
}

CBase::~CBase()
{

}

void CBase::Update(float fElapsedTime)
{
	m_nPosX = m_nPosX + (GetDirX() * m_fSpeed * fElapsedTime);
	m_nPosY = m_nPosY + (GetDirY() * m_fSpeed * fElapsedTime);
	if(this->GetRotation() >= 6.28)
		this->SetRotation(0.0f);
	if(this->GetRotation() <= -6.28)
		this->SetRotation(0.0f);
	//SimpleWorldClamping( *this );
}


void CBase::Render()
{
	CSGD_TextureManager::GetInstance()->Draw(GetImageID(),
		(int)(GetCenterPosX() - CCamera::GetInstance()->GetPosX()), (int)(GetCenterPosY() - CCamera::GetInstance()->GetPosY()));
}

Circle CBase::GetCollisionVolume()
{
	Circle bounds;
	bounds.m_Center.fX = GetCenterPosX();
	bounds.m_Center.fY = GetCenterPosY();
	bounds.m_fRadius = GetWidth() / 2.0f;

	return bounds;

	//RECT tempRect = { (LONG)GetPosX(), (LONG)GetPosY(), (LONG)(GetPosX() + GetWidth()), (LONG)(GetPosY() + GetHeight()) };
	//return tempRect;
}

type CBase::CheckCollision(IBaseInterface* pBase)
{
	Circle temp = this->GetCollisionVolume();
	if(temp.CheckCollision( pBase->GetCollisionVolume() ))
	{
		this->SetPosX(temp.m_Center.fX - this->GetWidth()/2);
		this->SetPosY(temp.m_Center.fY - this->GetHeight()/2);
		//return true;
		return pBase->GetType();
	}
	//return false;
	return OBJECT_NONE;

	/*RECT intersection;

	if(IntersectRect(&intersection, &GetRect(), &pBase->GetRect()))
		return true;
	return false;*/
}

void CBase::SetName(char* name)
{
	strcpy_s(m_nName,32,name);
}
char* CBase::GetName()
{
	return m_nName;
}