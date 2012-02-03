
#include "SimpleWorldClamp.h"
#include "CBase.h"

void SimpleWorldClamping(CBase& _player)
{

	if ( (_player.GetCenterPosY() - (_player.GetHeight() * 0.5f)) < WORLD_TOP )
	{
		_player.SetPosY(WORLD_TOP);
	}

	else if ( (_player.GetCenterPosY() + (_player.GetHeight() * 0.5f)) > WORLD_BOTTOM )
	{
		_player.SetPosY(WORLD_BOTTOM - _player.GetHeight());
	}

	if ( (_player.GetCenterPosX() - (_player.GetWidth() * 0.5f)) < WORLD_LEFT )
	{
		_player.SetPosX(WORLD_LEFT);
	}

	else if ( (_player.GetCenterPosX() + (_player.GetWidth() * 0.5f)) > WORLD_RIGHT )
	{
		_player.SetPosX(WORLD_RIGHT - _player.GetWidth());
	}
}
