#include "hashlib.hpp"

using namespace ds;

int main()
{
	HashNameTable myHash;
	myHash.insertName("agllo");
	myHash.insertName("aello");
	myHash.insertName("adllo");
	myHash.insertName("cello");
	myHash.insertName("cdllo");
	myHash.insertName("cqllo");
	myHash.insertName("wello");
	myHash.insertName("wqllo");
	myHash.insertName("qpllo");

	myHash.printTable();

	return 0;
}