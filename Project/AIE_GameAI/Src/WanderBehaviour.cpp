#include "WanderBehaviour.h"
#include "GameObject.h"
#include "Vec2.h"
#include <random>
#include <time.h>
#include <math.h>

WanderBehaviour::WanderBehaviour()
{

}

WanderBehaviour::~WanderBehaviour()
{

}

void WanderBehaviour::Update(GameObject* obj, float deltaTime)
{
	float distToWp = Vector2Length(Vector2Subtract(m_wanderPoint, obj->GetPosition()));
	if (distToWp < 10 || Vector2Length(obj->GetVelocity()) == 0 || IsKeyPressed(KEY_Q))
	{
		Vector2 wanderCentre;
		Vector2 newVel = { 1, 1 };

		if (Vector2Length(obj->GetVelocity()) == 0)
		{
			obj->SetVelocity(newVel);
		}

		wanderCentre = obj->GetPosition(); // Vector2Add(Vector2Scale(Vector2Normalize(obj->GetVelocity()), obj->GetMaxSpeed()), obj->GetPosition());

		auto angle = (rand() % 360) * PI / 180.0f;

		Vector2 displace = { sin(angle) * m_targetRadius, cos(angle) * m_targetRadius };

		Vector2 wp = Vector2Add(wanderCentre, displace);

		m_wanderCenter = obj->GetPosition(); // wanderCentre;
		m_wanderPoint = wp;
	}
	
	Vector2 wtd = Vector2Scale(Vector2Normalize(Vector2Subtract(m_wanderPoint, obj->GetPosition())), obj->GetMaxForce());
	obj->ApplyForce(wtd);
}

void WanderBehaviour::Draw(GameObject* obj)
{
	DrawCircleV(m_wanderCenter, m_targetRadius, { 255, 0, 0, 128 });
	DrawCircleV(m_wanderPoint, 5, { 0, 0, 0, 128 });
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