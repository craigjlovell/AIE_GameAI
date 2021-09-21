#include "Application.h"
#include "raylib.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "SplashState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "HighScoreState.h"

Application::Application(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight)
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "AIE Game State Manager");

    m_gameStateManager = new GameStateManager();
    m_gameStateManager->SetState("Splash", new SplashState(this));
    m_gameStateManager->SetState("Menu", new MenuState(this));
    m_gameStateManager->SetState("Play", new PlayState(this));
    m_gameStateManager->SetState("Pause", new PauseState(this));
    m_gameStateManager->SetState("HighScore", new HighScoreState(this));

    m_gameStateManager->PushState("Splash");


    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Update(dt);
        Draw();
    }

    delete m_gameStateManager;

    CloseWindow();
}

void Application::Update(float dt)
{
    m_gameStateManager->Update(dt);
}

void Application::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_gameStateManager->Draw();

    EndDrawing();
}