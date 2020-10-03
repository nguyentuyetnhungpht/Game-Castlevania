#pragma once
#include "gameobject.h"
#define HEART	1
#define WHIP_UPDATE	2
#define DAGGER	3
#define MONEY_BAG	4
#define BOOMERANG	5
#define AXE			6

#define ITEM_STATE_NORMAL 0
#define ITEM_STATE_COLLIDE_SIMON	1

class CItem :
	public CGameObject
{
public:
	CItem(float x, float y);
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
};

#define BIG_HEART_GRAVITY	0.0004f
#define SMALL_HEART_GRAVITY	0.000004f

#define BIG_HEART	0
#define SMALL_HEART	100

#define BIG_HEART_ANI	0
#define SMALL_HEART_ANI	1

#define BIG_HEART_BBOX_WIDTH	14
#define BIG_HEART_BBOX_HEIGHT	11

#define SMALL_HEART_BBOX_WIDTH	10
#define SMALL_HEART_BBOX_HEIGHT	11

class CHeart : public CItem
{
	int type;
	int heart;

	void InitAnimation();
public:
	CHeart(float x, float y, int type);
	CHeart(float x, float y);
	void Update (DWORD dt, vector<LPGAMEOBJECT> *coObjects= NULL);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

#define WHIP_UPDATE_GRAVITY	0.0004f

#define WHIP_UPDATE_BBOX_WIDTH	19
#define WHIP_UPDATE_BBOX_HEIGHT	19

class CWhipUpdate : public CItem
{
	void InitAnimation();
public:
	CWhipUpdate(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects= NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};