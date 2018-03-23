#pragma once

#include "Unit.h"

#define PLAYER_IDLE 1

class Player : public Unit
{
private:
	float m_probe;

	Image* portrait;
	Image* ani[6];
	int aniMaxNum[6];
public:
	Player();
	~Player();

	void Init(Direction dir, float x, float y, float width, float height) {
		m_dir = dir; m_x = x; m_y = y; m_width = width; m_height = height;
	}
	void Probe(Image* pixel, float bgX, float bgY, float winsizeX, float winsizeY);
	//void InputPlayer();

	void SetAni(int status, Image* img) { ani[status] = img; }
	Image* GetAni(int status) { return ani[status]; }

	void SetAniMaxNum(int index, int maxNum) { aniMaxNum[index] = maxNum; }
	int GetAniMaxNum(int index) { return aniMaxNum[index]; }

	Image* GetPortrait() { return portrait; }
	void SetPortrait(Image* portrait) { this->portrait = portrait; }
};

