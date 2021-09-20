#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "Assets.h"

#include "GameScreen.h"

#include "Player.h"
#include "Guards.h"

#include "BlackBoard.h"

#include "Graph2D.h"

#include "FollowBehaviour.h"

#include <string>

GameScreen::GameScreen(Application* app) : m_app(app)
{
	
}

GameScreen::~GameScreen()
{
	
}

void GameScreen::BuildGraphMap()
{

	int tilesize = 32;

	m_graph = new Graph2D();

	int numRows = ASSETS->imgGameMap.height / tilesize;
	int numCols = ASSETS->imgGameMap.width / tilesize;

	float xOffset = 16;
	float yOffset = 16;
	float spacing = tilesize;

	// Create Graph Nodes
	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			float xPos = x * spacing + xOffset;
			float yPos = y * spacing + yOffset;
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, xPos, yPos);

			if (color != C_BLACK) // Black
			{
				m_graph->AddNode({ xPos, yPos });
			}
		}
	}
	
	// Connecting Graph Nodes (adding edges between nodes)
	for (auto node : m_graph->GetNodes())
	{
		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(node->data, tilesize, nearbyNodes);

		for (auto connectedNode : nearbyNodes)
		{
			if (connectedNode == node) { continue; }

			float dist = Vector2Distance(node->data, connectedNode->data);
			m_graph->AddEdge(node, connectedNode, dist);
			m_graph->AddEdge(connectedNode, node, dist);
		}
	}

	std::vector<Vector2> guardPath;

	// Swawn game objects
	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			float xPos = x * spacing + xOffset;
			float yPos = y * spacing + yOffset;
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, xPos, yPos);

			if (color == C_RED) // Red
			{
				PlayerBuild(xPos, yPos);
			}

			if (color == C_CYAN) // Cyan/Aqua 			
			{
				CreateGuards({ xPos, yPos });
			}

			if (color == C_YELLOW) // Yellow
			{
				// todo generate a path
				auto startNode = m_graph->GetNearbyNode({ xPos, yPos }, 32);
				auto guardPathNodes = m_graph->FindPath(IGraph::SearchType::DIJKSTRA, startNode, [&](auto n)
				{
					auto nColor = GetImagePixel(ASSETS->imgGameMapInfoRaw, n->data.x, n->data.y);
					if( Vector2Distance({ xPos, yPos }, n->data) > 100)
						return nColor == C_BROWN;
					return false;
				});

				guardPath.clear();
				for (auto pathNode : guardPathNodes)
					guardPath.push_back(pathNode->data);

			}
		}
	}

	// TODO:
	// loop through the guards, set the path for their follow behaviour.
	for (auto guard : m_guards)
	{
		guard->SetFollowBehaviourPath(guardPath);
	}

}

void GameScreen::Load()
{

	m_blackboard = new BlackBoard;

	BuildGraphMap();

	m_cam.zoom = 1;
	m_cam.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}

void GameScreen::Unload()
{
	delete m_graph;
	m_graph = nullptr;

	delete m_player1;
	m_player1 = nullptr;

	delete m_blackboard;
	m_blackboard = nullptr;
}

void GameScreen::Update(float dt)
{
	m_player1->Update(dt);
	
	for (auto guard : m_guards)
	{
		guard->Update(dt);
	}

	if (IsKeyPressed(KEY_LEFT_SHIFT))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Pause");
	}

	UpdateGameCam(dt);
}

void GameScreen::Draw()
{
	BeginMode2D(m_cam);

	DrawTexture(ASSETS->imgGameMap, 0, 0, WHITE);

	if (IsKeyDown(KEY_TAB)) DrawTexture(ASSETS->imgGameMapInfo, 0, 0, WHITE);

	if (IsKeyDown(KEY_ENTER)) DrawDebugGraph();
	if (IsKeyDown(KEY_CAPS_LOCK)) DrawColRec();

	m_player1->Draw();

	for (auto guard : m_guards)
	{
		guard->Draw();
	}

	EndMode2D();
	DrawUI();
}

