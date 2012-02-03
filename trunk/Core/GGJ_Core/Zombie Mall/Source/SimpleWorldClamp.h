#ifndef SIMPLE_WORLD_CLAMP_H
#define SIMPLE_WORLD_CLAMP_H

class CBase;

#define WORLD_TOP		54.0f
#define WORLD_BOTTOM		1194.0f
#define WORLD_LEFT		200.0f
#define WORLD_RIGHT		1396.0f

void SimpleWorldClamping(CBase& _player);

#endif