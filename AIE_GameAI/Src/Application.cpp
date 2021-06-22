#include "Application.h"
#include "raylib.h"

#include "GameObject.h"

#include "KeyBoardBehaviour.h"
#include "Player.h"

#include "Graph2D.h"
#include "Graph2DEditor.h"

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
	SetTargetFPS(60);

	Load();

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		Update(deltaTime);
		Draw();
	}

	Unload();

	CloseWindow();
}

void Application::Load()
{
	//m_player1 = new Player();
	//m_player1->SetPosition({ m_windowWidth * 0.25f, m_windowHeight / 2.0f });
	//m_player1->SetFriction(1.0f);

	m_graph = new Graph2D();	

	int numRows = 4;
	int numCols = 6;
	float xOffset = 100;
	float yOffset = 100;
	float spacing = 50;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			m_graph->AddNode
			({
				x * spacing + xOffset,
				y * spacing + yOffset
			});
		}
	}


	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(node->data, 60, nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node) { continue; }

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}
	}

	m_graphEditor = new Graph2DEditor();
	m_graphEditor->SetGraph(m_graph);
}

void Application::Unload()
{
	//delete m_player1;
	//m_player1 = nullptr;
	//delete m_player2;
	//m_player2 = nullptr;

	delete m_graph;
	m_graph = nullptr;

	delete m_graphEditor;
	m_graphEditor = nullptr;
}

void Application::Update(float deltaTime)
{
	//m_player1->Update(deltaTime);
	//m_player2->Update(deltaTime);

	m_graphEditor->Update(deltaTime);

}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	m_graphEditor->Draw();

	//m_player1->Draw();
	//m_player2->Draw();

	EndDrawing();
}