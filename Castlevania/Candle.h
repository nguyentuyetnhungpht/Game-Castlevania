#pragma once
#include "gameobject.h"
#include "Effect.h"
#include "Item.h"
#include "SubWeapon.h"

#define BIG_CANDLE		0
#define SMALL_CANDLE	1


#define CANDLE_STATE_NORMAL 0
#define CANDLE_STATE_DISAPPEAR	1


#define BIG_CANDLE_ANI		0
#define SMALL_CANDLE_ANI	1

#define BIG_CANDLE_BBOX_WIDTH	18
#define BIG_CANDLE_BBOX_HEIGHT	34

#define SMALL_CANDLE_BBOX_WIDTH	10
#define SMALL_CANDLE_BBOX_HEIGHT	18

#define TIME_EFFECT	200
class CCandle :
	public CGameObject
{
	int type;
	CEffect *effect;
	CItem *item;

	DWORD startEffect;
	void InitAnimation();
public:
	CCandle(float x,float y, int type);
	CCandle(float x,float y, int type, int typeitem);
	CCandle(void);
	~CCandle(void);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);

	void SetStartEffect() {startEffect = GetTickCount();}
};

