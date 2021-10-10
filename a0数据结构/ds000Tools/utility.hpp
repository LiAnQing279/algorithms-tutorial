
#pragma once

#include <string>
using std::string;

namespace ds
{
string intToStr(int n)
{
	char int_s[20] = {0};  //末尾加上'\0'
	_itoa_s(n, int_s, 10); // 10 表示十进制
	return string(int_s);
}
} // namespace ds
