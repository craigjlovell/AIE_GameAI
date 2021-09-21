#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "HighScoreState.h"

HighScoreState::HighScoreState(Application* app) : m_app(app)
{

}

HighScoreState::~HighScoreState()
{

}

void HighScoreState::Load()
{

}

void HighScoreState::Unload()
{

}

void HighScoreState::Update(float dt)
{
	if (KeyboardKey(IsKeyReleased(KEY_TAB)))
	{
		m_app->GetGameStateManager()->PopState();
	}
}

void HighScoreState::Draw()
{
	DrawText("Score", 10, 10, 20, BLUE);
}