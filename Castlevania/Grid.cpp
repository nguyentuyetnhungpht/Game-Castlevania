#include "Grid.h"
#include "Game.h"
#include "debug.h"

int CCell::AddObject(LPGAMEOBJECT object)
{
	objects.push_back(object);
	return objects.size() - 1;
}

CGrid::CGrid(float width, float height)
{
	int row = height / CELL_HEIGHT;
	int column = width / CELL_WIDTH;

	cell = new CCell *[row];
	for (int i = 0; i < column; i++)
		cell[i] = new CCell [column];
}

void CGrid::InitGrid(vector<LPGAMEOBJECT> objects)
{
	for (UINT i = 0; i < objects.size(); i++)
	{
		
		float x, y;
		objects[i]->GetPosition(x, y);
		int row, column;
		
		row = (int) (y / CELL_HEIGHT);
		column = (int) (x / CELL_WIDTH);

		//DebugOut(L"row %d, column %d\n", row, column);
		cell[row][column].AddObject(objects[i]);		
	}
}

CCell CGrid::GetCell(float x, float y)
{
	int row = y / VIEWPORT_HEIGHT;
	int column = x / VIEWPORT_WIDTH;
	
	return cell[row][column];
}

void CGrid::GetListObject(vector<LPGAMEOBJECT> &objects)
{
	CGame *game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);
	objects.clear();
	int start_row, end_row;
	int start_column, end_column;
	
	start_row = (int) (cy / CELL_HEIGHT);
	end_row = (int) (cy + VIEWPORT_HEIGHT) / CELL_HEIGHT;
	
	start_column = (int) (cx / CELL_WIDTH);
	end_column = (int) (cx + VIEWPORT_WIDTH) / CELL_WIDTH;
	
	int i;
	int j;
	
	for (i = start_row; i <= end_row; i++)
		for (j = start_column; j <= end_column; j++)
		{	
			vector<LPGAMEOBJECT> objs = cell[i][j].GetObjects();
			for (UINT k = 0; k < objs.size(); k++)
				objects.push_back(objs[k]);
			/*vector<LPGAMEOBJECT>::iterator it = objects.end();
			objects.insert(it, 
							cell[i][j].GetObjects().begin(),
							cell[i][j].GetObjects().end());*/
		}
}