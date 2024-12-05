#include "pch.h"
#include "AStarPathFinder.h"
#include "AStarGrid.h"
#include "AStarNode.h"
#include "TimeManager.h"
#include "Object.h"

void AStarPathFinder::LateUpdate()
{
	if (m_isStopped || m_path.empty()) return;
	Vec2 myPos = m_owner->GetPos();
	if ((m_wayPoint - myPos).Length() < 3.f)
		m_path.pop_back();

	m_wayPoint = m_path.back();
	Vec2 dir = (m_wayPoint - myPos);
	dir.Normalize();

	m_owner->SetPos(myPos + dir * fDT * 100);
}

void AStarPathFinder::Render(HDC _hdc)
{
}

void AStarPathFinder::SetDestination(Vec2 _pos)
{
	AStarNode* node = m_aStarGrid->GetNodeFromPosition(_pos);
	if (node == nullptr) return;
	if (m_targetNode == nullptr)
	{
		m_targetNode = node;
		return;
	}
	else if (*node == *m_targetNode && m_path.size() > 0)
	{
		m_isStopped = false;
		return;
	}

	m_targetPos = _pos;
	m_targetNode = node;
	m_path = m_aStarGrid->GetPath(m_owner->GetPos(), m_targetPos);
	cout << m_path.size() << endl;
	Start();
}