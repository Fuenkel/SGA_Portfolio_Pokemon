#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon()
{
	for (int i = 0; i < BULLETMAX; i++) {
		m_bullet[i].isFire = false;
		m_bullet[i].moveFrame = 0;
	}

	m_moveFrame = 0;
}


Pokemon::~Pokemon()
{
}

void Pokemon::BulletFire()
{
	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].isFire == true) continue;

		m_bullet[i].isFire = true;
		switch (m_dir)
		{
		case DIRECTION_DOWN:
			m_bullet[i].x = m_x;
			m_bullet[i].y = m_y + 50;
			m_bullet[i].rc = RectMake(m_bullet[i].x, m_bullet[i].y, 50, 50);
			m_bullet[i].dir = DIRECTION_DOWN;
			break;
		case DIRECTION_UP:
			m_bullet[i].x = m_x;
			m_bullet[i].y = m_y - 50;
			m_bullet[i].rc = RectMake(m_bullet[i].x, m_bullet[i].y, 50, 50);
			m_bullet[i].dir = DIRECTION_UP;
			break;
		case DIRECTION_LEFT:
			m_bullet[i].x = m_x - 50;
			m_bullet[i].y = m_y;
			m_bullet[i].rc = RectMake(m_bullet[i].x, m_bullet[i].y, 50, 50);
			m_bullet[i].dir = DIRECTION_LEFT;
			break;
		case DIRECTION_RIGHT:
			m_bullet[i].x = m_x + 50;
			m_bullet[i].y = m_y;
			m_bullet[i].rc = RectMake(m_bullet[i].x, m_bullet[i].y, 50, 50);
			m_bullet[i].dir = DIRECTION_RIGHT;
			break;
		}
		break;
	}
}

void Pokemon::BulletMove()
{
	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].isFire == false) continue;

		switch (m_bullet[i].dir)
		{
		case DIRECTION_DOWN:
			m_bullet[i].y += 5.0f;
			break;
		case DIRECTION_UP:
			m_bullet[i].y -= 5.0f;
			break;
		case DIRECTION_LEFT:
			m_bullet[i].x -= 5.0f;
			break;
		case DIRECTION_RIGHT:
			m_bullet[i].x += 5.0f;
			break;
		}

		m_bullet[i].rc = RectMake(m_bullet[i].x, m_bullet[i].y, 50, 50);
		m_bullet[i].moveFrame += 0.25f;
		if (m_bullet[i].moveFrame >= 14)
			m_bullet[i].moveFrame = 0;
	}

	for (int i = 0; i < BULLETMAX; i++) {
		if (m_bullet[i].isFire == false) continue;

		switch (m_bullet[i].dir)
		{
		case DIRECTION_DOWN:
			if (m_bullet[i].y + 50 > WINSIZEY)
				m_bullet[i].isFire = false;
			break;
		case DIRECTION_UP:
			if (m_bullet[i].y < 0)
				m_bullet[i].isFire = false;
			break;
		case DIRECTION_LEFT:
			if (m_bullet[i].x < 0)
				m_bullet[i].isFire = false;
			break;
		case DIRECTION_RIGHT:
			if (m_bullet[i].x + 50 > WINSIZEX)
				m_bullet[i].isFire = false;
			break;
		}
	}
}

void Pokemon::MeleeAttack(bool isAttack)
{
	if (isAttack) {
		m_melee.isAttack = true;
		m_melee.dir = m_dir;
		switch (m_melee.dir)
		{
		case DIRECTION_DOWN:
			m_melee.rc = RectMake(m_x, m_y + 50, 50, 50);
			break;
		case DIRECTION_UP:
			m_melee.rc = RectMake(m_x, m_y - 50, 50, 50);
			break;
		case DIRECTION_LEFT:
			m_melee.rc = RectMake(m_x - 50, m_y, 50, 50);
			break;
		case DIRECTION_RIGHT:
			m_melee.rc = RectMake(m_x + 50, m_y, 50, 50);
			break;
		}
	}
	else {
		m_melee.isAttack = false;
	}
}
