#pragma once
class Battery
{
public:
	RECT GetRect() { 
		RECT rect
		{ 
			(long)m_pos.x - m_size.x / 2,
			(long)m_pos.y - m_size.y / 2, 
			(long)m_pos.x + m_size.x / 2,
			(long)m_pos.y + m_size.y / 2 
		};
		return rect;
	};
private:
	Vec2 m_size;
	Vec2 m_pos;
};