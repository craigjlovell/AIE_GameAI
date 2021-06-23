#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "PauseState.h"

PauseState::PauseState(Application* app) : m_app(app)
{

}

PauseState::~PauseState()
{

}

void PauseState::Load()
{

}

void PauseState::Unload()
{

}

void PauseState::Update(float dt)
{
	if (KeyboardKey(IsKeyPressed(KEY_LEFT_SHIFT)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Play");
	}
}

void PauseState::Draw()
{
	DrawText("Pause", 10, 10, 20, BLUE);
}