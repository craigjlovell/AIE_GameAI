#include "GameObject.h"
#include "Behaviour.h"
#include "Vec2.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{

	


	if (m_behaviour != nullptr) m_behaviour->Update(this, deltaTime);

	ApplyForce(Vector2Scale(Vector2Negate(m_velocity), m_friction));

	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));

	float speed = Vector2Length(m_velocity);
	if (speed > GetMaxSpeed())
		m_velocity = Vector2Scale(Vector2Normalize(m_velocity), GetMaxSpeed());

	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));
	m_acceleration = { 0, 0 };
}

void GameObject::Draw()
{

	if (m_behaviour != nullptr) m_behaviour->Draw(this);

	Vector2 heading = Vector2Add(m_position, m_velocity);

	DrawCircle(m_position.x, m_position.y, 8, RED);
	DrawLine(m_position.x, m_position.y, heading.x, heading.y, GOLD);
}

void GameObject::ApplyForce(const Vector2& force)
{
	m_acceleration = Vector2Add(m_acceleration, force);
}

// Getters
const Vector2& GameObject::GetPosition() const
{
	return m_position;
}

const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}

const float& GameObject::GetFriction() const
{
	return m_friction;
}

Behaviour* GameObject::GetBehaviour()
{
	return m_behaviour;
}

// Setters
void GameObject::SetPosition(const Vector2& pos)
{
	m_position = pos;
}

void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}

void GameObject::SetFriction(const float& friction)
{
	m_friction = friction;
}

void GameObject::SetBehaviour(Behaviour* behaviour)
{
	m_behaviour = behaviour;
}

const float& GameObject::GetMaxSpeed() const
{
	return m_maxSpeed;
}

void GameObject::SetMaxSpeed(const float& speed)
{
	m_maxSpeed = speed;
}

const float& GameObject::GetMaxForce() const
{
	return m_maxForce;
}

void GameObject::SetMaxForce(const float& force)
{
	m_maxForce = force;
}