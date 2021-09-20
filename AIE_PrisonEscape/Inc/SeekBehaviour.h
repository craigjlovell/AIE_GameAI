#pragma once
#include "Behaviour.h"
#include "raymath.h"
#include <functional>

class SeekBehaviour : public Behaviour
{
public:

	SeekBehaviour();
	virtual ~SeekBehaviour();

	virtual void Update(GameObject* obj, float dt);
	virtual void Draw(GameObject* obj);

	const Vector2& GetTarget() const;
	void SetTarget(const Vector2& target);

	const float& GetTragetRadius() const;
	void SetTargetRadius(const float& radius);

	void OnArrive(std::function<void()> callback);

protected:

	Vector2 m_target;
	float m_targetRadius = 10.0f;

	std::function<void()> m_onArriveFn;

private:
};