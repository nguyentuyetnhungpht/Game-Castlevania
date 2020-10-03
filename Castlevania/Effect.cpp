#include "Effect.h"


CEffect::CEffect(void)
{
	manager = new CAnimationManager();
}


CEffect::~CEffect(void)
{
}

void CEffect::AddAnimation(int aniID)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniID);
	animations.push_back(ani);
}

/*
	Method of Hit effect
*/

CHitEffect::CHitEffect(float x, float y):CEffect()
{
	this->x = x;
	this->y = y;
	InitAnimation();
}

void CHitEffect::InitAnimation()
{
	CAnimations *animations = CAnimations::GetInstance();
	manager->LoadAnimation(animations, L"Data\\HitEffect_Ani.txt");
	
	for (int i = 0; i < manager->GetSize(); i++)
		this->AddAnimation(manager->GetAni(i));
}

void CHitEffect::Render()
{
	animations[0]->Render(x, y);
}