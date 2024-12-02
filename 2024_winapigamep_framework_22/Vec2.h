#pragma once
#include<assert.h>
struct Vec2
{
public:
	Vec2() = default;
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vec2(const Vec2& _other) : x(_other.x), y(_other.y) {}
public:
	Vec2 operator + (const Vec2& _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator - (const Vec2& _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (const Vec2& _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator * (float _val)
	{
		return Vec2(x * _val, y * _val);
	}
	Vec2 operator / (const Vec2& _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	void operator+=(const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
	}
	void operator-=(const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
	}
	float LengthSquared()
	{
		return x * x + y * y;
	}
	float Length()
	{
		return ::sqrt(LengthSquared());
	}
	Vec2 Normalize()
	{
		float len = Length();
		// 0이면 안돼.
		if (len < FLT_EPSILON)
			return *this;
		x /= len;
		y /= len;
		return *this;
	}
	float Dot(Vec2 _other)
	{
		return x * _other.x + y * _other.y;
	}
	float Cross(Vec2 _other)
	{
		// z축이 나온다고 가정
		return x * _other.y - y * _other.x;
	}
public:
	float x = 0.f;
	float y = 0.f;
};

struct Vec2Int
{
    Vec2Int() {}
    Vec2Int(int x, int y) : x(x), y(y) {}
    Vec2Int(POINT pt) : x(pt.x), y(pt.y) {}
    Vec2Int(const Vec2& _pos) : x(_pos.x), y(_pos.y) {}

    Vec2Int operator+(const Vec2Int& other)
    {
        Vec2Int ret;
        ret.x = x + other.x;
        ret.y = y + other.y;
        return ret;
    }

    Vec2Int operator-(const Vec2Int& other)
    {
        Vec2Int ret;
        ret.x = x - other.x;
        ret.y = y - other.y;
        return ret;
    }

    Vec2Int operator*(int value)
    {
        Vec2Int ret;
        ret.x = x * value;
        ret.y = y * value;
        return ret;
    }

    bool operator<(const Vec2Int& other) const
    {
        if (x != other.x)
            return x < other.x;

        return y < other.y;
    }

    bool operator>(const Vec2Int& other) const
    {
        if (x != other.x)
            return x > other.x;

        return y > other.y;
    }

    bool operator==(const Vec2Int& other)
    {
        return x == other.x && y == other.y;
    }

    void operator+=(const Vec2Int& other)
    {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vec2Int& other)
    {
        x -= other.x;
        y -= other.y;
    }

    int LengthSquared()
    {
        return x * x + y * y;
    }

    float Length()
    {
        return (float)::sqrt(LengthSquared());
    }

    int Dot(Vec2Int other)
    {
        return x * other.x + y * other.y;
    }

    int Cross(Vec2Int other)
    {
        return x * other.y - y * other.x;
    }

    int x = 0;
    int y = 0;
};
