#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "PlayState.h"

PlayState::PlayState(Application* app) : m_app(app)
{

}

PlayState::~PlayState()
{

}

void PlayState::Load()
{

}

void PlayState::Unload()
{

}

void PlayState::Update(float dt)
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

void PlayState::Draw()
{
	if (m_app->GetGameStateManager()->GetCurrentState() != this)
		return;

	DrawText("Game Screen", 10, 10, 20, BLUE);
}

