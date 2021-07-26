#pragma once
#include "IGameState.h"
#include "raylib.h"
#include <list>

class Application;
class GameObject;
class Graph2D;
class Graph2DEditor;

enum Colours
{
	C_RED = 0xFF0000FF,
	C_GREEN = 0xFF00FF00,
	C_BLUE = 0xFFFF0000,
	C_CYAN = 0xFFFFFF00,
	C_MAGENTA = 0xFFFF00FF,
	C_YELLOW = 0xFF00FFFF,
	C_WHITE = 0xFFFFFFFF,
	C_BLACK = 0xFF000000
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

protected:

private:

	Application* m_app;

	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;

	GameObject* m_player1 = nullptr;

	std::list<GameObject*> m_guards;

	Camera2D m_cam;

};