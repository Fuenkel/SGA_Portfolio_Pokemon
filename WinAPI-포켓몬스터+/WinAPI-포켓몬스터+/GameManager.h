#pragma once

#include "SIngletonBase.h"

#include "Inventory.h"
#include "Item.h"

#define ITEMCOUNT 10

struct tagInvenInfo {
	RECT invenBox;
	tagItemInfo item;
	float x, y;
};

class GameManager : public SingletonBase<GameManager>
{
private:
	Inventory inventory;
	tagInvenInfo invenInfo[ITEMCOUNT];

	tagItemInfo currentItem;

	bool showInven;
	bool showStatus;

	bool isDrag;

	RECT invenRc;
	RECT statusBox;
public:
	GameManager();
	~GameManager();

	void Init();
	void Release();

	Inventory& GetInventory() { return inventory; }

	bool GetShowInven() { return showInven; }
	void SetShowInven(bool showInven) { this->showInven = showInven; }

	bool GetShowStatus() { return showStatus; }
	void SetShowStatus(bool showStatus) { this->showStatus = showStatus; }

	bool GetIsDrag() { return isDrag; }
	void SetIsDrag(bool isDrag) { this->isDrag = isDrag; }

	tagInvenInfo& GetInvenInfo(int i) { return invenInfo[i]; }
	tagItemInfo& GetCurrentItem() { return currentItem; }

	RECT GetInvenRc() { return invenRc; }
	RECT GetStatusBox() { return statusBox; }
};

#define GAME GameManager::GetSingleton()

