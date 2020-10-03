#include "AnimationData.h"


CAnimationData::CAnimationData(int aniID, int spriteID, DWORD time)
{
	this->animationID = aniID;
	this->spriteID = spriteID;
	this->time = time;
}


CAnimationData::~CAnimationData(void)
{
}
