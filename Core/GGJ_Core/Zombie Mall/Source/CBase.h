/////////////////////////////////////////////////////////
//	File Name	: "CBase.h"
//	Author Name : James Brown
//	Purpose		: To contrain all related data &
//				  functionality of our game objects
/////////////////////////////////////////////////////////

#ifndef _CBASE
#define _CBASE

#include "IBaseInterface.h"
#include <string>
enum type{ OBJECT_PLAYER, OBJECT_HUMAN, OBJECT_ZOMBIE, OBJECT_GUARD, OBJECT_NONE};

#include "SGD_Math.h"

struct Circle
{
	tVector2D	m_Center;
	float		m_fRadius;

	bool CheckCollision( Circle& test );
};

class CBase : public IBaseInterface
{
private:
	// reference counter
	unsigned int m_uiRefCount;

	// Dimensions
	int m_nWidth;
	int m_nHeight;

	// Position
	float m_nPosX;
	float m_nPosY;

	// Rotation
	float m_fTotalRot;

	// Direction
	tVector2D m_Look;

	float m_fRot;
	float m_fSpeed;

	// Image
	int m_nImageID;


	float m_nRespawnDelay;
	char* m_nName;
protected:
	// Type
	type m_nType;

public:

	CBase();
	virtual ~CBase();
	

	////////////////////////////////////////////////////////
	//	Function:	Accessors
	//
	//	Purpose:	To get the specified type.
	////////////////////////////////////////////////////////
	float GetRotation() { return m_fTotalRot;}
	void SetRotation(float rot) { m_fTotalRot = rot; }
	float GetPosX()	{return m_nPosX;}
	float GetPosY()	{return m_nPosY;}
	float GetDirX()	{return m_Look.fX;}
	float GetDirY()	{return m_Look.fY;}
	tVector2D GetLook() const {return m_Look;}
	float GetRot() const	{return m_fRot;}
	float GetSpeed() const {return m_fSpeed;}
	float GetCenterPosX()	{return m_nPosX + m_nWidth/2;}
	float GetCenterPosY()	{return m_nPosY + m_nHeight/2;}
	int GetImageID(){return m_nImageID;}
	type GetType() { return m_nType; }
	int GetWidth()	{return m_nWidth;}
	int GetHeight() {return m_nHeight;}
	char* GetName();
	float GetRespawnDelay() { return m_nRespawnDelay; }
	////////////////////////////////////////////////////////
	//	Function:	Modifiers
	//
	//	Purpose:	To get the specified type.
	////////////////////////////////////////////////////////
	void SetRespawnDelay(float delay) { m_nRespawnDelay = delay; }
	void SetPosX(float nPosX) {m_nPosX = nPosX;}
	void SetPosY(float nPosY) {m_nPosY = nPosY;}
	void SetDirX(float fDirX) {m_Look.fX = fDirX;}
	void SetDirY(float fDirY) {m_Look.fY = fDirY;}
	void SetLook( tVector2D look )	{m_Look = look;}
	void SetRot( float fRot )	{m_fRot = fRot;}
	void SetSpeed( float fSpeed )	{ m_fSpeed = fSpeed; }
	void SetImageID(int nImageID) {m_nImageID = nImageID;}
	void SetWidth(int nWidth)	{m_nWidth = nWidth;}
	void SetHeight(int nHeight)	{m_nHeight = nHeight;}
	void SetType(::type _type) { m_nType = _type; }

	void SetName(char* name);
	//Note: to input at top of Update if needed
	virtual void Update(float fElapsedTime);

	virtual void Render();

	void AddRef() { m_uiRefCount++; }

	void Release()
	{
		m_uiRefCount--;

		if(!m_uiRefCount)
			delete this;
	}

	virtual Circle GetCollisionVolume();

	virtual type CheckCollision(IBaseInterface* pBase);
};


#endif