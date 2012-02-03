#ifndef AUDIO_H_
#define AUDIO_H_

#include "IGameState.h"

class CSGD_TextureManager;
class CSGD_FModManager;
class CSGD_DirectInput;
class CPrintFont;
class CXboxInput;

class CAudioState : public IGameState 
{
	private:
	CSGD_TextureManager* m_pTM;
	CSGD_FModManager* m_pFM;
	CSGD_DirectInput* m_pDI;
	CPrintFont* m_pPF;

	int	m_nFontID;
	int m_nBackgroundMusicID;
	int m_nSelection;
	int arrowID;

	// Sounds
	int m_nMenuMove;
	int m_nMenuSelect;
	int m_nMenuCancel;

	CAudioState();
	~CAudioState();
	CAudioState( const CAudioState&);
	CAudioState& operator = (const CAudioState&);

	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	bool HandleEnter(void);

public:
	static CAudioState* GetInstance();

	void Enter(void);
	void Exit(void);

	int GetFontID(void) { return m_nFontID; }
	int GetBackgroundMusicID(void) { return m_nBackgroundMusicID; }

	bool Save( const char* szFileName);
};

#endif