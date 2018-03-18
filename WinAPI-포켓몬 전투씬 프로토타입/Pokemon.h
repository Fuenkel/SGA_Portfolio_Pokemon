#pragma once

#include "Unit.h"

enum Direction {
	DIRECTION_DOWN,
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

/*
	frame count
	idle 1
	attack 1
	movement 3
	special attack 2
	hurt 2
*/

enum Status {
	STATUS_IDLE,
	STATUS_MOVE,
	STATUS_ATTACK,
	STATUS_SPECIAL_ATTACK,
	STATUS_HURT,
	STATUS_ATTACK2
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
	Direction m_dir;
	Status m_status;

	Status m_attackStatus;

	tagBullet m_bullet[BULLETMAX];
	tagMeleeAttack m_melee;

	float m_moveFrame;
public:
	Pokemon();
	~Pokemon();

	void SetMoveFrame(float moveFrame) { m_moveFrame = moveFrame; }
	float GetMoveFrame() { return m_moveFrame; }

	Direction GetDirection() { return m_dir; }
	void SetDirection(Direction dir) { m_dir = dir; }

	Status GetStatus() { return m_status; }
	void SetStatus(Status status) { m_status = status; }

	Status GetAttackStatus() { return m_attackStatus; }
	void SetAttackStatus(Status status) { m_attackStatus = status; }

	void BulletFire();
	void BulletMove();
	tagBullet* GetBullet(int i) { return &m_bullet[i]; }

	void MeleeAttack(bool isAttack);
	tagMeleeAttack GetMeleeAttack() { return m_melee; }
};


