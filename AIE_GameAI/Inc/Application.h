#pragma once
class GameObject;
class Graph2D;
class Graph2DEditor;

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


protected:
private:

	int m_windowWidth;
	int m_windowHeight;
	const char* m_windowTitle;

	Graph2D* m_graph = nullptr;
	Graph2DEditor* m_graphEditor = nullptr;


	//GameObject* m_player1 = nullptr;
	//GameObject* m_player2 = nullptr;

};