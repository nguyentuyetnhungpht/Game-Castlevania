#pragma once
#include <d3d9.h>
#include "Textures.h"
#include "Sprites.h"
#include "AnimationManager.h"

#define ID_TEX_SIMON 0
#define ID_TEX_CANDLE	1
#define ID_TEX_BRICK	2
#define ID_TEX_GATE		3
#define ID_TEX_EFFECT	4
#define ID_TEX_ITEM		5

#define ID_TEX_MAP1A	20
#define ID_TEX_MAP1B	30
#define ID_TEX_MAP2B	40
class CResource
{
	CTextures *textures;
	CSprites *sprites;
public:
	CResource(void);
	~CResource(void);

	void LoadTextures();
	void LoadSprites();
};

