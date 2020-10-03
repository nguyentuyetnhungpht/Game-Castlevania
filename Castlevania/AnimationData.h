#pragma once
#include <d3d9.h>

class CAnimationData
{
	int animationID;
	int spriteID;
	DWORD time;
public:
	CAnimationData(int aniID, int spriteID, DWORD time);
	~CAnimationData(void);

	int GetAnimationID() {return this->animationID;}
	int GetSpriteID() {return this->spriteID;}
	DWORD GetTime() {return this->time;}
};

