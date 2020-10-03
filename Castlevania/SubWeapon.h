#pragma once
#include "item.h"

#define ITEM_STATE_SUBWEAPON	2
#define SUBWEAPON_STATE_COLLIDE_OBJECT	3

class CSubWeapon :
	public CItem
{
protected:
	int damage;
public:
	CSubWeapon(float x, float y) : CItem(x, y){}

	void SetDamage(int damage) {this->damage = damage;}
	int GetDamage() {return this->damage;}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;

};

#define DAGGER_GRAVITY	0.0004f
#define DAGGER_SPEED	0.2f

#define DAGGER_ANI_RIGHT	0
#define DAGGER_ANI_LEFT		1

#define DAGGER_BBOX_WIDTH	19
#define DAGGER_BBOX_HEIGHT	11

#define DAGGER_DAMAGE	2

class CDagger:public CSubWeapon
{
	void InitAnimation();
public:
	CDagger(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void SetState(int state);
};