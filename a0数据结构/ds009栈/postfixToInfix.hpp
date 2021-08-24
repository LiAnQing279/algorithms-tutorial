
/**
 * @file infixToPostfix.cpp
 * @author LiAnQing279
 * @brief 后缀转为中缀表达式
 * @version 0.1
 * @date 2021-08-19
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
#include <map>
#include <stack>
#include <string>

using std::map;
using std::stack;
using std::string;

using strPtr = string *;

bool isOP(char t_ch)
{
	return t_ch == '*' || t_ch == '/' || t_ch == '-' || t_ch == '+';
}

strPtr getNext(int &t_id, string &t_exp)
{
	int strLen = t_exp.size();
	if (t_id < strLen && isOP(t_exp[t_id])) {
		char op = t_exp[t_id];
		t_id += 2; //跳过空格
		string ops = string(" ") + char(op) + string(" ");
		return new string(ops);
	}

	int start = t_id;
	;
	while (t_id < strLen && t_exp[t_id] != ' ') {
		t_id++;
	}
	t_id++; //跳过空格

	return (new string(t_exp.substr(start, t_id - start - 1)));
}

int postfixToInfix(string &t_postfix, string &t_infix)
{
	stack<strPtr> stk;

	int i = 0;
	int strlen = t_postfix.size();
	while (i < strlen) {
		strPtr nxt = getNext(i, t_postfix);

		if (nxt->size() > 2 && isOP(nxt->at(1))) {
			strPtr b = stk.top();
			stk.pop();
			strPtr a = stk.top();
			stk.pop();

			string tmp = "(" + *a + *nxt + *b + ")"; //粗暴的加括号
			stk.push(new string(tmp));
			delete a;
			delete b;
			delete nxt;
		} else {
			stk.push(nxt);
		}
	}

	t_infix = *stk.top();

	return 0;
}

//------------------------去掉多余的括号--------------------------//

struct middle {
	string *val;
	int level;

	middle(string *t_val, int t_lev) : val(t_val), level(t_lev) {}
};

using midPtr = middle *;
map<int, int> level = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

midPtr getNext2(int &t_id, string &t_exp)
{
	int strLen = t_exp.size();
	if (t_id < strLen && isOP(t_exp[t_id])) {
		char op = t_exp[t_id];
		t_id += 2; //跳过空格

		string ops = string(" ") + char(op) + string(" ");
		return new middle(new string(ops), level[op]);
	}

	int start = t_id;
	;
	while (t_id < strLen && t_exp[t_id] != ' ') {
		t_id++;
	}
	t_id++; //跳过空格

	string *val = new string(t_exp.substr(start, t_id - start - 1));
	int lev = 0;

	return new middle(val, lev);
}

midPtr addParentheses(midPtr a, midPtr b, midPtr nxt)
{
	string astr = *(a->val);
	string bstr = *(b->val);

	int blev = b->level;
	int alev = a->level;
	int oplev = level[nxt->val->at(1)];

	//只有中间符号高于某一边时，才需要套上括号;特别的，数字不用
	if (alev && oplev > alev)
		astr = "(" + *(a->val) + ")";
	if (blev && oplev > blev)
		bstr = "(" + *(b->val) + ")";

	string tmp = astr + *(nxt->val) + bstr;
	return new middle(new string(tmp), oplev)
}

int postfixToInfix2(string &t_postfix, string &t_infix)
{
	stack<midPtr> stk;

	int i = 0;
	int strlen = t_postfix.size();
	while (i < strlen) {
		midPtr nxt = getNext2(i, t_postfix);

		if (nxt->val->size() > 2 && isOP(nxt->val->at(1))) {
			midPtr b = stk.top();
			stk.pop();
			midPtr a = stk.top();
			stk.pop();
			//添加圆括号
			stk.push(addParentheses(a, b, nxt));
			delete a;
			delete b;
			delete nxt;
		} else {
			stk.push(nxt);
		}
	}

	t_infix = *(stk.top()->val);

	return 0;
}

//----------------------main()----------------------------------//
#define out(x) std::cout << (x) << '#' << std::endl;
int main()
{
	string str = "101 230 50 40 - * + 900 13 / - ";
	string str1 = "11 33 522 * + 71 9 - / ";
	string str2 = "10 20 50 40 - * + 900 3000 + / ";
	string str3 = "12 91 64 344 / + 4445 - * 401 + ";
	string infix = "";
	/*
	int i = 0;
	while (i<str.size())
	{
		out(*getNext(i, str));
	}
	*/
	postfixToInfix2(str, infix);
	out(infix);
	postfixToInfix2(str1, infix);
	out(infix);
	postfixToInfix2(str2, infix);
	out(infix);
	postfixToInfix2(str3, infix);
	out(infix);
	return 0;
}