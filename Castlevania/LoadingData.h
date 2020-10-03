#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "AnimationData.h"
#include <string>
#include <d3d9.h>

#define BRICK	1
#define CANDLE	2
#define GATE	3
#define STAIR	4

class CLoadingData
{
public:
	CLoadingData(void);
	~CLoadingData(void);

	static void LoadSpriteFromFile(CSprites *sprites, LPCWSTR fileName, LPDIRECT3DTEXTURE9 tex);
	static void LoadAnimationsDataFromFile(vector<CAnimationData *> &data, LPCWSTR fileName);
	static void LoadObjectsFromFile(vector<LPGAMEOBJECT> &objects, LPCWSTR fileName);
};

