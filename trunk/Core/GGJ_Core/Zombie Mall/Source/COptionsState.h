#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "IGameState.h"

class CSGD_TextureManager;
class CSGD_FModManager;
class CSGD_DirectInput;
class CPrintFont;
class CXboxInput;

class COptionsState : public IGameState
{
private:
	CSGD_TextureManager* m_pTM;
	CSGD_FModManager* m_pFM;
	CSGD_DirectInput* m_pDI;
	CPrintFont* m_pPF;

	int	m_nFontID;
	int m_nBackgroundMusicID;
	int m_nBGImageID;
	int m_nSelection;
	int m_nMenuMove;
	int m_nMenuSelection;
	int m_nMenuCancel;

	COptionsState();
	~COptionsState();
	COptionsState( const COptionsState&);
	COptionsState& operator = (const COptionsState&);

	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	bool HandleEnter(void);

public:
	static COptionsState* GetInstance();

	void Enter(void);
	void Exit(void);

	int GetFontID(void) { return m_nFontID; }
	int GetBackgroundMusicID(void) { return m_nBackgroundMusicID; }
};



#endif