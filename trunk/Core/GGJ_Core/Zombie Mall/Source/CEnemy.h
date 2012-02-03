#ifndef _CENEMY_H
#define _CENEMY_H

#include "CBase.h"

class CEvent;

class CEnemy : public CBase
{

private:
	/*float m_fMovementDelay;
	float m_fMovementTime;

	bool m_bMovement;
	float m_fMovementIncreaseDelay;*/

	float m_fMoveTime;
	float m_fStopDelay;
	float m_fRandRot;

public:
	CEnemy(void);
	~CEnemy(void);

	void Update(float fElapsedTime);
	void Render(void);

	type CheckCollision(IBaseInterface* pBase);

	void HandleEvent(CEvent* pEvent);

	void ComputeMovement(float fElapsedTime);

	void SetMoveTime( float time) { m_fMoveTime = time;}
	void SetStopDelay(float delay){ m_fStopDelay = delay;}
	void SetRandRot(float rot){ m_fRandRot = rot;}

	float GetMoveTime(){ return m_fMoveTime;}
	float GetStopDelay() { return m_fStopDelay;}
	float GetRandRot() { return m_fRandRot;}
	void addTime(float time) { m_fMoveTime = m_fMoveTime + time; }
};

#endif