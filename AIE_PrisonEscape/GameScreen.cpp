#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "GameScreen.h"

GameScreen::GameScreen(Application* app) : m_app(app)
{

}

GameScreen::~GameScreen()
{

}

void GameScreen::Load()
{

}

void GameScreen::Unload()
{

}

void GameScreen::Update(float dt)
{
	if (m_app->GetGameStateManager()->GetCurrentState() != this)
		return;

	if (KeyboardKey(IsKeyPressed(KEY_LEFT_SHIFT)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Pause");
	}

	if (KeyboardKey(IsKeyDown(KEY_TAB)))
	{
		m_app->GetGameStateManager()->PushState("HighScore");
	}
}

void GameScreen::Draw()
{


	if (m_app->GetGameStateManager()->GetCurrentState() != this)
		return;

	DrawText("Game Screen", 10, 10, 20, BLUE);
}

