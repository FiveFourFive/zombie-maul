
#ifndef _CEndGameState_h_
#define _CEndGameState_h_

#include "IGameState.h"

class CPrintFont;

class CEndGameState : public IGameState
{
private:

	// font
	CPrintFont* m_pPF;

	int m_nBGImageID;

	CEndGameState();
	~CEndGameState();
	CEndGameState( const CEndGameState& );
	CEndGameState& operator=( const CEndGameState& );

public:
	static CEndGameState* GetInstance();

	void Enter();

	bool Input();

	void Update( float fElapsedTime );

	void Render();

	void Exit();

	bool HandleEnter();
};

#endif