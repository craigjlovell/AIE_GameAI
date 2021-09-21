#pragma once

#include "IGameState.h"

class Application;
class GameObject;
class Graph2D;
class Graph2DEditor;
class GameStateManager;

class GameScreen : public IGameState
{
public:

	GameScreen(Application* app);
	virtual ~GameScreen();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
private:

	Application* m_app;

	GameObject* m_player1 = nullptr;


};
