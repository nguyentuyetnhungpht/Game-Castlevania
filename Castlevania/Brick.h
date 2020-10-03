#pragma once
#include "GameObject.h"

#define BRICK_TYPE1	0
#define BRICK_TYPE2 100
#define BRICK_TYPE3	200

#define BRICK_ANI_TYPE1	0
#define BRICK_ANI_TYPE2	1
#define BRICK_ANI_TYPE3	2

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_BBOX_TYPE3_WIDTH	8
#define BRICK_BBOX_TYPE3_HEIGHT	7

class CBrick : public CGameObject
{
	int type;
	void InitAnimation();
public:
	CBrick(int type);

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};