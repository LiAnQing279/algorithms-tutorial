#pragma once
#include "graph.hpp"
#include <queue>

using std::queue;

namespace ds
{

class breadthFirstSearch
{
	using BoolArrPtr = unique_ptr<vector<bool>>;

  public:
	breadthFirstSearch(Graph &G, int s);

	int count() { return m_count; }
	bool marked(int v) { return (*m_inQueue)[v]; }

  private:
	BoolArrPtr m_inQueue = nullptr;
	int m_count = 0; //相连通的节点，不包括自己
	void bfs(Graph &G, int now);
};

breadthFirstSearch::breadthFirstSearch(Graph &G, int s)
{
	m_inQueue = BoolArrPtr(new vector<bool>(G.V(), false));
	m_count = 0;
	bfs(G, s);
}
inline void breadthFirstSearch::bfs(Graph &G, int now)
{
	queue<int> Q;
	Q.push(now);
	m_inQueue->at(now) = true;

	while (!Q.empty()) {

		int v = Q.front();
		Q.pop(); //从队列中删除下一顶点

		for (auto &w : G.adj(v)) {
			if (!(*m_inQueue)[w]) { //邻接点未被标记
				Q.push(w);
				m_inQueue->at(w) = true; //入队
				++m_count;				 //这里是可变的，其他部分算固定框架
			}
		}
	}
}

} // namespace ds
void testBfs()
{
	ds::Graph G("graph");
	ds::breadthFirstSearch bfs(G, 2);
	std::cout << bfs.count() << std::endl;
}