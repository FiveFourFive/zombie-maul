/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	“AnimationManager.cpp”
//
// Author:	Ren Davis
// 
// Purpose: Class that handles animations of game objects.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AnimationManager.h"

#include "tinyxml.h"
#include "CSGD_TextureManager.h"

#ifdef DEBUG
	// For debugging purposes
	#include <assert.h>
#endif

AnimManager* AnimManager::m_pInstance = NULL;

///////////////////////////////////////////////////
// AnimFrame
///////////////////////////////////////////////////
AnimManager::AnimFrame::AnimFrame()
{
	fDuration = 0.0f;
}

///////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////
AnimManager::Animation::Animation()
{
	szAnimName = NULL;
	bIsLooping = false;
}

AnimManager::Animation::~Animation()
{
	free( szAnimName );
}

AnimManager::Animation::Animation( const Animation& anim )
{
	const size_t LEN = strlen(anim.GetAnimName()) + 1;

	szAnimName = (char*)malloc( LEN );
	strcpy_s( szAnimName, LEN, anim.GetAnimName() );

	vAnimFrames = anim.vAnimFrames;

	bIsLooping = anim.bIsLooping;
}

AnimManager::Animation& AnimManager::Animation::operator=( const Animation& anim )
{
	if( this != &anim )
	{
		SetAnimName( anim.GetAnimName() );

		vAnimFrames = anim.vAnimFrames;

		bIsLooping = anim.bIsLooping;
	}

	return *this;
}

void AnimManager::Animation::SetAnimName( const char* szName )
{
	free( szAnimName );

	const size_t LEN = strlen(szName) + 1;

	szAnimName = (char*)malloc( LEN );
	strcpy_s( szAnimName, LEN, szName );
}

///////////////////////////////////////////////////
// AnimSheet
///////////////////////////////////////////////////
AnimManager::AnimSheet::AnimSheet()
{
	nImageID = -1;
}

///////////////////////////////////////////////////
// AnimObj
///////////////////////////////////////////////////
AnimManager::AnimObj::AnimObj()
{
	fCurTime = 0.0f;
	fAnimSpeed = 1.0f;

	uiCurFrame = 0;
	nCurAnim = NULL;
	nCurSheet = NULL;

	bIsPlaying = false;
}

void AnimManager::AnimObj::Play()
{
	Reset();
	Resume();
}

void AnimManager::AnimObj::Stop()
{
	bIsPlaying = false;
}

void AnimManager::AnimObj::Resume()
{
	bIsPlaying = true;
}

void AnimManager::AnimObj::Reset()
{
	fCurTime = 0.0f;
	uiCurFrame = 0;
}

///////////////////////////////////////////////////
// AnimManager
///////////////////////////////////////////////////
AnimManager::AnimManager()
{

}

AnimManager::~AnimManager()
{
	m_vAnimSheets.clear();
	m_vAnimObjs.clear();
}

AnimManager* AnimManager::GetInstance()
{
	if( m_pInstance == NULL )
		m_pInstance = new AnimManager();

	return m_pInstance;
}

void AnimManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = NULL;
}

void AnimManager::PlayAnimation( int nAnimID )
{
#ifdef DEBUG
	assert( nAnimID > -1 && nAnimID < (int)m_vAnimObjs.size() && "nAnimID is out of range." );
#endif

	m_vAnimObjs[nAnimID].Play();
}

void AnimManager::StopAnimation( int nAnimID )
{
#ifdef DEBUG
	assert( nAnimID > -1 && nAnimID < (int)m_vAnimObjs.size() && "nAnimID is out of range." );
#endif

	m_vAnimObjs[nAnimID].Stop();
}

void AnimManager::ResumeAnimation( int nAnimID )
{
#ifdef DEBUG
	assert( nAnimID > -1 && nAnimID < (int)m_vAnimObjs.size() && "nAnimID is out of range." );
#endif

	m_vAnimObjs[nAnimID].Resume();
}

void AnimManager::ResetAnimation( int nAnimID )
{
#ifdef DEBUG
	assert( nAnimID > -1 && nAnimID < (int)m_vAnimObjs.size() && "nAnimID is out of range." );
#endif

	m_vAnimObjs[nAnimID].Reset();
}

