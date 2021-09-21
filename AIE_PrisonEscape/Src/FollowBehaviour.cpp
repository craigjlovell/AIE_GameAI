#include "FollowBehaviour.h"
#include "GameObject.h"

#include <iostream>

FollowBehaviour::FollowBehaviour() : Behaviour()
{

}

FollowBehaviour::~FollowBehaviour()
{

}

void FollowBehaviour::Update(GameObject* obj, float dt)
{
	int closestPathIndex = 0;
	float closestDistance = 1000000000;

	// TODO:
	// get the index value of the point in the path that is closest to the obj (guard).
	for (int i = 0; i < m_path.size(); i++)
	{
		auto dist = Vector2Distance(obj->GetPosition(), m_path[i]);
		if (dist < closestDistance)
		{
			closestDistance = dist;
			closestPathIndex = i + m_pathDir;			
		}
	}

	if (closestPathIndex >= (int)m_path.size())
	{
		closestPathIndex = m_path.size() - 1;
		m_pathDir = -1;
	}
	else if (closestPathIndex < 0)
	{
		closestPathIndex = 0;
		m_pathDir = 1;
	}

	std::cout << closestPathIndex << std::endl;

	m_pathIndex = closestPathIndex;
	Vector2 pos1 = m_path[m_pathIndex];

	Vector2 dirToTarget = Vector2Scale(Vector2Normalize(Vector2Subtract(pos1, obj->GetPosition())), obj->GetMaxForce());
	obj->ApplyForce(dirToTarget);
	float distToTarget = Vector2Distance(pos1, obj->GetPosition());

}

void FollowBehaviour::Draw(GameObject* obj)
{
	for (auto pathpoint : m_path)
	{
		if (IsKeyDown(KEY_Z))
		{
			DrawCircle(pathpoint.x, pathpoint.y, 10, PINK);
		}
	}
}

const std::vector<Vector2>& FollowBehaviour::GetPath() const
{
	return m_path;
}

void FollowBehaviour::SetPath(std::vector<Vector2>& path)
{
	m_path = path;
}
