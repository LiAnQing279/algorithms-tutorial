/**
 * @file infixToPostfix.cpp
 * @author LiAnQing279
 * @brief 将中缀表达式转化为后缀表达式（逆波兰表达式）
 * @version 0.1
 * @date 2021-08-19
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "listStack.hpp"
#include <map>
#include <string>
using std::map;
using std::string;

bool isOP(char t_ch)
{
	return t_ch == '*' || t_ch == '/' || t_ch == '-' || t_ch == '+' || t_ch == '(' || t_ch == ')';
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
string intToStr(int n)
{
	char int_s[20] = {0};  //末尾加上'\0'
	_itoa_s(n, int_s, 10); // 10 表示十进制
	return string(int_s);
}

/**
 * @brief 这里有个小细节
 * 注意到 str+=char(42)+' ';本质是str+=char(42+32)即先算右边整体字符和，然后转化为一个字符
 * 所以，要分开行相加 ans+=char(42);ans+=' ';
 * 或者，ans += char(stk.top())+string(" "); 注意必须强调string(" ")，否则字符无法加const char*
 */
string infixToPostfix(const string &t_exp)
{
	map<int, int> level = {{'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {')', 7}};

	int i = 0;
	int n = t_exp.size();
	string ans = "";

	ds::ListStack stk;
	while (i < n) {
		int nxt = getNext(i, t_exp);
		if (isOP(nxt)) {
			switch (nxt) {
			case '(':
				stk.push('(');
				break;
			case ')':
				//匹配括号
				while (!stk.empty() && stk.top() != '(') {
					ans += char(stk.top()) + string(" ");
					stk.pop();
				}
				stk.pop(); //丢弃左括号
				break;
			default:
				//弹出高优先级的符号
				while (!stk.empty() && level[stk.top()] >= level[nxt]) {
					ans += char(stk.top()) + string(" ");
					stk.pop();
				}
				stk.push(nxt);
				break;
			}
		} else {
			ans += intToStr(nxt) + ' ';
		}
	}
	while (!stk.empty()) {
		ans += char(stk.top()) + string(" ");

		stk.pop();
	}
	return ans;
}
//没搞清楚相加错误，就直接用字典来查符号字符串
string infixToPostfix1(const string &t_exp)
{
	map<int, int> level = {{'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {')', 7}};
	map<int, string> ops = {{43, "+"}, {45, "-"}, {42, "*"}, {47, "/"}};
	int i = 0;
	int n = t_exp.size();
	string ans = "";

	ds::ListStack stk;
	while (i < n) {
		int nxt = getNext(i, t_exp);
		if (isOP(nxt)) {
			switch (nxt) {
			case '(':
				stk.push('(');
				break;
			case ')':
				//匹配括号
				while (!stk.empty() && stk.top() != '(') {
					ans += ops[stk.top()] + ' ';
					stk.pop();
				}
				stk.pop(); //丢弃左括号
				break;
			default:
				//弹出高优先级的符号
				while (!stk.empty() && level[stk.top()] >= level[nxt]) {
					ans += ops[stk.top()] + " ";
					stk.pop();
				}
				stk.push(nxt);
				break;
			}
		} else {
			ans += intToStr(nxt) + ' ';
		}
	}
	while (!stk.empty()) {
		ans += ops[stk.top()] + ' ';
		stk.pop();
	}
	return ans;
}

int main()
{
	string str = "100 - 9 * 10 + ( 20 * ( 11 - 6 ) - 90 ) * 12";
	int i = 0;
	// std::cout << getNext(i, str) << std::endl;
	// std::cout << i << std::endl;
	std::cout << infixToPostfix(str) << std::endl; //"100 9 10 * - 20 11 6 - * 90 - 12 * +";

	return 0;
}