void GameScreen::DrawDebugGraph()
{

	// drw all nodes
	for (auto& node : m_graph->GetNodes())
	{
		if (IsInCamView(node->data))
		{
			DrawCircle(node->data.x, node->data.y, 4, GRAY);
		}		
	}

	// draw all edges
	for (auto& node : m_graph->GetNodes())
	{
		if (IsInCamView(node->data))
		{
			for (auto connection : node->connections)
			{
				DrawLine(node->data.x, node->data.y, connection.to->data.x, connection.to->data.y, RED);
			}
		}
	}
}

void GameScreen::DrawColRec()
{
	int tilesize = 32;
	int numRows = ASSETS->imgGameMap.height / tilesize;
	int numCols = ASSETS->imgGameMap.width / tilesize;
	float spacing = tilesize;

	for (int y = 0; y < numRows; y++)
	{
		for (int x = 0; x < numCols; x++)
		{
			float xPos = x * spacing;
			float yPos = y * spacing;
			auto color = GetImagePixel(ASSETS->imgGameMapInfoRaw, xPos, yPos);

			if (color == C_BLACK) // Black
			{
				DrawRectangle(xPos, yPos, tilesize, tilesize, RED);
			}
		}
	}
}

unsigned int GameScreen::GetImagePixel(Image img, int xPos, int yPos)
{
	unsigned int* data = (unsigned int*)img.data;
	unsigned int color = data[yPos * img.width + xPos];
	return color;
}

void GameScreen::UpdateGameCam(float dt)
{
	//if (IsKeyDown(KEY_UP)) m_cam.target.y -= 200.0f * dt;
	//if (IsKeyDown(KEY_DOWN)) m_cam.target.y += 200.0f * dt;
	//if (IsKeyDown(KEY_LEFT)) m_cam.target.x -= 200.0f * dt;
	//if (IsKeyDown(KEY_RIGHT)) m_cam.target.x += 200.0f * dt;
	
	int mouseMove = GetMouseWheelMove();
	m_cam.zoom += mouseMove;
	m_cam.target = m_player1->GetPosition();
}

bool GameScreen::IsInCamView(Vector2 pos)
{
	pos = GetWorldToScreen2D(pos, m_cam);
	return !(pos.x < 0 || pos.x > GetScreenWidth() || pos.y < 0 || pos.y > GetScreenHeight());
}

void GameScreen::PlayerBuild(float x, float y)
{
	m_player1 = new Player(m_app, this);
	m_player1->SetPosition({ x, y });
	m_player1->SetFriction(1.0f);

	m_player1->SetBlackBoard(m_blackboard);
}

GameObject* GameScreen::CreateGuards(Vector2 pos)
{
	Guards* guard = new Guards(this);
	guard->SetPosition(pos);
	guard->SetMaxForce(50);
	guard->SetMaxSpeed(50);
	m_guards.push_back(guard);

	guard->SetBlackBoard(m_blackboard);
	return guard;
}

void GameScreen::DrawUI()
{
	DrawText("Game Screen", 10, 10, 20, BLUE);
	DrawText(std::to_string((int)m_player1->m_timer).c_str(), 10, 50, 35, GOLD);

	if (m_player1->m_lever2 == true)
	{
		DrawText("Guard Room is open", 10, 30, 20, RED);
	}
	else
	{
		DrawText("Guard Room is closed", 10, 30, 20, RED);
	}
}

void GameScreen::UpdateUI(float dt)
{
	
}

Player* GameScreen::GetPlayer()
{
	return m_player1;
}

void GameScreen::SetPlayer(Player* player)
{
	m_player1 = player;
}

//GameObject* GameScreen::GetGuard()
//{
//	return m_guards;
//}
//
//void GameScreen::SetGuard(GameObject* guard)
//{
//	m_guards = guard;
//}





