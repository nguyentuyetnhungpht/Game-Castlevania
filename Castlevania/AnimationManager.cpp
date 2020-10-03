#include "AnimationManager.h"
#include "AnimationData.h"
#include "LoadingData.h"

CAnimationManager::CAnimationManager(void)
{
}


CAnimationManager::~CAnimationManager(void)
{
}

void CAnimationManager::LoadAnimation(CAnimations *animations, LPCWSTR fileName)
{
	int j = 0;
	vector<CAnimationData *> listAniData;
	CLoadingData::LoadAnimationsDataFromFile(listAniData, fileName);
	
	int tempAniID = listAniData[0]->GetAnimationID();
	LPANIMATION ani = new CAnimation(150);

	CAnimationData *aniData = NULL;
	for (UINT i = 0; i < listAniData.size(); i++)
	{
		aniData = listAniData[i];
		if (tempAniID == aniData->GetAnimationID())
			ani->Add(aniData->GetSpriteID(), aniData->GetTime());
		else
		{
			tempAniID = aniData->GetAnimationID();
			aniData = listAniData[i - 1];
			animations->Add(aniData->GetAnimationID(), ani);
			aniDB[j] = aniData->GetAnimationID();
			j++;
			ani = new CAnimation(100);
			aniData = listAniData[i];
			ani->Add(aniData->GetSpriteID() , aniData->GetTime());
		}
	}
	
	animations->Add(aniData->GetAnimationID(), ani);
	aniDB[j] = aniData->GetAnimationID();
	j++;
}