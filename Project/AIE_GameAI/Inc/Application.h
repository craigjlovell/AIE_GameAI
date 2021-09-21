#pragma once
class GameObject;
class Graph2D;
class Graph2DEditor;
class GameStateManager;

class Application
{
public:

	Application(int windowWidth, int windowHeight, const char* windowTitle);
	~Application();

	void Run();

	void Load();
	void Unload();

	void Update(float deltaTime);

	void Draw();

	GameStateManager* GetGameStateManager()
	{
		return m_gameStateManager;
	}


protected:
private:

	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowTitle;

	

	GameStateManager* m_gameStateManager = nullptr;

};