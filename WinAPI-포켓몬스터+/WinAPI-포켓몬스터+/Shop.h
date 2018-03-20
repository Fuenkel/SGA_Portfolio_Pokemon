#pragma once

#include "Item.h"

class Shop
{
private:
	vector<tagItemInfo> m_vItem;
	vector<tagItemInfo>::iterator m_viItem;
public:
	Shop();
	~Shop();

	void ItemSetup();
	void AddItem(tagItemInfo item);
	tagItemInfo BuyItem(int num, int& gold);

	tagItemInfo GetItem(int num) { return m_vItem[num]; }
	int GetItemCount() { return m_vItem.size(); }
};

