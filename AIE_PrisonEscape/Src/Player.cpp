#include "KeyBoardBehaviour.h"

#include "Player.h"
#include "Assets.h"

#include "GameScreen.h"
#include "GameStateManager.h"

#include "Application.h"


#include <string>

Player::Player(Application* app, GameScreen* game) : m_app(app), m_gamescreen(game)
{
	m_kbBehaviour = new KeyBoardBehaviour();
	SetBehaviour(m_kbBehaviour);
}

Player::~Player()
{
	SetBehaviour(nullptr);
	delete m_kbBehaviour;
}

void Player::Update(float dt)
{
	m_timer += dt;
	
	if (IsKeyPressed(KEY_ONE))
	{
		SetBehaviour(m_kbBehaviour);
	}

	GameObject::Update(dt);
	UpdateColRect();
	Door1();
	Door2();
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
		ApplyForce({ GetMaxForce(), 0.2f });
		SetVelocity({ 0.0f, GetVelocity().y });
	}
	if (rColor == C_BLACK)
	{
		ApplyForce({ -GetMaxForce(), 0.2f });
		SetVelocity({ 0.0f, GetVelocity().y });
	}
	if (tColor == C_BLACK)
	{
		ApplyForce({ 0.2f, GetMaxForce() });
		SetVelocity({ GetVelocity().x, 0.0f });
	}
	if (bColor == C_BLACK)
	{
		ApplyForce({ 0.2f,-GetMaxForce() });
		SetVelocity({ GetVelocity().x, 0.0f });
	}
}

void Player::Door1()
{
	
	int tilesize = 16;
	auto doorPos = GetPosition();

	auto lColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x - tilesize, doorPos.y);
	auto rColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x + tilesize, doorPos.y);
	auto tColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x, doorPos.y - tilesize);
	auto bColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x, doorPos.y + tilesize);

	if (lColor == C_BLUE || rColor == C_BLUE || tColor == C_BLUE || bColor == C_BLUE)
	{
		m_lever = true;
	}

	if (m_lever == true)
	{
		if (lColor == C_ORANGE || rColor == C_ORANGE || tColor == C_ORANGE || bColor == C_ORANGE)
		{
			m_app->GetGameStateManager()->PopState();
			m_app->GetGameStateManager()->PushState("GameOver");
		}
	}

	if (m_lever == false)
	{
		if (lColor == C_ORANGE || rColor == C_ORANGE || tColor == C_ORANGE || bColor == C_ORANGE)
		{
			ApplyForce({ GetMaxForce(), 0.0f });
			SetVelocity({ 0.0f });
		}
	}
}

void Player::Door2()
{

	int tilesize = 16;
	auto doorPos = GetPosition();

	auto lColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x - tilesize, doorPos.y);
	auto rColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x + tilesize, doorPos.y);
	auto tColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x, doorPos.y - tilesize);
	auto bColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, doorPos.x, doorPos.y + tilesize);

	if (lColor == C_GREEN || rColor == C_GREEN || tColor == C_GREEN || bColor == C_GREEN)
	{
		m_lever2 = true;
	}

	if (m_lever2 == false)
	{
		if (lColor == C_MAGENTA || rColor == C_MAGENTA || tColor == C_MAGENTA || bColor == C_MAGENTA)
		{
			ApplyForce({ GetMaxForce(), 0.0f });
			SetVelocity({ 0.0f });
		}
	}
}

unsigned int Player::GetImagePixel(Image img, int xPos, int yPos)
{
	if (xPos < 0 || yPos < 0 || xPos >= img.width || yPos >= img.height)
		return 0;

	unsigned int* data = (unsigned int*)img.data;
	unsigned int color = data[yPos * img.width + xPos];
	return color;
}
