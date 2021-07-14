#include "Graph2DEditor.h"
#include "Graph2D.h"
#include "Vec2.h"

Graph2DEditor::Graph2DEditor()
{

}

Graph2DEditor::~Graph2DEditor()
{

}

void Graph2DEditor::Update(float deltaTime)
{
	if (IsMouseButtonPressed(1))
	{
		auto mousePos = GetMousePosition();
		std::vector<Graph2D::Node*> setNode;
		m_graph->GetNearbyNodes(mousePos, 8, setNode);
		if (m_firstNode == nullptr)
		{
			if (setNode.size() > 0)
			{				
				m_firstNode = setNode[0];
			}
		}
		else if(m_lastNode == nullptr)
		{
			if (setNode.size() > 0)
			{
				m_lastNode = setNode[0];
				m_path = m_graph->FindPath(IGraph::SearchType::DIJKSTRA, m_firstNode, [this](auto n) {
					return n == m_lastNode;
				});
				std::cout << "found path ";
			}
		}
	}

	if (IsMouseButtonPressed(0))
	{
		auto mousePos = GetMousePosition();
		
		auto newNode = m_graph->AddNode(mousePos);

		std::vector<Graph2D::Node*> nearbyNodes;
		m_graph->GetNearbyNodes(mousePos, 60, nearbyNodes);

		for (auto nearbyNode : nearbyNodes)
		{
			float dist = Vector2Distance(newNode->data, nearbyNode->data);
			m_graph->AddEdge(newNode, nearbyNode, dist);
			m_graph->AddEdge(nearbyNode, newNode, dist);
		}
	}
}

void Graph2DEditor::Draw()
{	
	for (auto node : m_graph->GetNodes())
	{
		for (auto connections : node->connections)
		{
			DrawLine(node->data.x, node->data.y, connections.to->data.x, connections.to->data.y, BLACK);
		}
	}

	for (auto node : m_graph->GetNodes())
	{
		DrawCircle(node->data.x, node->data.y, 8, PINK);
		DrawCircleLines(node->data.x, node->data.y, 8, YELLOW);
	}

	auto mousePos = GetMousePosition();
	DrawCircle(mousePos.x, mousePos.y, 6, RED);

	std::vector<Graph2D::Node*> nearbyNodes;
	m_graph->GetNearbyNodes(mousePos, 60, nearbyNodes);

	for (auto nearbyNode : nearbyNodes)
	{
		DrawLine(mousePos.x, mousePos.y, nearbyNode->data.x, nearbyNode->data.y, DARKGREEN);
	}

	// draw the path
	for (auto iter = m_path.begin(); iter != m_path.end(); iter++)
	{
		auto next = std::next(iter);
		if (next == m_path.end())
			break;

		auto p1 = (*iter)->data;
		auto p2 = (*next)->data;

		DrawLineEx(p1, p2, 2, BLACK);
		DrawCircle(m_lastNode->data.x, m_lastNode->data.y, 4, RED);
		DrawCircle(m_firstNode->data.x, m_firstNode->data.y, 4, RED);
	}

}

Graph2D* Graph2DEditor::GetGraph()
{
	return m_graph;
}

void Graph2DEditor::SetGraph(Graph2D* graph)
{
	m_graph = graph;
}