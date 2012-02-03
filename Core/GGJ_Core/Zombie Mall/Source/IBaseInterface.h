/////////////////////////////////////////////////////////
//	File Name : "IBaseInterface.h"
//	Author Name : James Brown
//	Purpose : Interface
/////////////////////////////////////////////////////////

#ifndef _IBASEINTERFACE
#define _IBASEINTERFACE

#include <Windows.h>

struct Circle;
enum type;

class IBaseInterface
{
public:
	virtual ~IBaseInterface() = 0 {};

	virtual void Update(float fElapsedTime) = 0;
	virtual void Render() = 0;

	virtual void AddRef() = 0;
	virtual void Release() = 0;

	virtual type GetType() = 0;
	
	virtual Circle GetCollisionVolume() = 0;

	virtual type CheckCollision(IBaseInterface* pBase) = 0;
};

#endif