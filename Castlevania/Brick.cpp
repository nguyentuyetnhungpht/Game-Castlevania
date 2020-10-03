#include "Brick.h"

CBrick::CBrick(int type):CGameObject()
{
	this->type = type;
	InitAnimation();
}

void CBrick::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Brick_Ani.txt");

	for (UINT i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CBrick::Render()
{
	int ani;
	switch (type)
	{
	case BRICK_TYPE1:
		ani = BRICK_ANI_TYPE1;
		break;
	case BRICK_TYPE2:
		ani = BRICK_ANI_TYPE2;
		break;
	case BRICK_TYPE3:
		ani = BRICK_ANI_TYPE3;
		break;
	}
	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (type == BRICK_TYPE3)
	{
		r = x + BRICK_BBOX_TYPE3_WIDTH;
		b = y + BRICK_BBOX_TYPE3_HEIGHT;
	}
	else
	{
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}