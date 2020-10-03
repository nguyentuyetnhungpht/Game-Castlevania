#include "LoadingData.h"
#include <fstream>
#include "debug.h"
#include "Brick.h"
#include "Candle.h"
#include "Gate.h"
#include "Stair.h"

CLoadingData::CLoadingData(void)
{
}


CLoadingData::~CLoadingData(void)
{
}

void CLoadingData::LoadSpriteFromFile(CSprites *sprites, LPCWSTR fileName, LPDIRECT3DTEXTURE9 tex)
{
	ifstream in;
	int id, left, top, right, bottom;
	in.open(fileName);
	if(!in)
		DebugOut(L"Can 't open file: %s\n ", fileName);
	else
	{
		while(!in.eof())
		{
			in >> id;
			in >> left;
			in >> top;
			in >> right;
			in >> bottom;

			sprites->Add(id, left, top, right, bottom, tex);
		}
	}
	in.close();
}

void CLoadingData::LoadAnimationsDataFromFile(vector<CAnimationData *> &data, LPCWSTR fileName)
{
	ifstream in;
	int aniID, spriteID;
	DWORD time;

	in.open(fileName);
	if (!in)
		DebugOut(L"Can't not open file %s\n", fileName);
	else
	{
		while(!in.eof())
		{
			in >> aniID;
			in >> spriteID;
			in >> time;

			data.push_back(new CAnimationData(aniID, spriteID, time));
		}
	}
	in.close();
}

void CLoadingData::LoadObjectsFromFile(vector<LPGAMEOBJECT> &objects, LPCWSTR fileName)
{
	ifstream in;
	int id, type, item;
	float x, y;

	in.open(fileName);
	if (!in)
		DebugOut(L"Can't not open file &s\n", fileName);
	else
	{
		while(!in.eof())
		{
			LPGAMEOBJECT object;
			in >> id;
			in >> x;
			in >> y;
			in >> type;
			in >> item;

			switch(id)
			{
			case BRICK:
				object = new CBrick(type);
				object->SetPosition(x, y);
				break;
			case CANDLE:
				if (item < 0)
					object = new CCandle(x, y, type);
				else 
					object = new CCandle(x, y, type, item);
				break;
			case GATE:
				object = new CGate();
				object->SetPosition(x, y);
				break;
			case STAIR:
				object =  new CStair(type);
				object->SetPosition(x, y);
				break;
			}

			objects.push_back(object);
		}
	}
}