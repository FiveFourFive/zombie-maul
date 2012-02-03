#include <Windows.h>
#include "CCollisionRect.h"




CCollisionRect::CCollisionRect()
{

}

CCollisionRect::~CCollisionRect()
{

}

CCollisionRect::CCollisionRect( float Pos_x, float Pos_y, int width, int height)
{
	m_fPosition.fX = Pos_x;
	m_fPosition.fY = Pos_y;
	m_nWidth = width;
	m_nHeight = height;
}

RECT CCollisionRect::GetRect()
{
	RECT r;
	r.left = m_fPosition.fX;
	r.top = m_fPosition.fY;
	r.right = r.left + m_nWidth;
	r.bottom = r.top + m_nHeight;
	return r;
}