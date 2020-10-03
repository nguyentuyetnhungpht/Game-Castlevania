#pragma once
#include "map.h"

#define SCENE_1	1
#define SCENE_2	2
#define SCENE_3	3
#define SCENE_4	4
#define SCENE_5	5

#define MIN_CAMERA_1	119.0f
#define MAX_CAMERA_1	631.0f
#define WIDTH_SCENE_1	768.0f

#define MIN_CAMERA_2	119.0f
#define MAX_CAMERA_2	1399.0f
#define WIDTH_SCENE_2	1536.0f
class CLevel1 :
	public Map
{
	static CLevel1 *__instance;
public:
	CLevel1(void);
	~CLevel1(void);

	void LoadMap();
	void Update(DWORD dt, CSimon * simon);
	void Render(CSimon * simon);

	void GetMinMaxCamera(float & min, float & max, float & widthScene);
	static CLevel1 *GetInstance();
};

