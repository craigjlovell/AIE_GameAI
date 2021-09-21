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
	if (IsPointInBox(menuRec, GetMousePosition()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void GameOverState::Draw()
{
	DrawText("GameOver", 10, 10, 20, BLUE);

	if (IsPointInBox(menuRec, GetMousePosition()))
	{
		DrawRectangleRec(menuRec, GOLD);
	}
	else
	{
		DrawRectangleRec(menuRec, RED);
	}

	DrawText("Menu", menuRec.x + menuRec.width / 2 - 65, menuRec.y + menuRec.height / 2 - 20, 50, BLACK);
}

bool GameOverState::IsPointInBox(Rectangle rect, Vector2 point)// move to math lib
{
	return point.x > rect.x && point.x < rect.x + rect.width && point.y > rect.y && point.y < rect.y + rect.height;
}