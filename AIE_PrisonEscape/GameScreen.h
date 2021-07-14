#pragma once

#include "IGameState.h"

class Application;

class GameScreen : public IGameState
{
public:

	GameScreen(Application* app);
	virtual ~GameScreen();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;

	Camera2D* m_cam;

};