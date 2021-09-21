#include "MenuState.h"
#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"

#include <iostream>
#include "raymath.h" 

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

void MenuState::Update(float deltaTime)
{
	if (KeyboardKey(IsKeyPressed(KEY_SPACE)))
	{
		//m_app->GetGameStateManager()->SetState("Menu", nullptr);
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Game");
	}

	if (KeyboardKey(IsKeyPressed(KEY_ENTER)))
	{
		//m_app->GetGameStateManager()->SetState("Menu", nullptr);
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Graph");
	}
}

void MenuState::Draw()
{
	ClearBackground(BLUE);
	DrawRectangle(150, 125, 250, 150, RED);
	DrawText("Menu", 230, 150, 30, GOLD);
	DrawText("Press Space", 180, 190, 30, GOLD);
	DrawText("Game", 220, 220, 30, GOLD);

	DrawRectangle(430, 125, 250, 150, PINK);
	DrawText("Menu", 490, 150, 30, GOLD);
	DrawText("Press Enter", 450, 190, 30, GOLD);
	DrawText("Graph", 490, 220, 30, GOLD);
}