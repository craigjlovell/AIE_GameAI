#include "Guards.h"
#include "KeyBoardBehaviour.h"
#include "WanderBehaviour.h"
#include "Assets.h"
#include <GameScreen.h>

Guards::Guards()
{
	m_kbBehaviour = new KeyBoardBehaviour();

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(50.0f);

	SetBehaviour(m_wanderBehaviour);
}

Guards::~Guards()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
}

void Guards::Update(float deltaTime)
{
	if (IsKeyPressed(KEY_ONE))
	{
		m_wanderBehaviour->SetTarget(GetMousePosition());
		SetBehaviour(m_wanderBehaviour);
	}
	UpdateColRect();
	GameObject::Update(deltaTime);
}

void Guards::Draw()
{
	DrawTexturePro(ASSETS->guard1,
		{ 0,0, (float)ASSETS->player.width, (float)ASSETS->player.height },
		{ m_position.x, m_position.y, m_size.x, m_size.y },
		{ m_size.x / 2, m_size.y / 2 },
		0, WHITE);

	GameObject::Draw();
}

void Guards::UpdateColRect()
{
	// check pixel to the left of the entity
	int tilesize = 8; // TODO: make this variable a member variabe
	auto playerPos = GetPosition();

	auto lColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x - tilesize, playerPos.y);
	auto rColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x + tilesize, playerPos.y);
	auto tColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x, playerPos.y - tilesize);
	auto bColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x, playerPos.y + tilesize);


	if (lColor == C_BLACK)
	{
		ApplyForce({ GetMaxForce(), 0.0f });
		SetVelocity({ 0.0f , GetVelocity().y });
	}
	if (rColor == C_BLACK)
	{
		ApplyForce({ -GetMaxForce(), 0.0f });
		SetVelocity({ 0.0f , GetVelocity().y });
	}
	if (tColor == C_BLACK)
	{
		ApplyForce({ 0.0f, GetMaxForce() });
		SetVelocity({ GetVelocity().x, 0.0f });
	}
	if (bColor == C_BLACK)
	{
		ApplyForce({ 0.0f,-GetMaxForce() });
		SetVelocity({ GetVelocity().x, 0.0f });
	}
}

unsigned int Guards::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int*)img.data;
	unsigned int color = data[yPos * img.width + xPos];
	return color;
}