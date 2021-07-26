#include "raylib.h"

#include "Application.h"
#include "GameStateManager.h"
#include "Assets.h"
#include "GameScreen.h"
#include "Player.h"
#include "Guards.h"

#include "Graph2D.h"
#include "Graph2DEditor.h"


GameScreen::GameScreen(Application* app) : m_app(app)
{
	
}

GameScreen::~GameScreen()
{
}

void GameScreen::BuildGraphMap()
{

	int tilesize = 32;

	delete m_graph;
	m_graph = new Graph2D();

	int numRows = ASSETS->imgGameMap.height / tilesize;
	int numCols = ASSETS->imgGameMap.width / tilesize;

	float xOffset = 16;
	float yOffset = 16;
	float spacing = tilesize;

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

			if (color == C_RED) // Red
			{
				PlayerBuild(xPos, yPos);
			}

			if (color == C_CYAN) // Cyan/Aqua 			
			{
				CreateGuards({xPos, yPos });
			}
		}
	}

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
}

void GameScreen::PlayerBuild(float x, float y)
{
	m_player1 = new Player();
	m_player1->SetPosition({ x, y });
	m_player1->SetFriction(1.0f);
}

GameObject* GameScreen::CreateGuards(Vector2 pos)
{
	GameObject* guard = new Guards();
	guard->SetPosition(pos);
	m_guards.push_back(guard);

	auto playerPos = guard->GetPosition();


	return guard;
}

void GameScreen::Load()
{
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
}

void GameScreen::Update(float dt)
{
	m_player1->Update(dt);

	for (auto guard : m_guards)
	{
		guard->Update(dt);
	}

	//pause
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
	
	DrawText("Game Screen", 10, 10, 20, BLUE);

	EndMode2D();
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
	if (IsKeyDown(KEY_UP)) m_cam.target.y -= 200.0f * dt;
	if (IsKeyDown(KEY_DOWN)) m_cam.target.y += 200.0f * dt;
	if (IsKeyDown(KEY_LEFT)) m_cam.target.x -= 200.0f * dt;
	if (IsKeyDown(KEY_RIGHT)) m_cam.target.x += 200.0f * dt;
	
	
	int mouseMove = GetMouseWheelMove();
	m_cam.zoom += mouseMove;
	//m_cam.target = m_player1->GetPosition();
}

bool GameScreen::IsInCamView(Vector2 pos)
{
	pos = GetWorldToScreen2D(pos, m_cam);
	return !(pos.x < 0 || pos.x > GetScreenWidth() || pos.y < 0 || pos.y > GetScreenHeight());
}



