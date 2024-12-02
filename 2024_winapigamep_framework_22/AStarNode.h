#pragma once

class AStarNode
{
public:
	AStarNode(int _x, int _y, Vec2 _pos, bool _isWalkable);
public:
	int X, Y;
	float G, H;
	__declspec(property(get = f)) float F;
	float f() { return G + H; }

	bool IsWalkable;
	AStarNode* ParentNode;

public:
	float GetDistanceCost(const AStarNode& neighbor);
	Vec2 GetPos() { return m_vPos; }

	void operator =(const AStarNode& b);
	bool operator ==(const AStarNode& b);
	bool operator !=(const AStarNode& b);
private:
	Vec2 m_vPos;
};