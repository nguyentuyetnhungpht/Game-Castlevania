#pragma once
#include "TileMap.h"
#include "Grid.h"
#include "GameObject.h"
#include "Simon.h"
class Map
{
protected:
	int scene;
	CGrid *grid;
	CTileMap *tilemap;
	vector<LPGAMEOBJECT> coObjects;
public:
	Map(void);
	~Map(void);

	virtual void LoadMap() = 0;
	virtual void Update(DWORD dt, CSimon * simon) = 0;
	virtual void Render(CSimon * simon) = 0;

	int GetScene() {return this->scene;}
	void SetScene(int scene) {this->scene = scene;}
};

