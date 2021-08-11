#pragma once

#include "graph.hpp"

namespace ds
{
class depthFirstSearch
{
	using BoolArrPtr = unique_ptr<vector<bool>>;

  public:
	depthFirstSearch(Graph &G, int s);

	int count() { return m_count; }
	bool marked(int v) { return m_visited->at(v); }

  private:
	BoolArrPtr m_visited = nullptr; //标记是否相连
	int m_count;					//与source起点连通的顶点数，包括自己

	void dfs(Graph &G, int now);
};

depthFirstSearch::depthFirstSearch(Graph &G, int s)
{
	m_visited = BoolArrPtr(new vector<bool>(G.V(), false));
	m_count = 0;
	dfs(G, s);
}

inline void depthFirstSearch::dfs(Graph &G, int now)
{
	m_visited->at(now) = true;
	m_count++;

	for (const auto &next : G.adj(now)) {
		if (!(*m_visited)[next]) {
			dfs(G, next);
		}
	}
}
} // namespace ds

void testDfs()
{
	ds::Graph G("graph");
	ds::depthFirstSearch dfs(G, 2);
	std::cout << dfs.count() << std::endl;
}
