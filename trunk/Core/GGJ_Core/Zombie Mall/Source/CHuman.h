#ifndef _CHUMAN_H
#define _CHUMAN_H

#include "CEnemy.h"
#include "SGD_Math.h"

class CEvent;

class CHuman : public CEnemy
{

private:
	bool IsUndead;

	int m_nAnimID;

	Circle m_nCollisionWithStaticObjectsSphere;

public:
	CHuman(void);
	~CHuman(void);

	void Update(float fElapsedTime);
	void Render(void);

	void ComputeMovement(float fElapsedTime);
	type CheckCollision(IBaseInterface* pBase);

	void HandleEvent(CEvent* pEvent);

	int GetAnimID() const	{ return m_nAnimID; }

	void SetAnimID( int nID )	{ m_nAnimID = nID; }

	bool GetIsUndead() const { return IsUndead; }

	void SetIsUndead( bool bIsUndead )	{ IsUndead = bIsUndead; }

	Circle* GetSphere(){ return &m_nCollisionWithStaticObjectsSphere;}
};




#endif