#include "SubWeapon.h"
#include "debug.h"
#include "Candle.h"
#include "Simon.h"
#include "Gate.h"

void CSubWeapon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CItem::Update(dt);
}

CDagger::CDagger(float x, float y):CSubWeapon(x, y)
{
	damage = DAGGER_DAMAGE;
	InitAnimation();
}

void CDagger::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Dagger_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CItem::Update(dt);
	if (this->state == ITEM_STATE_NORMAL)
		vy += DAGGER_GRAVITY *dt;
	else vy = 0;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (state != ITEM_STATE_COLLIDE_SIMON)
		CalcPotentialCollisions(coObjects, coEvents);

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
		else if (dynamic_cast<CGate *>(e->obj))
		{
			coEvents.erase(coEvents.begin() + i);
			i--;
		}

	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny = 0;
		FilterCollision(coEvents,coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CCandle *>(e->obj))
			{
				CCandle *candle = dynamic_cast<CCandle *>(e->obj);
				candle->SetState(CANDLE_STATE_DISAPPEAR);
				candle->SetStartEffect();
				
				this->state = SUBWEAPON_STATE_COLLIDE_OBJECT;
			}
			else if (dynamic_cast<CSimon *>(e->obj))
			{
				CSimon *simon = dynamic_cast<CSimon *>(e->obj);
				simon->SetSubWeapon(new CDagger(simon->x, simon->y));
				
				this->state = ITEM_STATE_COLLIDE_SIMON;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//DebugOut(L"vx %f\n", vx);
}

void CDagger::Render()
{
	if (state == ITEM_STATE_NORMAL)
		animations[DAGGER_ANI_RIGHT]->Render(x, y);
	else if (state == ITEM_STATE_SUBWEAPON)
	{
		if (nx > 0) animations[DAGGER_ANI_RIGHT]->Render(x, y);
		else animations[DAGGER_ANI_LEFT]->Render(x, y);
	}
	
}

void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + DAGGER_BBOX_WIDTH;
	bottom = y + DAGGER_BBOX_HEIGHT;
}

void CDagger::SetState(int state)
{
	CGameObject::SetState(state);
	switch(state)
	{
	case ITEM_STATE_SUBWEAPON:
		if (nx > 0) vx = DAGGER_SPEED;
		else vx = -DAGGER_SPEED;
		break;
	}
}