#include "CRobot.h"
#include "CEvent.h"
#include "CSGD_TextureManager.h"
#include "CSGD_Direct3D.h"
CRobot::CRobot()
{
	m_sSpeed = 200;
	SetPosX(300);
	SetPosY(300);
	m_pTM = CSGD_TextureManager::GetInstance();
	SetImageID(m_pTM->LoadTexture("resource/character.bmp",D3DCOLOR_XRGB(255,255,255)));
	SetWidth(m_pTM->GetTextureWidth(GetImageID()));
	SetHeight(m_pTM->GetTextureHeight(GetImageID()));
}

CRobot::~CRobot()
{

}
void CRobot::Update(float fElapsedTime)
{
	SetPosX(GetPosX() + (m_pLookVector.fX * m_sSpeed * fElapsedTime));
	SetPosY(GetPosY() + (m_pLookVector.fY * m_sSpeed * fElapsedTime));

}
void CRobot::Render(void)
{

	RECT r;
	r.left = GetCenterPosX();
	r.top = GetCenterPosY();
	r.right = r.left + GetWidth()/2;
	r.bottom = r.top + GetHeight()/2;
	m_pTM->Draw(GetImageID(),GetPosX(),GetPosY());
	CSGD_Direct3D::GetInstance()->DrawRect(r,255,0,0);
}

bool CRobot::CheckCollision(IBaseInterface* pBase)
{
	return false;
}

RECT CRobot::GetRect()
{
	RECT out;
	return out;
}

void CRobot::HandleEvent(CEvent* pEvent)
{

}
void CRobot::SetLook(tVector2D Vec)
{
	m_pLookVector = Vec;
}
void CRobot::SetShoot(tVector2D Vec)
{
	m_pShootVector = Vec;
}

void CRobot::GetShoot(char& x, char&y)
{
	x = m_pShootVector.fX;
	y = m_pShootVector.fY;
}