#pragma once
#include "raymath.h"

class Behaviour;

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ApplyForce(const Vector2& force);

	const Vector2& GetPosition() const;
	const Vector2& GetVelocity() const;
	const float& GetFriction() const;

	Behaviour* GetBehaviour();

	void SetPosition(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& friction);

	void SetBehaviour(Behaviour* behaviour);

	const float& GetMaxSpeed() const;
	void SetMaxSpeed(const float& speed);

	const float& GetMaxForce() const;
	void SetMaxForce(const float& force);

protected:

	Vector2 m_position = { 0.0f, 0.0f };
	Vector2 m_velocity = { 0.0f, 0.0f };
	Vector2 m_acceleration = { 0.0f, 0.0f };
	float m_friction = 0.0f;

	float m_maxSpeed = { 100.0f };
	float m_maxForce = { 100.0f };

	Behaviour* m_behaviour = nullptr;

	Vector2 m_size = { 32, 32 };

private:
};