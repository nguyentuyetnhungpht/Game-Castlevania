#pragma once
#include <unordered_map>
#include "Sprites.h"

using namespace std;
class CAnimationManager
{
	unordered_map<int, int> aniDB;
public:
	CAnimationManager(void);
	~CAnimationManager(void);

	void LoadAnimation(CAnimations *animations, LPCWSTR fileName);

	int GetSize() {return aniDB.size();}
	int GetAni(int ani) {return aniDB[ani];}
};

