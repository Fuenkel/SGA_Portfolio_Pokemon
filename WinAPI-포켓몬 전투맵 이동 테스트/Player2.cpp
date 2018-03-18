#include "stdafx.h"
#include "Player2.h"


Player2::Player2()
{
}


Player2::~Player2()
{
}

void Player2::Probe(Image* pixel)
{
	switch (m_dir)
	{
	case DIRECTION_DOWN:
		m_probe = m_y + m_height;
		for (int i = m_probe - 10; i < m_probe; i++) {
			COLORREF color = GetPixel(pixel->GetMemDC(), m_x + m_width / 2, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_y = i - m_height;
				break;
			}
		}
		break;
	case DIRECTION_UP:
		m_probe = m_y;
		for (int i = m_probe + 10; i > m_probe; i--) {
			COLORREF color = GetPixel(pixel->GetMemDC(), m_x + m_width / 2, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_y = i;
				break;
			}
		}
		break;
	case DIRECTION_LEFT:
		m_probe = m_x;
		for (int i = m_probe + 10; i > m_probe; i--) {
			COLORREF color = GetPixel(pixel->GetMemDC(), i, m_y + m_height / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_x = i;
				break;
			}
		}
		break;
	case DIRECTION_RIGHT:
		m_probe = m_x + m_width;
		for (int i = m_probe - 10; i < m_probe; i++) {
			COLORREF color = GetPixel(pixel->GetMemDC(), i, m_y + m_height / 2);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 255) {
				m_x = i - m_width;
				break;
			}
		}
		break;
	}


}
