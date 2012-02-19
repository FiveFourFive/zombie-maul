
#ifndef _CGAMEPLAYSTATE_H
#define _CGAMEPLAYSTATE_H

#include "IGameState.h"
#include "CBase.h"

#include "CObjectFactory.h"
#include "CMessageSystem.h"
#include "CEventSystem.h"
#include "CCapsule.h"
#include "Voices.h"

#include <string>
using std::string;
#include <vector>
#include <list>

class CBullet;
class CSGD_Direct3D;
class CSGD_DirectInput;
class CSGD_TextureManager;
class CSGD_FModManager;
class CObjectManager;
class CPrintFont;
class CCar;
class CBullet;
class CPlayer;
class CXboxInput;
class CSpeedRamp;
class ParticleManager;
class CEnemy;
class CHuman;
class CCollisionRect;
class CGuard;

class CGamePlayState : public IGameState
{

private:
	CSGD_Direct3D* m_pD3D;
	CSGD_DirectInput* m_pDI;
	CSGD_TextureManager* m_pTM;
	CSGD_FModManager* m_pFM;
	CMessageSystem* m_pMS;
	CEventSystem* m_pES;

	CObjectManager* m_pOM;
	CObjectFactory<string,CBase>* m_pOF;

	CXboxInput* m_pController1;
	CXboxInput* m_pController2;

	ParticleManager* m_pPM;		// The pointer to the particle manager.

	// font
	CPrintFont* m_pPF;
	CLevel* Level;
	RECT temp; // this is a temp rect that can be deleted when the camera is done

	// list for scores;
	std::vector<CCar*> m_lScores;
	
	// objects
	CPlayer* player;
	CEnemy* dummy;
	CSpeedRamp* speedy;
	CBullet* bullet;
	CHuman* hummy;

	// Guard Voices
	CVoices* guardVoice1;
	CVoices* guardVoice2;
	CVoices* guardVoice3;

	// sound
	int m_nBackgroundMusicID;
	int m_nIntroID;
	int m_nCountDown;
	int m_nCountDownEnd;

	// HUD ids
	int m_nLeftGuiID;
	int m_nRightGuiID;

	int m_nBGImageID;
	int m_nMinimapID;

	bool m_bTimePaused;
	float m_fPauseTimer;

	// spawning information
	bool m_bSpawnSideX;
	bool m_bSpawnSideY;
	float m_fSpawnTime;

	float time;		// total time, convert everything into seconds: 2 minutes = 120 seconds.
		// determine if a second has passed.

	int score;		// players score;

	CGamePlayState(void);
	~CGamePlayState(void){};
	CGamePlayState(const CGamePlayState&);
	CGamePlayState& operator = (const CGamePlayState&);

	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	bool HandleEnter(void);
	void RenderHUD();

	void SpawnHuman(void);
	void SpawnGuard(void);
public:

	std::vector<Capsule*> m_StoreWalls;

	CLevel* GetLevel () {return Level;}

	void Enter(void);
	void Exit(void);

	std::vector<CCar*>* GetList(void) { return &m_lScores; }

	static CGamePlayState* GetInstance();

	static void MessageProc(CBaseMessage* pMsg);
	void RenderMinimap();

	void InitializeGuardVoices(void);

	int GetScore() const					{ return score; }
	void SetScore( int nScore )				{ score = nScore; }
	void AddScore( int nScoreToAdd )		{ score += nScoreToAdd; }

	float GetGameTime() const					{ return time; }
	void SetGameTime( float fTime )			{ time = fTime; }
	void AddGameTime( float fTimeToAdd )	{ time += fTimeToAdd; }
	void LoseGameTime( float fTimeToLose )	{ time -= fTimeToLose; }

	bool GetIsTimePaused() const {return m_bTimePaused; }
	void SetIsTimePaused( bool bIsPaused )	{ m_bTimePaused = bIsPaused;}

	float GetPausedTimer() const {return m_fPauseTimer;}
	void SetPauseTimer( float fTime )	{m_fPauseTimer = fTime;}
};


#endif