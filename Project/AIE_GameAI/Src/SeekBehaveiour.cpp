#include "SeekBehaviour.h"
#include "GameObject.h"

SeekBehaviour::SeekBehaviour() : Behaviour()
{

}

SeekBehaviour::~SeekBehaviour()
{

}

void SeekBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToTarget = Vector2Distance(obj->GetPosition(), m_target);

	if (distToTarget < m_targetRadius) 
	{
		if (m_onArriveFn)
		{
			m_onArriveFn();
		}
	}

	Vector2 heading = Vector2Add(obj->GetPosition(), obj->GetVelocity());

	Vector2 desiredDirToTarget = Vector2Normalize(Vector2Subtract(m_target, obj->GetPosition()));
	Vector2 desiredVelocity = Vector2Scale(desiredDirToTarget, obj->GetMaxSpeed());
	Vector2 targetForcePos = Vector2Add(desiredVelocity, obj->GetPosition());
	Vector2 forceDir = Vector2Scale(Vector2Normalize(Vector2Subtract(targetForcePos, heading)), obj->GetMaxForce());


	obj->ApplyForce(forceDir);
}

void SeekBehaviour::Draw(GameObject* obj)
{
	DrawCircle(m_target.x, m_target.y, m_targetRadius, GREEN);
	DrawCircle(m_target.x, m_target.y, 4, DARKGREEN);
}

const Vector2& SeekBehaviour::GetTarget() const
{
	return m_target;
}

const float& SeekBehaviour::GetTragetRadius() const
{
	return m_targetRadius;
}

void SeekBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

void SeekBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void SeekBehaviour::OnArrive(std::function<void()> callback)
{
	m_onArriveFn = callback;
}