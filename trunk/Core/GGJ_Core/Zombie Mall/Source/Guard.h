#ifndef _CGUARD_H
#define _CGUARD_H

#include "CEnemy.h"
#include "SGD_Math.h"

#include "Voices.h"

class CEvent;
class CPlayer;

class CGuard :	public CEnemy
{

private:
	CPlayer* pPlayer;
	bool IsUndead;

	int m_nAnimID;

	Circle m_nCollisionWithStaticObjectsSphere;

	CVoices* m_pVoice;

public:
	CGuard(void);
	~CGuard(void);

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

	CPlayer* GetpPlayer(void) { return pPlayer; }
	void SetpPlayer(CPlayer* player) { pPlayer = player; }

	bool CheckForPlayer(void);
	void HuntPlayer(void);

	// Lol, little mermaid referrence
	void TakeBackYourLegs(CVoices* voice);
};

#endif // _CGUARD_H