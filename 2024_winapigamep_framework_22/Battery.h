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
	void SetSize(Vec2 _size)
	{
		m_size = _size;
	}
	void SetPos(Vec2 _pos)
	{
		m_pos = _pos;
	}
private:
	Vec2 m_size;
	Vec2 m_pos;
};