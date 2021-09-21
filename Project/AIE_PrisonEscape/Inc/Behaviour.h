#pragma once

class GameObject;

class Behaviour
{
public:

	Behaviour() {}
	virtual ~Behaviour() {}

	virtual void End() {}
	virtual void Begin() {}

	virtual void Update(GameObject* obj, float deltaTime) {}
	virtual void Draw(GameObject* obj) {}


protected:

private:
};