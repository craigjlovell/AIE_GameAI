#pragma once
#include"GameObject.h"
#include "IGameState.h"
#include "BlackBoard.h"
#include "raylib.h"

class Application;
class KeyBoardBehaviour;
class BlackBoard;
class GameScreen;

class Player : public GameObject
{
public:

	Player(Application* app, GameScreen* game);
	virtual ~Player();

	void UpdateColRect();
	void Door1();
	void Door2();

	unsigned int GetImagePixel(Image img, int xPos, int yPos);

	virtual void Update(float dt);
	virtual void Draw();

	float m_timer = 0;
	bool m_lever = false;
	bool m_lever2 = false;

protected:



	KeyBoardBehaviour* m_kbBehaviour;

private:

	Application* m_app;	
	GameScreen* m_gamescreen;
};