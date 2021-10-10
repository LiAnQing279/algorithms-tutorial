
#include <iostream>
#include <stack>
#include <string>

using std::stack;
using std::string;

bool isOpenOp(char c)
{
	return c == '(' || c == '[' || c == '{'; //还有，/*要单独判定
}

char matchLeft(char c)
{
	char ans;
	if (c == '(') {
		ans = ')';
	} else if (c == '[') {
		ans = ']';
	} else if (c == '{') {
		ans = '}';
	} else {
		ans = c;
	}
	return ans;
}

void check(string &str)
{
	stack<char> stk;

	int i = 0;
	int strlen = str.size();
	while (i < strlen) {
		char c = str.at(i);
		if (c == '/') {
			if (str[i + 1] == '*') {
				stk.push('O'); //表示/*
				i += 2;
			} else {
				std::cerr << "Error: in pos " << i << " need a *" << std::endl;
				return;
			}
		} else if (c == '*') {
			if (str[i + 1] == '/') {
				if (stk.empty() || stk.top() != 'O') {
					std::cerr << "Error: in pos " << i << " need a '/*'" << std::endl;
					return;
				} else {
					stk.pop();
					i += 2;
				}
			} else {
				std::cerr << "Error: in pos " << i + 1 << " need a /" << std::endl;
				return;
			}
		} else if (isOpenOp(c)) {
			stk.push(c);
			i++;
		} else {
			// std::cout << c << std::endl;
			char rightChar = matchLeft(stk.top());
			if (rightChar != c) {
				std::cerr << "Error: in pos " << i << " need a " << rightChar << std::endl;
				return;
			} else {
				stk.pop();
				i++;
			}
		}
	}

	if (!stk.empty()) {
		std::cerr << "Error: lack of right bracket." << std::endl;
		return;
	}

	std::cout << "Right." << std::endl;
}

//----------------------main()----------------------------------//
#define out(x) std::cout << (x) << '#' << std::endl;
int main()
{
	string tmp[] = {"*/", "/**", "{{})", "[{}](()", "([()]){}", "()/*/"};

	for (size_t i = 0; i < 6; i++) {
		check(tmp[i]);
	}

	return 0;
}