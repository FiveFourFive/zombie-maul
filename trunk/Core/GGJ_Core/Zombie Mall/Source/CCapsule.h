#ifndef CAPSULE_H_
#define CAPSULE_H_

#include "SGD_Math.h"

class Capsule
{
private:
	tVector2D m_vStartPoint;
	tVector2D m_vEndPoint;
	float m_fRadius;

	
public:
	Capsule();
	~Capsule(){};
	Capsule( tVector2D start, tVector2D end, float radius) : m_vStartPoint(start), m_vEndPoint(end), m_fRadius(radius){}

	friend tVector2D ClosestPointOnALine( tVector2D start, tVector2D end, tVector2D testPoint);

	tVector2D GetStartPoint(){ return m_vStartPoint;}
	tVector2D GetEndPoint() { return m_vEndPoint;}
	float GetRadius() { return m_fRadius;}
};

#endif