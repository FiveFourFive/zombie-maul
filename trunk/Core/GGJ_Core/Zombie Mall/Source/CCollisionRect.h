#ifndef COLLISIONRECT_H_
#define COLLISIONRECT_H_


#include "SGD_Math.h"
#include "CBase.h"

class CCollisionRect
{
private:
	tVector2D m_fPosition;
	int m_nWidth;
	int m_nHeight;

	Circle m_CollisionCircle;

public:

	CCollisionRect();
	~CCollisionRect();
	CCollisionRect( float Pos_x, float Pos_y, int width, int height);

	RECT GetRect();

	void SetCollisionCircleCenter(tVector2D pos) { m_CollisionCircle.m_Center = pos;}
	void SetCollisionCenterRadius(float radius) { m_CollisionCircle.m_fRadius = radius;}

	tVector2D GetCollisionCircleCenter() { return m_CollisionCircle.m_Center;}
	float GetCollisionCenterRadius() { return m_CollisionCircle.m_fRadius;}

	Circle* GetCollisionCircle(){ return &m_CollisionCircle;}

};

#endif