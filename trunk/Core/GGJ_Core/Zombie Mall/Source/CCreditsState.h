
#ifndef _CCreditsState_h_
#define _CCreditsState_h_

#include "IGameState.h"

#include <vector>
#include <string>

class CPrintFont;

class CCreditsState : public IGameState
{
private:

	std::vector<std::string>	m_vNames;

	// font
	CPrintFont* m_pPF;

	int m_nBGImageID;

	CCreditsState();
	~CCreditsState();
	CCreditsState( const CCreditsState& );
	CCreditsState& operator=( const CCreditsState& );

	int m_nStartingY;
	int m_nEndingY;
	float* m_pYPos;

public:
	static CCreditsState* GetInstance();

	void Enter();

	bool Input();

	void Update( float fElapsedTime );

	void Render();

	void Exit();

	bool HandleEnter();
};

#endif