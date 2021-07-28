#pragma once
#include "raylib.h"
#include "Player.h"
#include "Guards.h"
#include "GameScreen.h"


class BlackBoard
{
public:

	BlackBoard();
	~BlackBoard();

	Vector2 playerPos = { NULL, NULL };
	bool IsPlayerLocKnown = false;

protected:

	

private:

};