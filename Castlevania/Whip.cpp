#include "Whip.h"
#include "Textures.h"
#include "Sprites.h"
#include "Simon.h"
#include "Candle.h"
#include "debug.h"
CWhip::CWhip(int type)
{
	manager = new CAnimationManager();
	this->type = type;
	InitAnimation();
}

CWhip::CWhip(void)
{
	manager = new CAnimationManager();
	InitAnimation();
}


CWhip::~CWhip(void)
{
}

void CWhip::InitAnimation()
{
	CAnimations * animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Whip_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	switch (type)
	{
	case NORMAL_WHIP:
	case BLUE_WHIP:
		if (nx > 0) vx = SHORT_WHIP_SPEED;
		else vx = -SHORT_WHIP_SPEED;
		break;
	case YELLOW_WHIP:
		if (nx > 0) vx = LONG_WHIP_SPEED;
		else vx = -LONG_WHIP_SPEED;
	}
	

	if (GetTickCount() - start > TIME)
	{
		CGameObject::Update(dt);
		start = 0;
		x += dx;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	CGameObject::CalcPotentialCollisions(coObjects, coEvents);

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<CCandle *>(e->obj))
		{
			CCandle *candle = dynamic_cast<CCandle *>(e->obj);
			if (candle->state == CANDLE_STATE_DISAPPEAR)
			{
				coEvents.erase(coEvents.begin() + i);
				i--;
			}
		}
	}

	float min_tx, min_ty, nx , ny = 0;
	CGameObject::FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CCandle *>(e->obj))
		{
			CCandle *candle = dynamic_cast<CCandle *>(e->obj);
			candle->SetState(CANDLE_STATE_DISAPPEAR);
			candle->SetStartEffect();
		}
	}	
}


void CWhip::Render()
{
	switch(type)
	{
	case NORMAL_WHIP:
		if (nx > 0)
		{
			SetPositionAni(ani_x, ani_y, SIMON_BBOX_WIDTH, SIMON_BBOX_WIDTH, 
				manager->GetAni(NORMAL_WHIP_ANI_RIGHT));
			animations[NORMAL_WHIP_ANI_RIGHT]->Render(255);
		}
		else 
		{		
			SetPositionAni(ani_x, ani_y, -OFFSET_X1, -SIMON_BBOX_WIDTH, 
				manager->GetAni(NORMAL_WHIP_ANI_LEFT));
			animations[NORMAL_WHIP_ANI_LEFT]->Render(255);
		}
		break;
	case BLUE_WHIP:
		if (nx > 0)
		{
			SetPositionAni(ani_x, ani_y, SIMON_BBOX_WIDTH, OFFSET_X, 
				manager->GetAni(BLUE_WHIP_ANI_RIGHT));
			animations[BLUE_WHIP_ANI_RIGHT]->Render(255);
		}
		else 
		{		
			SetPositionAni(ani_x, ani_y, -OFFSET_X1, -SIMON_BBOX_WIDTH, 
				manager->GetAni(BLUE_WHIP_ANI_LEFT));
			animations[BLUE_WHIP_ANI_LEFT]->Render(255);
		}
		break;
	case YELLOW_WHIP:
		if (nx > 0)
		{
			SetPositionAni(ani_x, ani_y, SIMON_BBOX_WIDTH, OFFSET_X, 
				manager->GetAni(YELLOW_WHIP_ANI_RIGHT));
			animations[YELLOW_WHIP_ANI_RIGHT]->Render(255);
		}
		else 
		{		
			SetPositionAni(ani_x, ani_y, -OFFSET_X2, -SIMON_BBOX_WIDTH, 
				manager->GetAni(YELLOW_WHIP_ANI_LEFT));
			animations[YELLOW_WHIP_ANI_LEFT]->Render(255);
		}
		break;
	}
	//RenderBoundingBox();
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_BBOX_WIDTH;
	bottom = y + WHIP_BBOX_HEIGHT;
}