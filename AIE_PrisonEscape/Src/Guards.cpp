#include "KeyBoardBehaviour.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"
#include "KeyboardBehaviour.h"

#include "BlackBoard.h"

#include "Guards.h"
#include "Assets.h"

#include "GameScreen.h"

Guards::Guards(GameScreen* game) : m_gamescreen(game)
{

	m_kbBehaviour = new KeyBoardBehaviour();

	m_wanderBehaviour = new WanderBehaviour();
	m_wanderBehaviour->SetTargetRadius(50.0f);

	m_seekBehaviour = new SeekBehaviour();
	m_seekBehaviour->SetTargetRadius(25.0f);
	

	SetBehaviour(NULL);
}

Guards::~Guards()
{
	SetBehaviour(nullptr);

	delete m_wanderBehaviour;
	delete m_seekBehaviour;

}

void Guards::Update(float deltaTime)
{
	UpdateColRect();
	float dist = Vector2Distance(m_gamescreen->GetPlayer()->GetPosition(), GetPosition());

	if (dist < m_targetRadius)
	{ 
		m_blackboard->playerPos = m_gamescreen->GetPlayer()->GetPosition();
		m_blackboard->IsPlayerLocKnown = true;
	}
	
	if (m_blackboard->IsPlayerLocKnown == true && m_gamescreen->GetPlayer()->m_lever2 == true)
	{
		m_seekBehaviour->SetTarget(m_blackboard->playerPos);
		SetBehaviour(m_seekBehaviour);
	}



	GameObject::Update(deltaTime);
}

void Guards::Draw()
{
	DrawTexturePro(ASSETS->guard1,
		{ 0,0, (float)ASSETS->player.width, (float)ASSETS->player.height },
		{ m_position.x, m_position.y, m_size.x, m_size.y },
		{ m_size.x / 2, m_size.y / 2 },
		0, WHITE);

	DrawCircleV(GetPosition(), m_targetRadius, { 255, 0, 0, 128 });

	GameObject::Draw();
}

void Guards::UpdateColRect()
{
	 //check pixel to the left of the entity
	int tilesize = 8; // TODO: make this variable a member variabe
	auto playerPos = GetPosition();
	
	auto lColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x - tilesize, playerPos.y);
	auto rColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x + tilesize, playerPos.y);
	auto tColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x, playerPos.y - tilesize);
	auto bColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, playerPos.x, playerPos.y + tilesize);

	if (lColor == C_BLACK)
	{
		ApplyForce({ GetMaxForce(), 0.2f });
		SetVelocity({ 0.0f , GetVelocity().y });
	}
	if (rColor == C_BLACK)
	{
		ApplyForce({ -GetMaxForce(), 0.2f });
		SetVelocity({ 0.0f , GetVelocity().y });
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

unsigned int Guards::GetImagePixel(Image img, int xPos, int yPos)
{
	if (xPos < 0 || yPos < 0 || xPos >= img.width || yPos >= img.height) 
		return 0;

	unsigned int* data = (unsigned int*)img.data;
	unsigned int color = data[yPos * img.width + xPos];
	return color;
}
