#include "Resource.h"
#include "GameObject.h"
#include "LoadingData.h"

CResource::CResource(void)
{
	textures = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
}


CResource::~CResource(void)
{
}

void CResource::LoadTextures()
{
	textures->Add(ID_TEX_SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(0, 128, 128));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_CANDLE, L"textures\\Candle.png", D3DCOLOR_XRGB(34, 177, 76));
	textures->Add(ID_TEX_BRICK, L"textures\\Brick.png", D3DCOLOR_XRGB(255, 255,255));
	textures->Add(ID_TEX_MAP1A, L"textures\\gate_tilemap.png", D3DCOLOR_XRGB(255, 255, 255));//sd 1 id, dùng id này để gọi
	textures->Add(ID_TEX_GATE, L"textures\\gate.png",D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_EFFECT, L"textures\\Effect.png", D3DCOLOR_XRGB(34, 177, 76));
	textures->Add(ID_TEX_ITEM, L"textures\\Items.png", D3DCOLOR_XRGB(128, 0, 0));
	textures->Add(ID_TEX_MAP1B, L"textures\\castle_tileset.png", D3DCOLOR_XRGB(255, 255, 255));
}

void CResource::LoadSprites()
{
	LPDIRECT3DTEXTURE9 texsimon;
	texsimon = textures->Get(ID_TEX_SIMON);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Simon.txt", texsimon);

	LPDIRECT3DTEXTURE9 texcandle;
	texcandle = textures->Get(ID_TEX_CANDLE);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Candle.txt", texcandle);

	LPDIRECT3DTEXTURE9 texwhip;
	texwhip = textures->Get(ID_TEX_SIMON);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Whip.txt", texwhip);

	LPDIRECT3DTEXTURE9 texbrick;
	texbrick = textures->Get(ID_TEX_BRICK);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Brick.txt", texbrick);

	LPDIRECT3DTEXTURE9 texgate;
	texgate = textures->Get(ID_TEX_GATE);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Gate.txt",texgate);

	LPDIRECT3DTEXTURE9 texeffect;
	texeffect = textures->Get(ID_TEX_EFFECT);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\HitEffect.txt", texeffect);

	LPDIRECT3DTEXTURE9 texheart;
	texheart = textures->Get(ID_TEX_ITEM);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Heart.txt", texheart);

	LPDIRECT3DTEXTURE9 texwhipupdate;
	texwhipupdate = textures->Get(ID_TEX_ITEM);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\WhipUpdate.txt", texwhipupdate);

	LPDIRECT3DTEXTURE9 texdagger;
	texdagger = textures->Get(ID_TEX_ITEM);
	CLoadingData::LoadSpriteFromFile(sprites, L"Data\\Dagger.txt", texdagger);

}
