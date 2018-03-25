#pragma once

#include "Item.h"

class Inventory
{
protected:
	vector<tagItemInfo> m_vItem;
	vector<tagItemInfo>::iterator m_viItem;

	//tagItemInfo m_equipItem;

	int m_gold;
public:
	Inventory();
	~Inventory();

	void ItemSetup();
	void AddItem(tagItemInfo item);
	tagItemInfo SellItem(int num, int& gold);
	void UseItem(int num);

	void DeleteItem(int num);
	tagItemInfo GetItem(int num) { return m_vItem[num]; }
	int GetItemCount() { return m_vItem.size(); }

	//void EquipItem(int num);

	//tagItemInfo GetEquipItem() { return m_equipItem; }
	//void SetEquipItem(tagItemInfo equipItem) { m_equipItem = equipItem; }

	int& GetGold() { return m_gold; }
	void SetGold(int gold) { m_gold = gold; }

};

