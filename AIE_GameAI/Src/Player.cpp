#include "Player.h"
#include "KeyBoardBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"

Player::Player()
{
	m_kbBehaviour = new KeyBoardBehaviour();

	m_seekBehaviour = new SeekBehaviour();	
	m_seekBehaviour->SetTargetRadius(25.0f);
	m_seekBehaviour->OnArrive([this]()
		{
			SetBehaviour(m_kbBehaviour);
		});

	m_fleeBehaviour = new FleeBehaviour();
	m_fleeBehaviour->SetTargetRadius(25.0f);
	m_fleeBehaviour->OnArrive([this]()
		{
			SetBehaviour(m_kbBehaviour);
		});

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(25.0f);
	m_wanderBehaviour->OnArrive([this]()
		{
			SetBehaviour(m_kbBehaviour);
		});

	SetBehaviour(m_kbBehaviour);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_seekBehaviour;
	delete m_fleeBehaviour;
	delete m_wanderBehaviour;
	delete m_kbBehaviour;
}

void Player::Update(float deltaTime)
{

	if (IsMouseButtonPressed(0))
	{
		m_seekBehaviour->SetTarget(GetMousePosition() );
		SetBehaviour(m_seekBehaviour);
	}
	else if (IsMouseButtonPressed(1))
	{
		m_fleeBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_fleeBehaviour);
	}
	else if (KeyboardKey(IsKeyPressed(KEY_ONE)))
	{
		m_wanderBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_wanderBehaviour);
	}

	GameObject::Update(deltaTime);
}

void Player::Draw()
{
	GameObject::Draw();
}