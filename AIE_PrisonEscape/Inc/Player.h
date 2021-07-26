#pragma once
#include"GameObject.h"

class KeyBoardBehaviour;
class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;

class Player : public GameObject
{
public:

	Player();
	virtual ~Player();

	void UpdateColRect();
	unsigned int GetImagePixel(Image img, int xPos, int yPos);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	KeyBoardBehaviour* m_kbBehaviour;

private:

};