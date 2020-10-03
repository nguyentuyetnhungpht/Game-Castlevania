#pragma once
#include "gameobject.h"
#include "Whip.h"
#include "SubWeapon.h"

#define SIMON_GRAVITY	0.0008f
#define SIMON_WALKING_SPEED	0.05f
#define SIMON_CLIMBING_STAIR_SPEED	0.06f
#define SIMON_JUMP_SPEED	0.24f

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALKING_LEFT	100
#define SIMON_STATE_WALKING_RIGHT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_KNEE			400
#define SIMON_STATE_FIGHTING		500
#define SIMON_STATE_KNEE_FIGHTING	600
#define SIMON_STATE_UP_STAIR		700
#define SIMON_STATE_DOWN_STAIR		800
#define SIMON_STATE_USING_SUBWEAPON	900
#define SIMON_STATE_COLLISION_ENEMY	1000
#define SIMON_STATE_DIE				1100
#define SIMON_STATE_AUTO			1200
#define SIMON_STATE_UP_STAIR_IDLE	1300
#define SIMON_STATE_DOWN_STAIR_IDLE	1400

#define SIMON_ANI_IDLE_LEFT			0 //OK
#define SIMON_ANI_IDLE_RIGHT		1//OK
#define SIMON_ANI_WALKING_LEFT		2//OK
#define SIMON_ANI_WALKING_RIGHT		3//OK
#define SIMON_ANI_JUMP_LEFT			4//OK
#define SIMON_ANI_JUMP_RIGHT		5//OK
#define SIMON_ANI_FIGHTING_LEFT		6//OK
#define SIMON_ANI_FIGHTING_RIGHT	7//OK
#define SIMON_ANI_USING_SUBWEAPON_LEFT	8
#define SIMON_ANI_USING_SUBWEAPON_RIGHT 9
#define SIMON_ANI_KNEE_FIGHTING_LEFT	10//OK
#define SIMON_ANI_KNEE_FIGHTING_RIGHT	11//OK
#define SIMON_ANI_UP_STAIR_LEFT			12
#define SIMON_ANI_UP_STAIR_RIGHT		13
#define SIMON_ANI_DOWN_STAIR_LEFT		14
#define SIMON_ANI_DOWN_STAIR_RIGHT		15
#define SIMON_ANI_UP_STAIR_IDLE_LEFT	16
#define SIMON_ANI_UP_STAIR_IDLE_RIGHT	17
#define SIMON_ANI_DOWN_STAIR_IDLE_LEFT	18
#define SIMON_ANI_DOWN_STAIR_IDLE_RIGHT	19
#define SIMON_ANI_COLLISION_ENEMY_LEFT	20
#define SIMON_ANI_COLLISION_ENEMY_RIGHT 21
#define SIMON_ANI_DIE_LEFT				22
#define SIMON_ANI_DIE_RIGHT				23

#define SIMON_BBOX_WIDTH	18
#define SIMON_BBOX_HEIGHT	31

#define SIMON_KNEE_BBOX_HEIGHT 24

#define OFFSET1	9
#define OFFSET2 7

#define MAX_HEART	99
#define MAX_POINT	999999
#define MAX_LIFE	99

#define TIME_UPDATE_SUBWEAPON	1000

class CSimon :
	public CGameObject
{

	CWhip *whip;
	CSubWeapon *subweapon;

	int health;
	int heart;
	int stage;
	int point;
	int life;

	bool isStair;
	bool isOnStair;

	bool isUpStair;
	bool isDownStair;

	bool untouchable;
	DWORD startUntouchable;

	bool isSub;

	void InitAnimation();
public:
	CSimon(void);
	~CSimon(void);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void SetState(int state);

	int GetHealth() {return this->health;}
	int GetHeart() {return this->heart;}
	int GetStage() {return this->stage;}
	bool GetIsUpStair() {return this->isUpStair;}
	bool GetIsDownStair() {return this->isDownStair;}
	CWhip *GetWhip() {return this->whip;}
	int GetPoint() {return this->point;}
	int GetLife() {return this->life;}
	CSubWeapon *GetSubWeapon() {return this->subweapon;}
	bool GetIsStair() {return isStair;}
	bool GetIsOnStair() {return isOnStair;}

	void SetHealth(int health) {this->health = health;}
	void SetHeart(int heart) {this->heart = heart;}
	void SetStage(int stage) {this->stage = stage;}
	void SetIsUpStair(bool isUpStair) {this->isUpStair = isUpStair;}
	void SetIsDownStair(bool isDownStair) {this->isDownStair = isDownStair;}
	void SetPoint(int point) {this->point = point;}
	void SetLife(int life) {this->life = life;}
	
	void SetSubWeapon(CSubWeapon *subweapon) {this->subweapon = subweapon;}
	void SetStartSub() {this->isSub = true;}
	void SetIsStair(bool isStair) {this->isStair = isStair;}
	void SetIsOnStair(bool isOnStair) {this->isOnStair = isOnStair;}

	void SetWhip(CWhip *whip) {this->whip = whip;}
	
};