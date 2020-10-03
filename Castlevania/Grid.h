#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;

#define CELL_WIDTH	64
#define CELL_HEIGHT	60

class CCell
{
	vector<LPGAMEOBJECT> objects;
public:
	vector<LPGAMEOBJECT> GetObjects() {return this->objects;}
	int AddObject(LPGAMEOBJECT object);
};
typedef CCell * LPCELL;

class CGrid
{
	LPCELL *cell;
public:
	CGrid(float width, float height);
	void InitGrid(vector<LPGAMEOBJECT> objects);
	CCell GetCell(float x, float y);
	void GetListObject(vector<LPGAMEOBJECT> &objects);
};

