#include "Simon.h"
#include "debug.h"
#include "Candle.h"
#include "Game.h"
#include "Gate.h"
#include "Level1.h"
#include "Stair.h"

CSimon::CSimon(void):CGameObject()
{
	this->health = 16;
	this->heart = 5;
	this->point = 0;
	this->life = 2;
	this->stage = 1;

	whip = new CWhip(NORMAL_WHIP);
	subweapon = NULL;
	isSub = false;
	isStair = false;
	isUpStair = false;
	isDownStair = false;
	InitAnimation();
}


CSimon::~CSimon(void)
{
}

void CSimon::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Simon_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);

	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamera(cam_x, cam_y);
	if (state != SIMON_STATE_UP_STAIR && state != SIMON_STATE_DOWN_STAIR 
		&& state != SIMON_STATE_UP_STAIR_IDLE && state != SIMON_STATE_DOWN_STAIR_IDLE)
	vy += SIMON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	CalcPotentialCollisions(coObjects, coEvents);
	//Delete objects doesn't collide with simon
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<CCandle *> (e->obj))
		{
			coEvents.erase(coEvents.begin() + i);
			i--;
		}
		else if (dynamic_cast<CGate *> (e->obj))
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
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.1f;
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
		}
	}

	if (state == SIMON_STATE_FIGHTING || state == SIMON_STATE_KNEE_FIGHTING)
		whip->Update(dt, coObjects);
	else if (isSub)
	{
		float sx, sy;
		subweapon->GetPosition(sx, sy);
		if (sx > cam_x && sx < cam_x + VIEWPORT_WIDTH && subweapon->state != SUBWEAPON_STATE_COLLIDE_OBJECT)
			subweapon->Update(dt, coObjects);
		else isSub = false;
	}
	
	DebugOut(L"Simon state: %d\n", state);
	//Coding camera
	//update tọa độ theo simon, min max là k update khi simon ở cuối hay đầu map

	float min, max, widthScene;
	CLevel1 *level1 = CLevel1::GetInstance();
	level1->GetMinMaxCamera(min, max, widthScene);

	if (this->x < min)
		game->SetCamera(0.0f, 0.0f);
	else if (this->x > max)
		game->SetCamera(widthScene - VIEWPORT_WIDTH, 0.0f);
	else game->SetCamera(x - 119.0f, 0.0f);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani;
	
	if (vx == 0)
	{
		if (nx > 0) 
		{
			ani = SIMON_ANI_IDLE_RIGHT;
			if (state == SIMON_STATE_KNEE)
				ani = SIMON_ANI_JUMP_RIGHT;			
			else if(state == SIMON_STATE_UP_STAIR_IDLE)
				ani = SIMON_ANI_UP_STAIR_IDLE_RIGHT;
			else if(state == SIMON_STATE_DOWN_STAIR_IDLE)
				ani = SIMON_ANI_DOWN_STAIR_IDLE_RIGHT;

			if (state == SIMON_STATE_FIGHTING)
			{
				whip->SetPositionAniToRender(x, y);
				whip->nx = nx;
				whip->Render();
				ani = SIMON_ANI_FIGHTING_RIGHT;
				
			}
			else if (state == SIMON_STATE_USING_SUBWEAPON && subweapon != NULL)
			{
				CGameObject::SetPositionAni(x, y, SIMON_BBOX_WIDTH, OFFSET1,
					manager->GetAni(SIMON_ANI_USING_SUBWEAPON_RIGHT));
				animations[SIMON_ANI_USING_SUBWEAPON_RIGHT]->Render(255);
				ani = SIMON_ANI_FIGHTING_RIGHT;
			}
			else if (state == SIMON_STATE_KNEE_FIGHTING)
			{
				whip->SetPositionAniToRender(x, y);
				whip->nx = nx;
				whip->Render();
				ani = SIMON_ANI_KNEE_FIGHTING_RIGHT;
			}
		}
		else
		{
			ani = SIMON_ANI_IDLE_LEFT;
			if (state == SIMON_STATE_KNEE)
				ani = SIMON_ANI_JUMP_LEFT;
			else if (state == SIMON_STATE_UP_STAIR_IDLE)
				ani = SIMON_ANI_UP_STAIR_IDLE_LEFT;
			else if (state == SIMON_STATE_DOWN_STAIR_IDLE)
				ani = SIMON_ANI_DOWN_STAIR_IDLE_LEFT;


			if (state == SIMON_STATE_FIGHTING)
			{
				whip->SetPositionAniToRender(x, y);
				whip->nx = nx;
				whip->Render();
				ani = SIMON_ANI_FIGHTING_LEFT;	
			}
			else if (state == SIMON_STATE_USING_SUBWEAPON)
			{
				CGameObject::SetPositionAni(x, y, -OFFSET2, -SIMON_BBOX_WIDTH,
					manager->GetAni(SIMON_ANI_USING_SUBWEAPON_LEFT));
				animations[SIMON_ANI_USING_SUBWEAPON_LEFT]->Render(255);
				ani = SIMON_ANI_FIGHTING_LEFT;
			}
			else if (state == SIMON_STATE_KNEE_FIGHTING)
			{
				whip->SetPositionAniToRender(x, y);
				whip->nx = nx;
				whip->Render();
				ani = SIMON_ANI_KNEE_FIGHTING_LEFT;
			}
		}
	}
	else 
	{
		if (nx > 0) 
		{
			ani = SIMON_ANI_WALKING_RIGHT;

			if (state == SIMON_STATE_UP_STAIR)
				ani = SIMON_ANI_UP_STAIR_RIGHT;
			else if (state == SIMON_STATE_DOWN_STAIR)
				ani = SIMON_ANI_DOWN_STAIR_RIGHT;
		}
		else 
		{	
			ani = SIMON_ANI_WALKING_LEFT;

			if (state == SIMON_STATE_UP_STAIR)
				ani = SIMON_ANI_UP_STAIR_LEFT;
			else if (state == SIMON_STATE_DOWN_STAIR)
				ani = SIMON_ANI_DOWN_STAIR_LEFT;
		}
	}

	if (vy < 0 && state != SIMON_STATE_FIGHTING && state != SIMON_STATE_USING_SUBWEAPON)
	{
		if (nx > 0)
			ani = SIMON_ANI_JUMP_RIGHT;
		else 
			ani = SIMON_ANI_JUMP_LEFT;
	}

	if (isSub) subweapon->Render();
	animations[ani]->Render(x, y);
	//RenderBoundingBox();
}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	if (state == SIMON_STATE_KNEE || state == SIMON_STATE_KNEE_FIGHTING)
		bottom = y + SIMON_KNEE_BBOX_HEIGHT;	
	else bottom = y + SIMON_BBOX_HEIGHT;
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch(state)
	{
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_WALKING_RIGHT:
	case SIMON_STATE_AUTO:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_UP_STAIR:
	case SIMON_STATE_DOWN_STAIR:
		if (nx > 0) vx = SIMON_CLIMBING_STAIR_SPEED;
		else vx = - SIMON_CLIMBING_STAIR_SPEED;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED;
	case SIMON_STATE_IDLE:
	case SIMON_STATE_KNEE:
	case SIMON_STATE_FIGHTING:
	case SIMON_STATE_USING_SUBWEAPON:
	case SIMON_STATE_UP_STAIR_IDLE:
	case SIMON_STATE_DOWN_STAIR_IDLE:
		vx = 0;
		break;
	}
}