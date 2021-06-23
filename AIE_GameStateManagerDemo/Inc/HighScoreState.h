#pragma once

#include "IGameState.h"

class Application;

class HighScoreState : public IGameState
{
public:

	HighScoreState(Application* app);
	virtual ~HighScoreState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;

};