int AnimManager::LoadAnimation( const char* szFilePath )
{
	TiXmlDocument doc;

	if( doc.LoadFile( szFilePath ) == false )
		return -1;

	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == NULL )
		return -1;

	AnimSheet sheet;

	const char* szImageName = pRoot->Attribute( "animSheet" );
	if( szImageName != NULL )
		sheet.nImageID = CSGD_TextureManager::GetInstance()->LoadTexture( szImageName );

	TiXmlElement* pAnimation = pRoot->FirstChildElement( "Animation" );
	while( pAnimation != NULL )
	{
		Animation anim;

		const char* szAnimName = pAnimation->Attribute( "animName" );
		if( szAnimName != NULL )
			anim.SetAnimName( szAnimName );

		const char* szIsLooping = pAnimation->Attribute( "isLooping" );
		if( szIsLooping != NULL )
		{
			if( strcmp( szIsLooping, "true" ) == 0 )
				anim.bIsLooping = true;
		}

		TiXmlElement* pFrame = pAnimation->FirstChildElement( "Frame" );
		while( pFrame != NULL )
		{
			AnimFrame frame;

			double dTime;
			if( pFrame->Attribute( "frameTime", &dTime ) )
				frame.fDuration = (float)dTime;

			TiXmlElement* pImageRect = pFrame->FirstChildElement( "ImageRect" );
			if( pImageRect != NULL )
			{
				int nLeft, nTop, nRight, nBottom;
				if( pImageRect->Attribute( "left", &nLeft ) )
					frame.rImageRect.left = nLeft;

				if( pImageRect->Attribute( "top", &nTop ) )
					frame.rImageRect.top = nTop;

				if( pImageRect->Attribute( "right", &nRight ) )
					frame.rImageRect.right = nRight;

				if( pImageRect->Attribute( "bottom", &nBottom ) )
					frame.rImageRect.bottom = nBottom;
			}

			anim.vAnimFrames.push_back( frame );
			pFrame = pFrame->NextSiblingElement( "Frame" );
		}
		anim.vAnimFrames.shrink_to_fit();

		sheet.vAnimations.push_back( anim );
		pAnimation = pAnimation->NextSiblingElement( "Animation" );
	}
	sheet.vAnimations.shrink_to_fit();

	m_vAnimSheets.push_back( sheet );

	AnimObj animObj;
	animObj.nCurSheet = m_vAnimSheets.size() - 1;
	animObj.nCurAnim = 0;
	m_vAnimObjs.push_back( animObj );

	return (int)m_vAnimObjs.size() - 1;
}

void AnimManager::Update( float fElapsedTime )
{
	for( std::vector<AnimObj>::size_type curAnimObj = 0; curAnimObj < m_vAnimObjs.size(); ++curAnimObj )
	{
		if( m_vAnimObjs[curAnimObj].bIsPlaying )
		{
			AnimObj& animObj = m_vAnimObjs[curAnimObj];
			animObj.fCurTime += fElapsedTime * animObj.fAnimSpeed;
			if( animObj.fCurTime >= m_vAnimSheets[animObj.nCurSheet].vAnimations[animObj.nCurAnim].vAnimFrames[animObj.uiCurFrame].fDuration)//animObj.pCurAnim->vAnimFrames[animObj.uiCurFrame].fDuration )
			{
				if( ++animObj.uiCurFrame >= m_vAnimSheets[animObj.nCurSheet].vAnimations[animObj.nCurAnim].vAnimFrames.size() )
				{
					if( m_vAnimSheets[animObj.nCurSheet].vAnimations[animObj.nCurAnim].bIsLooping )
						animObj.Reset();
					else
					{
						animObj.Stop();
						animObj.uiCurFrame = m_vAnimSheets[animObj.nCurSheet].vAnimations[animObj.nCurAnim].vAnimFrames.size() - 1;
					}
				}

				animObj.fCurTime = 0.0f;
			}
		}
	}
}

void AnimManager::Render( int nAnimID, int nPosX, int nPosY, float fScaleX, float fScaleY, float fRot ) const
{
#ifdef DEBUG
	assert( nAnimID > -1 && nAnimID < (int)m_vAnimObjs.size() && "nAnimID is out of range." );
#endif

	const AnimObj& animObj = m_vAnimObjs[nAnimID];
	RECT rImage = m_vAnimSheets[animObj.nCurSheet].vAnimations[animObj.nCurAnim].vAnimFrames[animObj.uiCurFrame].rImageRect;
	LONG width = (rImage.right - rImage.left);
	LONG height = (rImage.bottom - rImage.top);
	CSGD_TextureManager::GetInstance()->Draw( m_vAnimSheets[animObj.nCurSheet].nImageID, (int)(nPosX-(width/2)*fScaleX), (int)(nPosY-(height/2)*fScaleY), fScaleX, fScaleY, &rImage, (float)(width/2.0f), (float)(height/2.0f), fRot );
}

void AnimManager::SetAnimation( int nAnimID, const char* szAnim )
{
#ifdef DEBUG
	assert( nAnimID > -1 && nAnimID < (int)m_vAnimObjs.size() && "nAnimID is out of range." );
#endif
	const AnimObj& animObj = m_vAnimObjs[nAnimID];

	std::vector<Animation>& vAnims = m_vAnimSheets[animObj.nCurSheet].vAnimations;

	for( std::vector<Animation>::size_type curAnim = 0; curAnim < vAnims.size(); ++curAnim )
	{
		if( strcmp( vAnims[curAnim].GetAnimName(), szAnim ) == 0 )
		{
			m_vAnimObjs[nAnimID].Reset();
			m_vAnimObjs[nAnimID].nCurAnim = curAnim;
			break;
		}
	}
}