#include "GameScreen.h"
#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "KeyBoardBehaviour.h"
#include "Player.h"
#include "GameObject.h"
#include "SeekBehaviour.h"

#include <iostream>
#include "raymath.h" 


GameScreen::GameScreen(Application* app) : m_app(app)
{

}

GameScreen::~GameScreen()
{

}

void GameScreen::Load()
{
	m_player1 = new Player();
	m_player1->SetPosition({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });
	m_player1->SetFriction(1.0f);
}

void GameScreen::Unload()
{
	delete m_player1;
	m_player1 = nullptr;
}

void GameScreen::Update(float deltaTime)
{
	m_player1->Update(deltaTime);

	if (KeyboardKey(IsKeyPressed(KEY_LEFT_CONTROL)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void GameScreen::Draw()
{
	m_player1->Draw();
	
	DrawText("Game", 10, 10, 20, GOLD);

}