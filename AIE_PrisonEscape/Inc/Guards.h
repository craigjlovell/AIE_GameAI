#pragma once
#include"GameObject.h"

#include "BlackBoard.h"
#include "raylib.h"
#include <vector>

class SeekBehaviour;
class WanderBehaviour;
class KeyBoardBehaviour;
class FollowBehaviour;

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

	virtual void Update(float dt);
	virtual void Draw();

	Behaviour* CalBehaviour();

	void SetFollowBehaviourPath(std::vector<Vector2>& path);

protected:

	SeekBehaviour* m_seekBehaviour;
	WanderBehaviour* m_wanderBehaviour;
	FollowBehaviour* m_followBehaviour;

	KeyBoardBehaviour* m_kbBehaviour;

	float m_targetRadius = 100.0f;
	
private:

	Application* m_app;
	GameScreen* m_gamescreen;
};