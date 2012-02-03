/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	“CCamera.h”
//
// Author:	Ren Davis
// 
// Purpose: To allow movement across levels.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CCamera_h_
#define _CCamera_h_

class CCamera
{
private:

	float	m_fPosX;
	float	m_fPosY;

	int		m_nCamWidth;
	int		m_nCamHeight;

	CCamera();
	~CCamera();
	CCamera( const CCamera& );
	CCamera& operator=( const CCamera& );

public:
	///////////////////////////////////////////////////////////////////////////////////////
	//	Function:	"GetInstance"
	//
	//	Input:		void
	//
	//	Return:		Pointer to the singleton instance
	//
	//	Purpose:	Returns the only instance of the CCamera class 
	//				so that anyone can access the class and it's methods.
	///////////////////////////////////////////////////////////////////////////////////////
	static CCamera* GetInstance();

	///////////////////////////////////////////////////
	//	Function	:	Public Modifiers/Mutators
	//
	//	Purpose		:	To set the specified type.
	///////////////////////////////////////////////////
	void SetPosX( float fPosX )			{m_fPosX		= fPosX;}
	void SetPosY( float fPosY )			{m_fPosY		= fPosY;}
	void SetCamWidth( int nWidth )		{m_nCamWidth	= nWidth;}
	void SetCamHeight( int nHeight )	{m_nCamHeight	= nHeight;}

	///////////////////////////////////////////////////
	//	Function	:	Public Accessors
	//
	//	Purpose		:	To get the specified type.
	///////////////////////////////////////////////////
	float GetPosX() const		{return m_fPosX;}
	float GetPosY() const		{return m_fPosY;}
	int   GetCamWidth() const	{return m_nCamWidth;}
	int   GetCamHeight() const	{return m_nCamHeight;}
};

#endif