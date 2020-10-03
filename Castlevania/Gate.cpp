#include "Gate.h"

CGate::CGate(void):CGameObject()
{
	InitAnimation();
}


CGate::~CGate(void)
{
}

void CGate::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Gate_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CGate::Render()
{
	animations[0]->Render(x, y);
}

void CGate::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GATE_BBOX_WIDTH;
	bottom = y + GATE_BBOX_HEIGHT;
}