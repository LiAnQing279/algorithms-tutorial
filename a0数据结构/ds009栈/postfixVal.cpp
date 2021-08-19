
//实现后缀表达式值
#include "listStack.hpp"
#include <string>
using std::string;

bool isOP(char t_ch)
{
	return t_ch == '*' || t_ch == '/' || t_ch == '-' || t_ch == '+';
}

int getNext(int &t_id, const string &t_exp)
{
	int strLen = t_exp.size();
	if (t_id < strLen && isOP(t_exp[t_id])) {
		char op = t_exp[t_id];
		t_id += 2; //跳过空格
		return op;
	}

	int num = 0;
	while (t_id < strLen && t_exp[t_id] != ' ') {
		num = num * 10 + (t_exp[t_id] - '0');
		t_id++;
	}
	t_id++; //跳过空格
	return num;
}

int cal(char ch, int a, int b)
{
	int ans = 0;
	switch (ch) {

	case '+':
		ans = a + b;
		break;
	case '-':
		ans = a - b;
		break;
	case '*':
		ans = a * b;
		break;
	case '/':
		ans = a / b;
		break;
	default:
		break;
	}
	return ans;
}

int suffixValue(string t_exp)
{
	ds::ListStack valStk;
	int n = t_exp.size();
	int i = 0;
	while (i < n) {
		int nxt = getNext(i, t_exp);
		if (isOP(nxt)) {
			int b = valStk.top();
			valStk.pop();
			int a = valStk.top();
			valStk.pop();
			valStk.push(cal(nxt, a, b));
		} else {
			valStk.push(nxt);
		}
	}
	return valStk.top();
}

int main()
{
	string tmp = "100 9 10 * - 20 11 6 - * 90 - 12 * +"; // 100 - 9 * 10 + ( 20 * ( 11 - 6 ) - 90 ) * 12
	string str = "231 131 - 25 10 - * 600 -";			 //(231-131)*(25-10)-600
	int id = 0;
	// std::cout << getNext(id, str)<<std::endl;
	// std::cout << id << std::endl;
	// std::cout << cal('-',231,131) << std::endl;
	std::cout << suffixValue(str) << std::endl;

	return 0;
}