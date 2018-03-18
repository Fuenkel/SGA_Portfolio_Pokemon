#pragma once

#include "Unit.h"

#define PLAYER_IDLE 1

class Player2 : public Unit
{
private:
	int m_gold;

	float m_probe;
public:
	Player2();
	~Player2();

	int& GetGold() { return m_gold; }
	void SetGold(int gold) { m_gold = gold; }

	void Init(Direction dir, float x, float y, float width, float height) {
		m_dir = dir; m_x = x; m_y = y; m_width = width; m_height = height;
	}
	void Probe(Image* pixel);
};

