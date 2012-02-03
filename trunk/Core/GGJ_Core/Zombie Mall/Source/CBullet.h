#ifndef _CBULLET_H
#define _CBULLET_H

#include "CBase.h"
class CEvent;
class CSGD_TextureManager;
class CSGD_FModManager;

class CBullet : public CBase
{

private:
	CSGD_FModManager* m_pFM;
	CSGD_TextureManager* m_pTM;

	char m_cDirX;
	char m_cDirY;

	short m_sSpeed;
	float m_fRot;

public:
	CBullet(void);
	~CBullet(void);

	void Update(float fElapsedTime);
	void Render(void);


	type CheckCollision(IBaseInterface* pBase);
	void SetDir(char x, char y){m_cDirX = x; m_cDirY = y; }
	void SetRot(float rot) { m_fRot = rot; }
	void HandleEvent(CEvent* pEvent);
	float GetRot(void) { return m_fRot; }

};





#endif