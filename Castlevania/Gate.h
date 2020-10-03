#pragma once
#include "gameobject.h"

#define GATE_BBOX_WIDTH	64
#define GATE_BBOX_HEIGHT	160

class CGate :
	public CGameObject
{

	void InitAnimation();
public:
	CGate(void);
	~CGate(void);

	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

