#pragma once
#include "gameobject.h"

#define STAIR_STATE_UP		0
#define STAIR_STATE_DOWN	1

#define STAIR_BBOX_WIDTH	16
#define STAIR_BBOX_HEIGHT	9

class CStair :
	public CGameObject
{
public:
	CStair(int state);
	~CStair(void);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};

