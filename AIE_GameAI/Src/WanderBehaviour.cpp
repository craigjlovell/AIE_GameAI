#include "WanderBehaviour.h"
#include "GameObject.h"
#include "Vec2.h"


WanderBehaviour::WanderBehaviour()
{

}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject* obj, float deltaTime)
{
	Vector2 wanderCentre = Vector2Normalize(obj->GetVelocity());
	wanderCentre.x = wanderCentre.x * obj->GetMaxSpeed();
	wanderCentre.y = wanderCentre.y * obj->GetMaxSpeed();

	auto angle = (rand() % 360) * (180 / 11);

	Vector2 displace;
	displace.x = sin(angle) * obj->GetMaxForce();
	displace.y = cos(angle)* obj->GetMaxForce();

	auto wp = wanderCentre + obj->GetPosition() + displace;
}

void WanderBehaviour::Draw(GameObject* obj)
{

}

const Vector2& WanderBehaviour::GetTarget() const
{
	return m_target;
}

void WanderBehaviour::SetTarget(const Vector2& target)
{
	m_target = target;
}

const float& WanderBehaviour::GetTragetRadius() const
{
	return m_targetRadius;
}

void WanderBehaviour::SetTargetRadius(const float& radius)
{
	m_targetRadius = radius;
}

void WanderBehaviour::OnArrive(std::function<void()> callback)
{

}