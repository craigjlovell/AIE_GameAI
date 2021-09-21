#pragma once

#include "IGameState.h"

class Application;

class PauseState : public IGameState
{
public:

	PauseState(Application* app);
	virtual ~PauseState();

	virtual void Load();
	virtual void Unload();

	bool IsPointInBox(Rectangle rect, Vector2 point);

	virtual void Update(float dt);
	virtual void Draw();


	Rectangle menuRec{ GetScreenWidth() / 2.0f - 75, GetScreenHeight() / 2.0f - 50, 150, 100 };

protected:
private:

	Application* m_app;

};