#include "pch.h"
#include "AStarNode.h"

AStarNode::AStarNode(int _x, int _y, Vec2 _pos, bool _isWalkable)
{
	X = _x;
	Y = _y;
	m_vPos = _pos;
	G = 0;
	H = 0;
	IsWalkable = _isWalkable;
	ParentNode = nullptr;
}

float AStarNode::GetDistanceCost(const AStarNode& node)
{
	int disX = this->X - node.X;
	int disY = this->Y - node.Y;

	//if (disX > disY) return 1.4f * disY + (disX - disY);
	//return 1.4f * disX + (disY - disX);
	return disX * disX + disY * disY;
}

void AStarNode::operator=(const AStarNode& b)
{
	X = b.X;
	Y = b.Y;
	G = b.G;
	H = b.H;
	IsWalkable = b.IsWalkable;
	ParentNode = b.ParentNode;
}

bool AStarNode::operator==(const AStarNode& b)
{
	return X == b.X && Y == b.Y;
}

bool AStarNode::operator!=(const AStarNode& b)
{
	return !(*this == b);
}