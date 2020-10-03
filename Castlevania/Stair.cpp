#include "Stair.h"


CStair::CStair(int state)
{
	this->state = state;
}


CStair::~CStair(void)
{
}

void CStair::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

}

void CStair::Render()
{
	RenderBoundingBox();
}

void CStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + STAIR_BBOX_WIDTH;
	bottom = y + STAIR_BBOX_HEIGHT;
}