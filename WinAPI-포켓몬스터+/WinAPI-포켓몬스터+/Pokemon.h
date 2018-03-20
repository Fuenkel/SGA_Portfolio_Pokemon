#pragma once

#include "Unit.h"

#include "Item.h"

class Pokemon : public Unit
{
private:
	tagItemInfo m_equipItem;

	Image* img;
public:
	Pokemon();
	~Pokemon();

	void EquipItem(int num);

	tagItemInfo GetEquipItem() { return m_equipItem; }
	void SetEquipItem(tagItemInfo equipItem) { m_equipItem = equipItem; }

	Image* GetImage() { return img; }
	void SetImage(Image* img) { this->img = img; }
};

