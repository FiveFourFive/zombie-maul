#ifndef _CROBOT_H
#define _CROBOT_H

#include "CBase.h"
#include "SGD_Math.h"

class CSGD_TextureManager;
class CEvent;

class CRobot : public CBase
{
private:
	CSGD_TextureManager* m_pTM;


	tVector2D m_pLookVector;
	tVector2D m_pShootVector;

	float m_sSpeed;

	int m_pID;



public:
	CRobot();
	~CRobot();

	void Update(float fElapsedTime);
	void Render(void);

	bool CheckCollision(IBaseInterface* pBase);

	RECT GetRect();

	void HandleEvent(CEvent* pEvent);
	void SetLook(tVector2D Vec);
	void SetShoot(tVector2D Vec);
	void GetShoot(char& x, char&y);
	void SetSpeed(float speed) {m_sSpeed = speed;}
};


#endif