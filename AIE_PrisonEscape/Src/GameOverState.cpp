#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "GameOverState.h"

GameOverState::GameOverState(Application* app) : m_app(app)
{

}

GameOverState::~GameOverState()
{

}

void GameOverState::Load()
{

}

void GameOverState::Unload()
{

}

void GameOverState::Update(float dt)
{

}

void GameOverState::Draw()
{
	DrawText("GameOver", 10, 10, 20, BLUE);
}

bool GameOverState::IsPointInBox(Rectangle rect, Vector2 point)// move to math lib
{
	return point.x > rect.x && point.x < rect.x + rect.width && point.y > rect.y && point.y < rect.y + rect.height;
}