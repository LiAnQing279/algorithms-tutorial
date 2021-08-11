#include "graph.hpp"
#define random(x) (rand() % x)
using namespace ds;
Graph::Graph(int V)
{
	m_V = V;
	m_E = 0;

	m_adj = GraphAdjPtr(new vector<ListPtr>(V, nullptr));
	for (int i = 0; i < V; i++) {
		m_adj->at(i) = new list<int>(0);
	}
}

Graph::Graph(string file)
{
	ifstream in(file, std::ios::in);
	if (!in) {
		printf_s("file open error.");
		return;
	}

	//初始化节点
	in >> m_V;
	m_adj = GraphAdjPtr(new vector<ListPtr>(m_V, nullptr));
	for (int i = 0; i < m_V; i++) {
		m_adj->at(i) = new list<int>(0);
	}

	//加入边
	int edges = 0;
	in >> edges; //一般大于m_E，含自环和平行边
	for (int w, v, i = 0; i < edges; i++) {
		in >> w >> v;
		addEdge(w, v);
	}
	in.close();
}

void Graph::addEdge(int v, int w)
{
	if (isParallel_edges_self_loop(v, w))
		return;
	m_adj->at(v)->push_front(w);
	m_adj->at(w)->push_front(v);
	++m_E;
}

string Graph::toString()
{
	string s = intToStr(m_V) + " vertices, " + intToStr(m_E) + " edges\n";

	for (int i = 0; i < m_V; i++) {
		s += intToStr(i) + ": ";
		for (auto adj : *(m_adj->at(i))) {
			s += intToStr(adj) + " ";
		}
		s += "\n";
	}
	return s;
}

string inline Graph::intToStr(int n)
{
	char int_s[20] = {0};  //末尾加上'\0'
	_itoa_s(n, int_s, 10); // 10 表示十进制
	return string(int_s);
}

bool Graph::isParallel_edges_self_loop(int v, int w)
{
	if (v == w)
		return true;
	for (auto &n : *(m_adj->at(v))) {
		if (n == w) {
			return true;
		}
	}
	return false;
}

void GFile(int V, int E, string fileName)
{ //指定节点边数生成随机图
	std::ofstream write(fileName);
	if (!write) {
		std::cout << "file opens error !" << std::endl;
		return;
	}
	write << V << std::endl;
	write << E << std::endl;
	srand((unsigned)time(0));
	for (int i = 0; i < E; ++i) {
		int from = random(V);
		int to = random(V);
		write << from << " " << to << std::endl;
	}
	write.close();
}

void testG()
{
	// GFile(9, 33,"graph");
	Graph myG("graph");
	std::cout << (myG.toString()) << std::endl;
}
