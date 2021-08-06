#include "btree.hpp"
#include <vector>

using namespace std;
using namespace btree;

int main()
{
	vector<int> data{100, 35,  65,	130, 180, 10,  20,	40,	 50,  70,  80,
					 90,  110, 120, 140, 160, 190, 240, 260, 270, 280, 302};

	BTree<int> myBTree;
	for (auto item : data) {
		myBTree.insert(item);
	}

	int goal2 = 260;
	myBTree.search(goal2);
	myBTree.visit();

	return 0;
}