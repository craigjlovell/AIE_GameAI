#include "GraphScreen.h"
#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "KeyBoardBehaviour.h"
#include "Player.h"
#include "GameObject.h"
#include "SeekBehaviour.h"

#include <iostream>
#include "raymath.h"

#include "Graph.h"
#include "Graph2D.h"
#include "Graph2DEditor.h"


GraphScreen::GraphScreen(Application* app) : m_app(app)
{

}

GraphScreen::~GraphScreen()
{

}

void GraphScreen::Load()
{
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

void GraphScreen::Unload()
{
	delete m_graph;
	m_graph = nullptr;
	
	delete m_graphEditor;
	m_graphEditor = nullptr;
}

void GraphScreen::Update(float deltaTime)
{
	m_graphEditor->Update(deltaTime);

	if (KeyboardKey(IsKeyPressed(KEY_LEFT_CONTROL)))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
	}
}

void GraphScreen::Draw()
{
	m_graphEditor->Draw();
	DrawText("Graph", 10, 10, 20, GOLD);

}