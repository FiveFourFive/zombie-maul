/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	“AnimationManager.h”
//
// Author:	Ren Davis
// 
// Purpose: Class that handles animations of game objects.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _AnimationManager_h_
#define _AnimationManager_h_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <vector>

class AnimManager
{
private:
	struct AnimFrame
	{
		RECT	rImageRect;
		float	fDuration;

		AnimFrame();
	};

	struct Animation
	{
	private:
		char*					szAnimName;

	public:
		std::vector<AnimFrame>	vAnimFrames;
		bool					bIsLooping;

		Animation();
		~Animation();

		Animation( const Animation& anim );
		Animation& operator=( const Animation& anim );

		void SetAnimName( const char* szName );

		char const* GetAnimName() const		{ return szAnimName; }
	};

	struct AnimSheet
	{
		std::vector<Animation>	vAnimations;
		int						nImageID;

		AnimSheet();
	};

	struct AnimObj
	{
	public:
		float			fCurTime;
		float			fAnimSpeed;
		UINT			uiCurFrame;
		int				nCurAnim;
		int				nCurSheet;
		bool			bIsPlaying;

		AnimObj();

		void Play();
		void Stop();
		void Resume();
		void Reset();
	};

	static AnimManager*		m_pInstance;

	std::vector<AnimSheet>	m_vAnimSheets;
	std::vector<AnimObj>	m_vAnimObjs;

	AnimManager();
	~AnimManager();
	AnimManager( const AnimManager& );
	AnimManager& operator=( const AnimManager& );

public:
	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"GetInstance"
	//
	//	Input:		void
	//
	//	Return:		Pointer to the singleton instance
	//
	//	Purpose:	Returns the only instance of the CGame class 
	//				so that anyone can access the class and it's methods.
	///////////////////////////////////////////////////////////////////////////////////////
	static AnimManager* GetInstance();

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"DeleteInstance"
	//
	//	Input:		void
	//
	//	Return:		void
	//
	//	Purpose:	Deletes the instance and cleans up all resources used by the class.
	///////////////////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"PlayAnimation"
	//
	//	Input:		nAnimID	-	The ID for the animation instance
	//
	//	Return:		void
	//
	//	Purpose:	Sets the given animation with the given id to play its animation.
	///////////////////////////////////////////////////////////////////////////////////////
	void PlayAnimation( int nAnimID );

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"StopAnimation"
	//
	//	Input:		nAnimID	-	The ID for the animation instance
	//
	//	Return:		void
	//
	//	Purpose:	Sets the given animation with the given id to stop its animation.
	///////////////////////////////////////////////////////////////////////////////////////
	void StopAnimation( int nAnimID );

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"ResumeAnimation"
	//
	//	Input:		nAnimID	-	The ID for the animation instance
	//
	//	Return:		void
	//
	//	Purpose:	Sets the given animation with the given id to resume
	//				its animation at its present frame.
	///////////////////////////////////////////////////////////////////////////////////////
	void ResumeAnimation( int nAnimID );

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"ResetAnimation"
	//
	//	Input:		nAnimID	-	The ID for the animation instance
	//
	//	Return:		void
	//
	//	Purpose:	Sets the given animation with the given id to reset 
	//				its animation back to the first frame.
	///////////////////////////////////////////////////////////////////////////////////////
	void ResetAnimation( int nAnimID );

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"LoadAnimation"
	//
	//	Input:		szFilePath	-	The name of the file path for the 
	//								animation to load
	//
	//	Return:		id for the animation instance
	//
	//	Purpose:	Loads an animation from a file and creates an animation instance and 
	//				returns the id to the instance.
	///////////////////////////////////////////////////////////////////////////////////////
	int LoadAnimation( const char* szFilePath );

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"Update"
	//
	//	Input:		fElapsedTime	-	The time passed since the last frame
	//
	//	Return:		void
	//
	//	Purpose:	Updates any animation that is playing.
	///////////////////////////////////////////////////////////////////////////////////////
	void Update( float fElapsedTime );

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"Render"
	//
	//	Input:		nAnimID	-	The ID for the animation instance
	//				nPosX	-	The X coordinate for the image
	//				nPosY	-	The Y coordinate for the image
	//				fScaleX	-	The percentage to scale on the X axis
	//				fScaleY	-	The percentage to scale on the Y axis
	//
	//	Return:		void
	//
	//	Purpose:	Renders the given animation at the position and 
	//				scaling aplied.
	///////////////////////////////////////////////////////////////////////////////////////
	void Render( int nAnimID, int nPosX, int nPosY, float fScaleX = 1.0f, float fScaleY = 1.0f, float fRot = 0.0f ) const;

	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"SetAnimation"
	//
	//	Input:		nAnimID	-	The ID for the animation instance
	//				szAnim	-	The name of the animation to change to
	//
	//	Return:		void
	//
	//	Purpose:	Changes the animation to the animation name specified.
	///////////////////////////////////////////////////////////////////////////////////////
	void SetAnimation( int nAnimID, const char* szAnim );
};

#endif