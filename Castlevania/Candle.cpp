#include "Candle.h"
#include "AnimationManager.h"

CCandle::CCandle(float x,float y, int type):CGameObject()
{
	this->type = type;
	this->x = x;
	this->y = y;
	state = CANDLE_STATE_NORMAL;
	effect = new CHitEffect(this->x + OFFSET_EFFECT_X, this->y + OFFSET_EFFECT_Y);
	InitAnimation();
}

CCandle::CCandle(float x,float y, int type, int typeitem):CGameObject()
{
	this->type = type;
	this->x = x;
	this->y = y;
	state = CANDLE_STATE_NORMAL;
	effect = new CHitEffect(this->x + OFFSET_EFFECT_X, this->y + OFFSET_EFFECT_Y);

	switch(typeitem)
	{
	case HEART:
		item = new CHeart(this->x + OFFSET_EFFECT_X, this->y + OFFSET_EFFECT_Y);
		break;
	case WHIP_UPDATE:
		item = new CWhipUpdate(this->x + OFFSET_EFFECT_X, this->y + OFFSET_EFFECT_Y);
		break;
	case DAGGER:
		item = new CDagger(this->x + OFFSET_EFFECT_X, this->y + OFFSET_EFFECT_Y);
		break;
	}
	InitAnimation();
}

CCandle::CCandle(void)
{
}


CCandle::~CCandle(void)
{
}

void CCandle::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\Candle_Ani.txt");

	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == CANDLE_STATE_DISAPPEAR)
		item->Update(dt, coObjects);
}

void CCandle::Render()
{
	DWORD now = GetTickCount();
	if (state != CANDLE_STATE_DISAPPEAR)
	{
		int ani;
		if (type == BIG_CANDLE)
			ani = BIG_CANDLE_ANI;
		else ani = SMALL_CANDLE_ANI;

		animations[ani]->Render(x, y);
		
	}
	else
	{
		if (now - startEffect < 200)
			effect->Render();
		else 
			item->Render();
	}
}

void CCandle::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (type == BIG_CANDLE)
	{
		right = x + BIG_CANDLE_BBOX_WIDTH;
		bottom = y + BIG_CANDLE_BBOX_HEIGHT;
	}
	else 
	{
		right = x + SMALL_CANDLE_BBOX_WIDTH;
		bottom = y + SMALL_CANDLE_BBOX_HEIGHT;
	}
}