#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon()
{
	m_equipItem.itemKind = ITEM_EMPTY;
	isDied = false;
	alpha = 255;

	for (int i = 0; i < BULLETMAX; i++) {
		m_bullet[i].isFire = false;
		m_bullet[i].moveFrame = 0;
	}

	m_moveFrame = 0;

	effectNum = EFFECT_END;
}


Pokemon::~Pokemon()
{

}

void Pokemon::EquipItem(int num) {
	if (num == -1) {
		tagItemInfo beforeItem;
		beforeItem = GetEquipItem();

		tagItemInfo emptyItem;
		emptyItem.itemKind = ITEM_EMPTY;
		SetEquipItem(emptyItem);

		if (beforeItem.itemKind != ITEM_EMPTY)
			GAME->GetInventory().AddItem(beforeItem);
	}
	else {
		tagItemInfo beforeItem;
		//m_viItem = m_vItem.begin() + num;

		beforeItem = GetEquipItem();
		//SetEquipItem(*m_viItem);
		SetEquipItem(GAME->GetInventory().GetItem(num));
		//m_vItem.erase(m_viItem);
		GAME->GetInventory().DeleteItem(num);
		if (beforeItem.itemKind != ITEM_EMPTY)
			GAME->GetInventory().AddItem(beforeItem);
	}
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

		switch (effectNum)
		{
		case EFFECT_ELECTRICITY:
			m_bullet[i].moveFrame = 0;
			break;
		case EFFECT_FIRE:
			switch (m_bullet[i].dir)
			{
			case DIRECTION_DOWN:
				m_bullet[i].moveFrame = 0;
				break;
			case DIRECTION_UP:
				m_bullet[i].moveFrame = 3;
				break;
			case DIRECTION_LEFT:
				m_bullet[i].moveFrame = 6;
				break;
			case DIRECTION_RIGHT:
				m_bullet[i].moveFrame = 9;
				break;
			}
			break;
		case EFFECT_WATER:
			switch (m_bullet[i].dir)
			{
			case DIRECTION_DOWN:
				m_bullet[i].moveFrame = 0;
				break;
			case DIRECTION_UP:
				m_bullet[i].moveFrame = 2;
				break;
			case DIRECTION_LEFT:
				m_bullet[i].moveFrame = 4;
				break;
			case DIRECTION_RIGHT:
				m_bullet[i].moveFrame = 6;
				break;
			}
			break;
		case EFFECT_GRASS:
			m_bullet[i].moveFrame = 0;
			break;
		case EFFECT_END:
			break;
		default:
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

		switch (effectNum)
		{
		case EFFECT_ELECTRICITY:
			m_bullet[i].moveFrame += 0.25f;
			if (m_bullet[i].moveFrame >= 14)
				m_bullet[i].moveFrame = 0;
			break;
		case EFFECT_FIRE:
			m_bullet[i].moveFrame += 0.1f;
			switch (m_bullet[i].dir)
			{
			case DIRECTION_DOWN:
				if (m_bullet[i].moveFrame >= 3)
					m_bullet[i].moveFrame = 0;
				break;
			case DIRECTION_UP:
				if (m_bullet[i].moveFrame >= 6)
					m_bullet[i].moveFrame = 3;
				break;
			case DIRECTION_LEFT:
				if (m_bullet[i].moveFrame >= 9)
					m_bullet[i].moveFrame = 6;
				break;
			case DIRECTION_RIGHT:
				if (m_bullet[i].moveFrame >= 12)
					m_bullet[i].moveFrame = 9;
				break;
			}
			break;
		case EFFECT_WATER:
			m_bullet[i].moveFrame += 0.1f;
			switch (m_bullet[i].dir)
			{
			case DIRECTION_DOWN:
				if (m_bullet[i].moveFrame >= 2)
					m_bullet[i].moveFrame = 0;
				break;
			case DIRECTION_UP:
				if (m_bullet[i].moveFrame >= 4)
					m_bullet[i].moveFrame = 2;
				break;
			case DIRECTION_LEFT:
				if (m_bullet[i].moveFrame >= 6)
					m_bullet[i].moveFrame = 4;
				break;
			case DIRECTION_RIGHT:
				if (m_bullet[i].moveFrame >= 8)
					m_bullet[i].moveFrame = 6;
				break;
			}
			break;
		case EFFECT_GRASS:
			m_bullet[i].moveFrame += 0.25f;
			if (m_bullet[i].moveFrame >= 20)
				m_bullet[i].moveFrame = 0;
			break;
		case EFFECT_END:
			break;
		default:
			break;
		}
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
