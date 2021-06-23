#pragma once

#include "IGameState.h"

class Application;
class GameObject;
class Graph2D;
class Graph2DEditor;
class GameStateManager;

class GraphScreen : public IGameState
{
public:

	GraphScreen(Application* app);
	virtual ~GraphScreen();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
private:

	Application* m_app;

	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;

};
