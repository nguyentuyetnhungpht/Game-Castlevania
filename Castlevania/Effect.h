#pragma once
#include <vector>
#include "Sprites.h"
#include "AnimationManager.h"
using namespace std;

class CEffect
{
protected:
	float x, y;
	vector<LPANIMATION> animations;
	CAnimationManager *manager;

public:
	CEffect(void);
	~CEffect(void);
	void SetPosition(float x, float y) {this->x = x; this->y = y;}
	void AddAnimation(int aniID);
	virtual void Render() = 0;
};

#define OFFSET_EFFECT_X	5
#define OFFSET_EFFECT_Y	5

class CHitEffect : public CEffect
{
	void InitAnimation();
public:
	CHitEffect(float x, float y);

	void Render();
};
