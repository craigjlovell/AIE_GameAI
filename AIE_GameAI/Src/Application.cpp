#include "Application.h"
#include "raylib.h"
#include "Vec2.h"

#include "Graph2D.h"
#include "Graph2DEditor.h"

#include "GameStateManager.h"
#include "IGameState.h"

#include "MenuState.h"
#include "GameScreen.h"
#include "GraphScreen.h"

Application::Application(int windowWidth, int windowHeight, const char* windowTitle) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_windowTitle(windowTitle)
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, m_windowTitle);

	m_gameStateManager = new GameStateManager();
	m_gameStateManager->SetState("Menu", new MenuState(this));
	m_gameStateManager->SetState("Game", new GameScreen(this));
	m_gameStateManager->SetState("Graph", new GraphScreen(this));

	m_gameStateManager->PushState("Menu");

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		Update(deltaTime);
		Draw();
	}

	delete m_gameStateManager;

	CloseWindow();
}

void Application::Load()
{

	
}

void Application::Unload()
{

}

void Application::Update(float deltaTime)
{
	m_gameStateManager->Update(deltaTime);	
}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	m_gameStateManager->Draw();

	EndDrawing();
}