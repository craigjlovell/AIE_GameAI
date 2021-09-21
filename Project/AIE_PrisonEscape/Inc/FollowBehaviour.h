#pragma once
#include "Behaviour.h"
#include "raymath.h"
#include <functional>
#include <vector>

class FollowBehaviour : public Behaviour
{
public:

	FollowBehaviour();
	virtual ~FollowBehaviour();

	virtual void Update(GameObject* obj, float dt);
	virtual void Draw(GameObject* obj);

	// TODO:
	// create getter and setter for the m_path

	const std::vector<Vector2>& GetPath() const;
	void SetPath(std::vector<Vector2>& path);

protected:

	std::vector<Vector2> m_path;
	int m_pathIndex = 0;
	int m_pathDir = 1;

private:
};