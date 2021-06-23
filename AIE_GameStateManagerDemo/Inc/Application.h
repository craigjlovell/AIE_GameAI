#pragma once

class GameStateManager;

class Application
{
public:

	Application(int windowWidth, int windowHeight);
	~Application();

	void Run();

	void Update(float dt);
	void Draw();

	GameStateManager* GetGameStateManager()
	{
		return m_gameStateManager;
	}

protected:
private:

	int m_windowWidth;
	int m_windowHeight;

	GameStateManager* m_gameStateManager = nullptr;

};