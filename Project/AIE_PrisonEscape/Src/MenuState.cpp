#include "MenuState.h"
#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"

#include <iostream>

MenuState::MenuState(Application* app) : m_app(app)
{

}

MenuState::~MenuState()
{

}

void MenuState::Load()
{
	std::cout << "Loading Menu" << std::endl;
}

void MenuState::Unload()
{
	std::cout << "Unloading Menu" << std::endl;
}

void MenuState::Update(float dt)
{
	if (KeyboardKey(IsKeyPressed(KEY_SPACE)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Game");
	}
}

void MenuState::Draw()
{

	DrawText("Menu", 10, 10, 20, GOLD);
	DrawText("Press Space to start the game", 225, 200, 20, BLUE);
}