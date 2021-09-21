#pragma once
#include "IGameState.h"
#include "raylib.h"
#include <list>

class Application;

class GameObject;

class Player;
class Guards;

class Graph2D;
class Graph2DEditor;

class BlackBoard;

enum Colours
{
	C_RED = 0xFF0000FF,
	C_GREEN = 0xFF00FF00,
	C_BLUE = 0xFFFF0000,
	C_CYAN = 0xFFFFFF00,
	C_MAGENTA = 0xFFFF00FF,
	C_YELLOW = 0xFF00FFFF,
	C_WHITE = 0xFFFFFFFF,
	C_BLACK = 0xFF000000,
	C_ORANGE = 0xFF277FFF,
	C_BROWN = 0xFF0A254E
};

class GameScreen : public IGameState
{
public:

	GameScreen(Application* app);
	virtual ~GameScreen();

	void BuildGraphMap();
	void PlayerBuild(float x, float y);

	GameObject* CreateGuards(Vector2 pos);

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

	void UpdateGameCam(float dt);

	void DrawDebugGraph();

	unsigned int GetImagePixel(Image img, int xPos, int yPos);

	bool IsInCamView(Vector2 pos);

	void DrawColRec();

	void UpdateUI(float dt);
	void DrawUI();

	Player* GetPlayer();
	void SetPlayer(Player* player);

protected:

private:
	
	Application* m_app;

	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;

	Player* m_player1 = nullptr;
	std::list<Guards*> m_guards;

	Camera2D m_cam;

	BlackBoard* m_blackboard = nullptr;

};