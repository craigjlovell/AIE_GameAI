#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <functional>

class IGraph
{
public:
	enum class SearchType
	{
		BFS,
		DIJKSTRA,
	};
};

template<class TNodeData, class TEdgeData>
class Graph
{

public:

	struct Node;
	struct Edge;

	struct Node
	{
		TNodeData data;
		std::vector<Edge> connections;
	};

	struct Edge
	{
		Node* to;
		TEdgeData data;
	};

	struct PFNode
	{
		Node* node;
		PFNode* parent = nullptr;

		int depth = 0;
		float gScore = 0;
		float hScore = 0;

		PFNode() {}
		PFNode(Node* n, PFNode* p) : node(n), parent(p) {}
	};

public:

	Graph()
	{

	}

	virtual ~Graph()
	{
		for (auto node : m_nodes)
		{
			delete node;
		}
		m_nodes.clear();
	}

	Node* AddNode(const TNodeData& data)
	{
		Node* node = new Node();
		node->data = data;

		m_nodes.push_back(node);
		return node;
	}

	void AddEdge(Node* nodeA, Node* nodeB, const TEdgeData& data)
	{
		nodeA->connections.push_back({ nodeB, data });
	}


	const std::vector<Node*>& GetNodes()
	{
		return m_nodes;
	}

	void ForEachBFSPrint(Node* startNode, std::function<bool(Node* n)> processNode)
	{
		// push sthe start node on the stack
		std::list<Node*> stack;
		stack.push_back(startNode);

		std::list<Node*> visited;


		while (stack.empty() == false)
		{
			// Get the node from the stack and remove it
			auto node = stack.front();
			stack.pop_front();

			visited.push_back(node);

			// print the node
			if (processNode(node) == false)
			{
				break;
			}

			for (auto& edge : node->connections)
			{
				if (std::find(visited.begin(), visited.end(), edge.to) == visited.end() &&
					std::find(stack.begin(), stack.end(), edge.to) == stack.end())
				{
					stack.push_back(edge.to);
				}
			}
		}
	}

	std::list<Node*> FindPath(IGraph::SearchType type, Node* startNode, std::function<bool(Node* n)> processNode)
	{
		// push sthe start node on the stack
		std::list<PFNode*> stack;
		std::list<PFNode*> visited;
		std::list<Node*> path;

		auto GetNodesInList = [&](Node* nodeToFind) -> PFNode*
		{
			for (auto& n : stack)
				if (n->node == nodeToFind)
					return n;

			for (auto& n : visited)
				if (n->node == nodeToFind)
					return n;

			return nullptr;
		};

		stack.push_back(new PFNode(startNode, nullptr));

		while (stack.empty() == false)
		{
			// Get the node from the stack and remove it
			auto pfNode = stack.front();
			stack.pop_front();

			visited.push_back(pfNode);

			// print the node
			if (processNode(pfNode->node) == true)
			{
				PFNode* current = pfNode;
				while (current != nullptr)
				{
					path.push_front(current->node);
					current = current->parent;

				}
				break;
			}

			for (auto& edge : pfNode->node->connections)
			{
				auto childNode = edge.to;
				float gScore = (pfNode->parent ? pfNode->parent->gScore : 0) + edge.data;
				float hScore = 0;
				int depth = pfNode->depth + 1;

				PFNode* childPFNode = GetNodesInList(edge.to);

				if (childPFNode == nullptr)
				{
					childPFNode = new PFNode(edge.to, pfNode);
					childPFNode->gScore = gScore;
					childPFNode->hScore = hScore;
					childPFNode->depth = depth;
					stack.push_back(childPFNode);
				}
				else if (childPFNode->gScore > gScore)
				{
					childPFNode->parent = pfNode;
					childPFNode->gScore = gScore;
					childPFNode->hScore = hScore;
					childPFNode->depth = depth;
				}
			}

			stack.sort([&](PFNode* a, PFNode* b) -> bool
				{
					switch (type)
					{
					case IGraph::SearchType::DIJKSTRA: return a->gScore < b->gScore;
					case IGraph::SearchType::BFS: return a->depth < b->depth;
					default: return a->gScore < b->gScore;
					}
				});
		}

		for (auto n : visited)
			delete n;

		for (auto n : stack)
			delete n;

		return path;
	}

protected:

	std::vector<Node*> m_nodes;

private:
};