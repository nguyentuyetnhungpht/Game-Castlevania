#include "Item.h"
#include "LoadingData.h"
#include "Simon.h"

CItem::CItem(float x, float y):CGameObject()
{
	this->x = x;
	this->y = y;
	state = ITEM_STATE_NORMAL;
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
}

CHeart::CHeart(float x, float y, int type):CItem(x, y)
{
	this->type = type;
	switch(type)
	{
	case BIG_HEART:
		heart = 5;
		break;
	case SMALL_HEART:
		heart = 1;
		break;
	}
	InitAnimation();
}

CHeart::CHeart(float x, float y):CItem(x, y)
{
	int random = rand() % 10 + 1;
	if (random <= 3)
		type = BIG_HEART;
	else type = SMALL_HEART;

	switch(type)
	{
	case BIG_HEART:
		heart = 5;
		break;
	case SMALL_HEART:
		heart = 1;
		break;
	}
	InitAnimation();
}

void CHeart::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Heart_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CItem::Update(dt);

	switch(type)
	{
	case BIG_HEART:
		vy += BIG_HEART_GRAVITY *dt;
		break;
	case SMALL_HEART:
		vy += SMALL_HEART_GRAVITY *dt;
		break;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (state == ITEM_STATE_NORMAL)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else 
	{
		float min_tx, min_ty, nx, ny = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += dx * min_tx + nx * 0.1f;
		y += dy * min_ty + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CSimon *>(e->obj))
			{
				CSimon *simon = dynamic_cast<CSimon *>(e->obj);
				if (simon->GetHeart() > MAX_HEART)
					simon->SetHeart(MAX_HEART);
				else 
					simon->SetHeart(simon->GetHeart() + this->heart);
				this->state = ITEM_STATE_COLLIDE_SIMON;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CHeart::Render()
{
	if (state == ITEM_STATE_NORMAL)
	{
		int ani;
		if (type == BIG_HEART)
			ani = BIG_HEART_ANI;
		else 
			ani = SMALL_HEART_ANI;
		animations[ani]->Render(x, y);
	}
}

void CHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (type == BIG_HEART)
	{
		right = x + BIG_HEART_BBOX_WIDTH;
		bottom = y + BIG_HEART_BBOX_HEIGHT;
	}
	else
	{
		right = x + SMALL_HEART_BBOX_WIDTH;
		bottom = y + SMALL_HEART_BBOX_HEIGHT;
	}
}

CWhipUpdate::CWhipUpdate(float x, float y):CItem(x, y)
{
	InitAnimation();
}

void CWhipUpdate::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\WhipUpdate_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CWhipUpdate::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CItem::Update(dt);
	vy += WHIP_UPDATE_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (state == ITEM_STATE_NORMAL)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += dx * min_tx + nx * 0.1f;
		y += dy * min_ty + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CSimon *>(e->obj))
			{
				CSimon *simon = dynamic_cast<CSimon *>(e->obj);
				CWhip *whip = simon->GetWhip();
				whip->SetType(whip->GetType() + 100);
				simon->SetWhip(whip);
				this->state = ITEM_STATE_COLLIDE_SIMON;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CWhipUpdate::Render()
{
	if (state == ITEM_STATE_NORMAL)
		animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CWhipUpdate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + WHIP_UPDATE_BBOX_WIDTH;
	bottom = y + WHIP_UPDATE_BBOX_HEIGHT;
}