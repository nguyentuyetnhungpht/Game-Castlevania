#pragma once
#include <string>
#include "Sprites.h"
using namespace std;

#define TILE_WIDTH 32
#define TILE_HEIGHT	32

class CTileMap
{
	int **map; //lưu ma trận trong file .txt khi tạo tile map
	int row;
	int column;

	float width;
	float height;

	unordered_map<int, LPSPRITE> sprites;
public:
	void GetSize(float &width, float &height) { width = this->width; height = this->height; }
	void LoadTileMap(string fileName, LPDIRECT3DTEXTURE9 tex);
	void Render(float x, float y);
};

