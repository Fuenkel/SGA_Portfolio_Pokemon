#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	Init();
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	inventory.ItemSetup();

	for (int i = 0; i < ITEMCOUNT; i++) {
		invenInfo[i].x = 610;
		invenInfo[i].y = 155 + 40 * i;
		invenInfo[i].invenBox = RectMake(
			invenInfo[i].x, invenInfo[i].y, 325, 40);
		invenInfo[i].item.itemKind = ITEM_EMPTY;
	}

	invenRc = RectMake(
		WINSIZEX - 400 - 50, 100, 400, 500);
	statusBox = RectMake(68, 214, 50, 50);

	inventory.SetGold(10000);

	showInven = false;
	showStatus = false;
	isDrag = false;
}

void GameManager::Release()
{
}

