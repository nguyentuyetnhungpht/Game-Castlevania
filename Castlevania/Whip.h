#pragma once
#include "gameobject.h"

#define SHORT_WHIP_SPEED 0.2f
#define LONG_WHIP_SPEED	0.3f

#define WHIP_IDLE 0
#define WHIP_KNEE 1


#define NORMAL_WHIP 0
#define BLUE_WHIP	100
#define YELLOW_WHIP	200
#define RED_WHIP	300


#define NORMAL_WHIP_ANI_LEFT	0
#define NORMAL_WHIP_ANI_RIGHT	1

#define BLUE_WHIP_ANI_LEFT		2	
#define BLUE_WHIP_ANI_RIGHT		3

#define YELLOW_WHIP_ANI_LEFT		4
#define YELLOW_WHIP_ANI_RIGHT		5



#define OFFSET_X	17
#define OFFSET_X1	28
#define OFFSET_X2	45

#define WHIP_BBOX_WIDTH		1
#define WHIP_BBOX_HEIGHT	1

#define TIME	250
class CWhip :
	public CGameObject
{
	int type;

	float ani_x, ani_y;

	DWORD start;
public:
	CWhip(int type);
	CWhip(void);
	~CWhip(void);

	void InitAnimation();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Render();
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);

	void SetPositionAniToRender(float ani_x, float ani_y) {this->ani_x = ani_x; this->ani_y = ani_y;}
	void SetStart(DWORD start) {this->start = start;}

	void SetType(int type) {this->type = type;}
	int GetType() {return this->type;}
};

