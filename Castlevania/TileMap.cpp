#include "TileMap.h"
#include "Game.h"
#include "debug.h"
#include <fstream>
using namespace std;

void CTileMap::LoadTileMap(string fileName, LPDIRECT3DTEXTURE9 tex)
{
	ifstream in(fileName);
	if (!in)
	{
		DebugOut(L"Can't not open file\n");
		return;
	}
	else DebugOut(L"Open file sucessful!\n");

	in >> column;//24
	in >> row;//6

	width = (float)TILE_WIDTH * column;
	height = (float)TILE_HEIGHT * row;

	//khoi tao ma tran map
	int i = 0;
	int j = 0;

	map = new int *[row];
	for (i = 0; i < row; i++)
		map[i] = new int[column];
	i = 0;
	//doc ma tran tu file
	for (map[i][j]; in >> map[i][j];)
	{
		if (j < column - 1)
			j++;
		else
		{
			j = 0;
			if (i < row - 1) i++;
			else break;
		}
	}

	int id = 1;
	int tileset_width;
	int tileset_height;

	in >> tileset_width;
	in >> tileset_height;
	in.close();

	int left, top;
	//lấy các ô hình trong tile map để lưu vào sprite
	//khi đọc ma trận map phía trên  vd map[0][0] = 1 thì sẽ lấy sprite có id = 1

	for (top = 0; top < tileset_height; top += TILE_HEIGHT)
		for (left = 0; left < tileset_width; left += TILE_WIDTH)
		{
			LPSPRITE s = new CSprite(id, left, top, left + TILE_WIDTH, top + TILE_HEIGHT, tex);
			sprites[id] = s;
			id++;
		}
}

void CTileMap::Render(float x, float y)
{
	int i, j;
	float x0, y0;
	x0 = x;
	y0 = y;

	//duyệt qua các phần tử trong ma trập map đọc từ file txt
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
		{
			int selectTile = map[i][j];  // gtrị =1, sprite có id =1
			sprites[selectTile]->Draw((int) x, (int) y);
			//tránh vẽ trên 1 hàng
			if (j < column - 1) x += TILE_WIDTH;
			else
			{
				x = x0;
				if (i < row) y += TILE_HEIGHT;
			}
		}
	
}
