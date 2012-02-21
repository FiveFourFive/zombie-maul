
#ifndef _CLoadState_h_
#define _CLoadState_h_

#include "IGameState.h"

class CPrintFont;

class CLoadState : public IGameState
{
private:

	// font
	CPrintFont* m_pPF;

	int m_nBGImageID;
	int m_nOuroboroID;
	float m_fRotation;

	CLoadState();
	~CLoadState();
	CLoadState( const CLoadState& );
	CLoadState& operator=( const CLoadState& );

public:
	static CLoadState* GetInstance();

	void Enter();

	bool Input();

	void Update( float fElapsedTime );

	void Render();

	void Exit();

	bool HandleEnter();
};

#endif