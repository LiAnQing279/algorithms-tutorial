#include "djsetlib.hpp"

using namespace ds;

int main()
{
	MyDjset set0(5);

	set0.unionSet(0, 2);
	set0.unionSet(2, 4);
	set0.unionSet(1, 3);
	set0.unionSet(3, 5);
	set0.unionSet(3, 2);

	std::cout << "before find 1,5:" << std::endl;
	set0.printSet();
	std::cout << "after  find 1,5:" << std::endl;
	set0.findSet(5);
	set0.findSet(1);

	set0.printSet();
	return 0;
}