#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory> //unique_ptr
#include <string>
#include <vector>

using std::function;
using std::ifstream;
using std::list;
using std::string;
using std::unique_ptr;
using std::vector;

namespace ds
{
class Graph
{
	using ListPtr = list<int> *;
	using GraphAdjPtr = unique_ptr<vector<ListPtr>>;
	using callback = function<void(int)>; //访问顶点
  public:
	Graph(){};
	Graph(int V);		//只有v个顶点不含边
	Graph(string file); //从文件读入图数据

	int V() { return m_V; }
	int E() { return m_E; }

	void addEdge(int v, int w);						 //向图中添加边v-w,顶点已存在
	list<int> adj(int v) { return *(m_adj->at(v)); } //复制对象

	string toString(); //对象的字符串表示
					   // void visit(int v,callback func);有点鸡肋，func中需要声明许多参数
  private:
	int m_V = 0;				 //节点数
	int m_E = 0;				 //边数
	GraphAdjPtr m_adj = nullptr; //邻接表

	string intToStr(int n);
	bool isParallel_edges_self_loop(int v, int w);
};
} // namespace ds

void GFile(int V, int E, string fileName); //指定节点、边数生成随机图fileName
void testG();