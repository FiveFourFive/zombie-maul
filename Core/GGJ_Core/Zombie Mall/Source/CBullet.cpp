#include "CBullet.h"

#include "CSGD_TextureManager.h"
#include "CSGD_FModManager.h"
#include "CSGD_Direct3D.h"
CBullet::CBullet(void)
{
	m_cDirX = 0;
	m_cDirY = 1;
	m_sSpeed = 600;
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pFM = CSGD_FModManager::GetInstance();
	
	SetImageID(m_pTM->LoadTexture("resource/bullet.png",D3DCOLOR_XRGB(255,0,255)));
	SetWidth(m_pTM->GetTextureWidth(GetImageID()));
	SetHeight(m_pTM->GetTextureHeight(GetImageID()));
}

CBullet::~CBullet(void)
{

}

void CBullet::Update(float fElapsedTime)
{
	SetPosX(GetPosX() + (m_sSpeed * m_cDirX * fElapsedTime));
	SetPosY(GetPosY() + (m_sSpeed * m_cDirY * fElapsedTime));
}

void CBullet::Render(void)
{
	RECT r;
	r.left = (int)GetCenterPosX();
	r.top = (int)GetCenterPosY();
	r.right = r.left + GetWidth();
	r.bottom = r.top + GetHeight();
	m_pTM->Draw(GetImageID(),(int)GetPosX(),(int)GetPosY(),1.0f,1.0f,NULL,(float)(GetWidth()/2.0f),(float)(GetHeight()/2.0f),GetRot());
	CSGD_Direct3D::GetInstance()->DrawRect(r,255,0,0);
}




type CBullet::CheckCollision(IBaseInterface* pBase)
{
	return type::OBJECT_NONE;
}

void CBullet::HandleEvent(CEvent* pEvent)
{

}
