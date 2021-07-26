#include "Application.h"
#include "raylib.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "GameScreen.h"
#include "Assets.h"
#include "PauseState.h"


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

    Assets::CreateSingleton();
    Assets::GetInstance()->LoadAssets();

    m_gameStateManager = new GameStateManager();
    m_gameStateManager->SetState("Menu", new MenuState(this));
    m_gameStateManager->SetState("Game", new GameScreen(this));
    m_gameStateManager->SetState("Pause", new PauseState(this));

    m_gameStateManager->PushState("Menu");

    

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Update(dt);
        Draw();
    }


    delete m_gameStateManager;

    Assets::GetInstance()->UnloadAssets();
    Assets::DestroySingleton();

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