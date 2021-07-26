#pragma once
#include"GameObject.h"

class KeyBoardBehaviour;
class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;

class Guards : public GameObject
{
public:

	Guards();
	virtual ~Guards();

	void UpdateColRect();
	unsigned int GetImagePixel(Image img, int xPos, int yPos);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	KeyBoardBehaviour* m_kbBehaviour;
	SeekBehaviour* m_seekBehaviour;
	FleeBehaviour* m_fleeBehaviour;
	WanderBehaviour* m_wanderBehaviour;

private:

};