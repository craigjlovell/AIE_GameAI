#pragma once
#include"GameObject.h"

#include "BlackBoard.h"
#include "raylib.h"

class SeekBehaviour;
class WanderBehaviour;
class KeyBoardBehaviour;

class GameScreen;

class Application;
class BlackBoard;

class Guards : public GameObject
{
public:

	Guards(GameScreen* game);
	virtual ~Guards();

	void UpdateColRect();
	unsigned int GetImagePixel(Image img, int xPos, int yPos);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	SeekBehaviour* m_seekBehaviour;
	WanderBehaviour* m_wanderBehaviour;

	KeyBoardBehaviour* m_kbBehaviour;

	float m_targetRadius = 100.0f;
	Vector2 m_target;

private:

	Application* m_app;
	GameScreen* m_gamescreen;
};