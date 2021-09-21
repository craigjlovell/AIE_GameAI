#pragma once
#include "Graph2D.h"

class Graph2D;

class Graph2DEditor
{
public:

	Graph2DEditor();
	~Graph2DEditor();

	void Update(float deltaTime);
	void Draw();

	Graph2D* GetGraph();
	void SetGraph(Graph2D* graph);

protected:

	Graph2D* m_graph;

	Graph2D::Node* m_firstNode = nullptr;
	Graph2D::Node* m_lastNode = nullptr;

	std::list<Graph2D::Node*> m_path;


private:
};