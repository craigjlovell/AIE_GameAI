#include "KeyBoardBehaviour.h"
#include "GameObject.h"
#include "raylib.h"

KeyBoardBehaviour::KeyBoardBehaviour() : Behaviour()
{
	m_upKey = KEY_W;
	m_downKey = KEY_S;
	m_leftKey = KEY_A;
	m_rightKey = KEY_D;
	m_moveForce = 100;
}

KeyBoardBehaviour::KeyBoardBehaviour(int upKey, int downKey, int leftKey, int rightKey, float moveForce) :
	Behaviour(),
	m_upKey(upKey),
	m_downKey(downKey),
	m_leftKey(leftKey),
	m_rightKey(rightKey),
	m_moveForce(moveForce)
{

}

KeyBoardBehaviour::~KeyBoardBehaviour()
{

}

void KeyBoardBehaviour::Update(GameObject* obj, float deltaTime)
{
	if (IsKeyDown(m_upKey)) obj->ApplyForce({ 0, -m_moveForce });
	if (IsKeyDown(m_downKey)) obj->ApplyForce({ 0, m_moveForce });
	if (IsKeyDown(m_leftKey)) obj->ApplyForce({ -m_moveForce, 0 });
	if (IsKeyDown(m_rightKey)) obj->ApplyForce({ m_moveForce, 0 });
}

void KeyBoardBehaviour::Draw(GameObject* obj)
{

}     