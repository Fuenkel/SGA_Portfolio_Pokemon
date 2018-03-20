#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Probe(Image * pixel, float bgX, float bgY, float winsizeX, float winsizeY)
{
	switch (m_dir)
	{
	case DIRECTION_DOWN:
		m_probe = winsizeY + m_y + m_height;
		for (int i = m_probe - 10; i < m_probe; i++) {
			COLORREF color = GetPixel(pixel->GetMemDC(), 
				winsizeX + m_x + m_width / 2, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_y = i - m_height - winsizeY;
				break;
			}
		}
		break;
	case DIRECTION_UP:
		m_probe = winsizeY + m_y;
		for (int i = m_probe + 10; i > m_probe; i--) {
			COLORREF color = GetPixel(pixel->GetMemDC(), 
				winsizeX + m_x + m_width / 2, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_y = i - winsizeY;
				break;
			}
		}
		break;
	case DIRECTION_LEFT:
		m_probe = winsizeX + m_x;
		for (int i = m_probe + 10; i > m_probe; i--) {
			COLORREF color = GetPixel(pixel->GetMemDC(), 
				i, winsizeY + m_y + m_height / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_x = i - winsizeX;
				break;
			}
		}
		break;
	case DIRECTION_RIGHT:
		m_probe = winsizeX + m_x + m_width;
		for (int i = m_probe - 10; i < m_probe; i++) {
			COLORREF color = GetPixel(pixel->GetMemDC(), 
				i, winsizeY + m_y + m_height / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_x = i - m_width - winsizeX;
				break;
			}
		}
		break;
	}
}

//void Player::InputPlayer()
//{
//	m_name = "ÆÄÀÌ¸®";
//	m_level = 8;
//	m_maxHp = 24;
//	m_hp = 24;
//	m_atk = 15;
//	m_def = 14;
//	m_spAtk = 15;
//	m_spDef = 14;
//	m_speed = 15;
//	m_exp = 0;
//	m_maxExp = 419;
//}
