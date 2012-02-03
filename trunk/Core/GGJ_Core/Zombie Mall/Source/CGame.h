
/////////////////////////////////////////////////////////
//	File Name : "CGame.h"
//	Author Name : Wade Shwallon
//	Purpose : contains all game related code
/////////////////////////////////////////////////////////

#ifndef _CGAME
#define _CGAME

#include "CStopWatch.h"
#include <vector>
class CPlayer;
using namespace std;
class CSGD_Direct3D;
class CSGD_TextureManager;
class CMainMenuState;
class IGameState;
class CSGD_FModManager;
class CSGD_DirectInput;
class CXboxInput;
class CGame
{
private:

	// Singleton Pointers
	CSGD_Direct3D*			m_pD3D;
	CSGD_TextureManager*	m_pTM;
	CSGD_FModManager*		m_pFM;
	CSGD_DirectInput*		m_pDI;

	// player
	CPlayer* m_pPlayer1;

	//controller input
	CXboxInput*				m_pController1;
	CXboxInput*				m_pController2;
	bool m_bController;

	// States
	IGameState*				m_pGameState;
	CMainMenuState*			m_pMainMenuState;
	vector<IGameState*>		m_vGameStates;
	float m_fInputDelay;
	float m_fThumbDelay;

	// Sound
	int						m_nSoundAVolume;
	int						m_nSoundBVolume;
	int						m_panning;

	// Time
	CStopWatch				m_stopWatch;
	float					m_fElapsedTime;

	//Screen stuffs
	int						m_ScreenWidth;
	int						m_ScreenHeight;

	int						m_nScore;

	int m_nMenuSelection;
	int m_nMenuMove;
	int m_nMenuCancel;

	CGame();
	~CGame();
	CGame(const CGame& game);
	CGame& operator =(const CGame& game);

	// Utility functions
	bool Input();
	void Update(float fElapsedTime);
	void Render();

public:
	static CGame* GetInstance();

	// Initialization
	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);

	// manage states
	void ChangeState(IGameState* state);
	void AddState(IGameState* state);
	void RemoveState();
	void ClearStates();

	int GetMenuSelectID() { return m_nMenuSelection; }
	int GetMenuMoveID() { return m_nMenuMove; }
	int GetMenuCancelID() { return m_nMenuCancel; }

	CXboxInput* GetController1(void) { return m_pController1; }
	CXboxInput* GetController2(void) { return m_pController2; }
	bool ControllerInput(void) { return m_bController; }
	float GetInputDelay(void) { return m_fInputDelay; }
	void ResetInputDelay(void) { m_fInputDelay = 0.0f; }
	float GetThumbDelay(void) { return m_fThumbDelay; }
	void ResetThumbDelay(void) { m_fThumbDelay = 0.0f; }
	int GetScreenWidth() { return m_ScreenWidth;}
	int GetScreenHeight(){ return m_ScreenHeight;}
	float GetElapsedTime(void){return m_fElapsedTime;}
	int getSoundAVolume();
	int getSoundBVolume();

	void SetSoundAVolume(int newvol);
	void SetSoundBVolume(int newvol);

	int getPanning();

	void SetPanning(int left);

	// player info
	CPlayer* GetPlayer(void);
	void SetPlayer(CPlayer* player);


	// Execution
	// returns false when game should quit
	bool Main();

	void SetScore(int score) { m_nScore = score; }
	int GetScore() { return m_nScore; }

	bool Load(const char* szFileName);

	// Clean Up
	void Shutdown();	
};

#endif