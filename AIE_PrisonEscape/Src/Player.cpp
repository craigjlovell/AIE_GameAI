#include "Player.h"
#include "KeyBoardBehaviour.h"
#include "Assets.h"
#include <GameScreen.h>

Player::Player()
{
	m_kbBehaviour = new KeyBoardBehaviour();
	SetBehaviour(m_kbBehaviour);
}

Player::~Player()
{
	SetBehaviour(nullptr);

	delete m_kbBehaviour;
}

void Player::Update(float deltaTime)
{
	if (IsKeyPressed(KEY_ONE))
	{
		SetBehaviour(m_kbBehaviour);
	}

	GameObject::Update(deltaTime);
	UpdateColRect();
}

void Player::Draw()
{
	DrawTexturePro(ASSETS->player,
		{ 0,0, (float)ASSETS->player.width, (float)ASSETS->player.height },
		{ m_position.x, m_position.y, m_size.x, m_size.y },
		{ m_size.x / 2, m_size.y / 2 },
		0, WHITE);

	GameObject::Draw();
}

void Player::UpdateColRect()
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

unsigned int Player::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int*)img.data;
	unsigned int color = data[yPos * img.width + xPos];
	return color;
}