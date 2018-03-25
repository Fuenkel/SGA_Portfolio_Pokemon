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

enum EffectKind {
	EFFECT_ELECTRICITY,
	EFFECT_FIRE,
	EFFECT_WATER,
	EFFECT_GRASS,
	EFFECT_END
};

#define BULLETMAX 10

struct tagBullet {
	RECT rc;
	Direction dir;
	bool isFire;
	float moveFrame;
	float x, y;
};

struct tagMeleeAttack {
	RECT rc;
	Direction dir;
	bool isAttack;
};

class Pokemon : public Unit
{
private:
	tagItemInfo m_equipItem;

	Status m_status;

	Status m_attackStatus;

	tagBullet m_bullet[BULLETMAX];
	tagMeleeAttack m_melee;

	Image* portrait[2];
	Image* model;
	Image* ani[6];
	int aniMaxNum[6];

	int portraitNum;
	int effectNum;

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

	Image* GetPortrait(int i) { return portrait[i]; }
	void SetPortrait(int i, Image* portrait) { this->portrait[i] = portrait; }

	Image* GetModel() { return model; }
	void SetModel(Image* model) { this->model = model; }

	void Init(Direction dir, float x, float y, float width, float height) {
		m_dir = dir; m_x = x; m_y = y; m_width = width; m_height = height;
	}

	void SetEffectNum(int num) { effectNum = num; }
	int GetEffectNum() { return effectNum; }

	void SetAni(Status status, Image* img) { ani[status] = img; }
	Image* GetAni(Status status) { return ani[status]; }

	void SetAniMaxNum(int index, int maxNum) { aniMaxNum[index] = maxNum; }
	int GetAniMaxNum(int index) { return aniMaxNum[index]; }

	void SetDied(bool isDied) { this->isDied = isDied; }
	bool GetDied() { return isDied; }

	void SetAlpha(float alpha) { this->alpha = alpha; }
	float GetAlpha() { return alpha; }
	void AddAlpha(float num) { alpha += num; }

	Status GetAttackStatus() { return m_attackStatus; }
	void SetAttackStatus(Status status) { m_attackStatus = status; }

	void BulletFire();
	void BulletMove();
	tagBullet* GetBullet(int i) { return &m_bullet[i]; }

	void MeleeAttack(bool isAttack);
	tagMeleeAttack GetMeleeAttack() { return m_melee; }

	void SetPortraitNum(int num) { this->portraitNum = num; }
	int GetPortraitNum() { return portraitNum; }
};

