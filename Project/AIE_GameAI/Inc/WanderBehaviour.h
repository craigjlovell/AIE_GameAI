#pragma once
#include "Behaviour.h"
#include "raymath.h"
#include <functional>

class Vec2;

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject* obj, float deltaTime);
	virtual void Draw(GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTragetRadius() const;
	void SetTargetRadius(const float& radius);

protected:

	Vector2 m_target;
	float m_targetRadius = 1.0f;

	Vector2 m_wanderCenter = { 0, 0 };
	Vector2 m_wanderPoint = { 0, 0 };

private:
};
