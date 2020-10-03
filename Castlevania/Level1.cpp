#include "Level1.h"
#include "Resource.h"
#include "LoadingData.h"
#include "debug.h"

CLevel1 *CLevel1::__instance = NULL;
CLevel1::CLevel1(void)
{
}


CLevel1::~CLevel1(void)
{
}

void CLevel1::LoadMap()
{
	CTextures *textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texscene1;
	LPDIRECT3DTEXTURE9 texscene2;
	vector<LPGAMEOBJECT> objects;
	float width, height;

	switch(scene)
	{
	case SCENE_1:
		tilemap = new CTileMap();
		texscene1 = textures->Get(ID_TEX_MAP1A);
		tilemap->LoadTileMap("Data\\TileMap1Stage1A.txt", texscene1);

		
		tilemap->GetSize(width, height);
		grid = new CGrid(width, height);

		CLoadingData::LoadObjectsFromFile(objects, L"Data\\Object_scene1.txt");
		grid->InitGrid(objects);
		break;
	case SCENE_2:
		tilemap = new CTileMap();
		texscene2 = textures->Get(ID_TEX_MAP1B);
		tilemap->LoadTileMap("Data\\TileMap1Stage1B.txt", texscene2);
		
		
		tilemap->GetSize(width, height);
		grid = new CGrid(width, height);

		CLoadingData::LoadObjectsFromFile(objects, L"Data\\Object_scene2.txt");
		grid->InitGrid(objects);
		break;
	}
}

void CLevel1::Update(DWORD dt, CSimon * simon)
{
	vector<LPGAMEOBJECT> objects;
	grid->GetListObject(coObjects);
	objects = coObjects;

	simon->Update(dt, &coObjects);
	coObjects.push_back(simon);

	for (UINT i = 0; i < objects.size(); i++)
		objects[i]->Update(dt, &coObjects);
}

void CLevel1::Render(CSimon *simon)
{
	tilemap->Render(0.0f, 0.0f);
	
	/*if (scene == SCENE_1)
	{
		for (UINT i = 0; i < coObjects.size(); i++)
			coObjects[i]->Render();

		simon->Render();
		coObjects[0]->Render();
	}
	else 
	{*/
		for (UINT i = 0; i < coObjects.size(); i++)
			coObjects[i]->Render();

		simon->Render();
	//}
}

void CLevel1::GetMinMaxCamera(float & min, float & max, float & widthScene)
{
	switch(scene)
	{
	case SCENE_1:
		min = MIN_CAMERA_1;
		max = MAX_CAMERA_1;
		widthScene = WIDTH_SCENE_1;
		break;
	case SCENE_2:
		min = MIN_CAMERA_2;
		max = MAX_CAMERA_2;
		widthScene = WIDTH_SCENE_2;
		break;
	}
}

CLevel1 *CLevel1::GetInstance() 
{
	if (__instance == NULL) __instance = new CLevel1();
	return __instance;
}