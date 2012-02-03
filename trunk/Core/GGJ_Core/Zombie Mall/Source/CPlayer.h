#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "CEventSystem.h"
#include "IListener.h"
#include "CBase.h"

#include "Voices.h"

// ADDED FOR THE VOICE STUFF
#define PUN_TIME_RANGE_MIN 2
#define PUN_TIME_RANGE_MAX 10
/////////////////////////

class CMessageSystem;
class CSGD_FModManager;
class CSGD_DirectInput;

class CPlayer : public CBase
{
private:
	
	CEventSystem* m_pES;
	CSGD_FModManager* m_pFM;
	CSGD_DirectInput* m_pDI;

	CVoices* m_pVoice;
	CVoices* m_pAttackQuotes;
	CVoices* m_pDmgQuotes;

	float m_fInDelay;

	float m_fDelayTillNextPun;
	float m_fTimeBetweenPuns;

	int m_nAnimID;

	// sound id's
	int m_nWalkSound;
	int m_nEatingSound;
	int m_nMoanSound;

	Circle m_nCollisionWithStaticObjectsSphere;

public:
	CPlayer();
	~CPlayer(void);

	void Input( float fElapsedTime );
	void Update(float fElapsedTime);
	void Render(void);


	type CheckCollision(IBaseInterface* pBase);
	void HandleEvent(CEvent* pEvent);

	int GetAnimID() const	{ return m_nAnimID; }

	void SetAnimID( int nID )	{ m_nAnimID = nID; }

	Circle* GetSphere(){ return &m_nCollisionWithStaticObjectsSphere;}
};



#endif