/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Simon.h"
#include "Resource.h"
#include "Level1.h"

#define WINDOW_CLASS_NAME L"Game_Window"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 271
#define SCREEN_HEIGHT 256

#define MAX_FRAME_RATE 120

#define OFFSET_TO_STAND_UP 7.0f
CGame *game;
CSimon *simon;
CLevel1 *level1;

DWORD startFight;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	float tmpx, tmpy;
	float sx, sy;
	switch(KeyCode)
	{
	case DIK_UP:
		if(game->IsKeyDown(DIK_DOWN) && simon->GetState() != SIMON_STATE_AUTO)
		{
			simon->GetPosition(tmpx, tmpy);
			simon->SetPosition(tmpx, tmpy - OFFSET_TO_STAND_UP);
		}
		break;
	case DIK_DOWN:
		if (!game->IsKeyDown(DIK_UP) && simon->GetState() != SIMON_STATE_AUTO)
		{
			simon->GetPosition(tmpx, tmpy);		
			simon->SetPosition(tmpx, tmpy + OFFSET_TO_STAND_UP);
		}
		break;
	case DIK_LEFT:
		if (simon->GetState() != SIMON_STATE_AUTO)
		simon->nx = -1;
		break;
	case DIK_RIGHT:
		if (simon->GetState() != SIMON_STATE_AUTO)
		simon->nx = 1;
		break;
	case DIK_SPACE:
		simon->SetPosition(100.f, 80.0f);
		break;
	case DIK_S:
		if (simon->GetState() != SIMON_STATE_FIGHTING && simon->GetState() != SIMON_STATE_KNEE
			&& simon->GetState()  != SIMON_STATE_KNEE_FIGHTING && simon->GetState() != SIMON_STATE_AUTO)
			simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A:
		if (simon->GetState() != SIMON_STATE_AUTO)		
		{
			CWhip *whip = simon->GetWhip();
			simon->GetPosition(sx, sy);
			if (simon->nx > 0)
				whip->SetPosition(sx, sy + 10.0f);
			else whip->SetPosition(sx + SIMON_BBOX_WIDTH, sy + 10.0f);

			whip->nx = simon->nx;
			whip->SetStart(GetTickCount());
			simon->SetWhip(whip);

			if (simon->GetState() != SIMON_STATE_USING_SUBWEAPON && game->IsKeyDown(DIK_UP))
			{
				CSubWeapon *subweapon = simon->GetSubWeapon();
				subweapon->SetPosition(simon->x, simon->y);
				subweapon->nx = simon->nx;
				subweapon->SetState(ITEM_STATE_SUBWEAPON);
				simon->SetSubWeapon(subweapon);
				simon->SetState(SIMON_STATE_USING_SUBWEAPON);
			}
			else if (simon->GetState() != SIMON_STATE_KNEE_FIGHTING && game->IsKeyDown(DIK_DOWN))
				simon->SetState(SIMON_STATE_KNEE_FIGHTING);
			else if (simon->GetState() != SIMON_STATE_FIGHTING)
				simon->SetState(SIMON_STATE_FIGHTING);

			startFight = GetTickCount();
		}
		break;
	}
	
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	float tmpx, tmpy;
	switch(KeyCode)
	{
	case DIK_UP:
		if (game->IsKeyDown(DIK_DOWN) && simon->GetState() != SIMON_STATE_AUTO)
		{
			simon->GetPosition(tmpx, tmpy);
			simon->SetPosition(tmpx, tmpy + OFFSET_TO_STAND_UP);
		}
		break;
	case DIK_DOWN:
		if (!game->IsKeyDown(DIK_UP) && simon->GetState() != SIMON_STATE_AUTO)
		{
			simon->GetPosition(tmpx, tmpy);
			simon->SetPosition(tmpx, tmpy - OFFSET_TO_STAND_UP);
		}
		break;
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (simon->GetState() != SIMON_STATE_AUTO)
	{
		if (game->IsKeyDown(DIK_DOWN) && simon->GetState() != SIMON_STATE_KNEE_FIGHTING) 
		{	
			simon->SetState(SIMON_STATE_KNEE);
		}
		else if(game->IsKeyDown(DIK_LEFT) && simon->GetState() != SIMON_STATE_FIGHTING) 
			simon->SetState(SIMON_STATE_WALKING_LEFT);
		else if (game->IsKeyDown(DIK_RIGHT) && simon->GetState() != SIMON_STATE_FIGHTING) 
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		else if (GetTickCount() - startFight > 450) 
		{
			if(!game->IsKeyDown(DIK_DOWN))
			{
				if (simon->GetState() == SIMON_STATE_USING_SUBWEAPON)
					simon->SetStartSub();
				simon->SetState(SIMON_STATE_IDLE);
			}
			else 
				simon->SetState(SIMON_STATE_KNEE);
		}
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CResource *resource = new CResource();
	resource->LoadTextures();
	resource->LoadSprites();
	
	CGame * game = CGame::GetInstance();
	game->SetCamera(0.0f, 0.0f);

	simon = new CSimon();
	simon->SetPosition(10.0f, 80.0f);

	level1 = CLevel1::GetInstance();
	level1->SetScene(SCENE_1);
	level1->LoadMap();
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	level1->Update(dt, simon);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		level1->Render(simon);

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}