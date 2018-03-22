#pragma once

#include "Unit.h"

#include "Item.h"

enum Status {
	STATUS_IDLE,
	STATUS_MOVE,
	STATUS_HURT,
	STATUS_ATTACK,
	STATUS_SPECIAL_ATTACK,
	STATUS_ATTACK2
};

class Pokemon : public Unit
{
private:
	tagItemInfo m_equipItem;

	Status m_status;

	Image* img;
	Image** ani;
	int num;

	bool isDied;
	float alpha;
public:
	Pokemon();
	~Pokemon();

	void EquipItem(int num);

	tagItemInfo GetEquipItem() { return m_equipItem; }
	void SetEquipItem(tagItemInfo equipItem) { m_equipItem = equipItem; }

	void SetStatus(Status status) { m_status = status; }
	Status GetStatus() { return m_status; }

	Image* GetImage() { return img; }
	void SetImage(Image* img) { this->img = img; }

	void Init(Direction dir, float x, float y, float width, float height) {
		m_dir = dir; m_x = x; m_y = y; m_width = width; m_height = height;
	}

	void InitAni(int num);
	void SetAni(Status status, Image* img) { ani[status] = img; }
	Image* GetAni(Status status) { return ani[status]; }

	void SetDied(bool isDied) { this->isDied = isDied; }
	bool GetDied() { return isDied; }

	void SetAlpha(float alpha) { this->alpha = alpha; }
	float GetAlpha() { return alpha; }
	void AddAlpha(float num) { alpha += num; }
};

