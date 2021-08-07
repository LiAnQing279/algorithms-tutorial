#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace ds
{

/**
 * @brief 记录一个名字的哈希表，发生冲突用一个list存储
 *
 */
class HashNameTable
{
	using UPtr = std::unique_ptr<std::list<std::string>>;

  public:
	HashNameTable();
	void insertName(const std::string &);

	bool has(const std::string &);
	void printTable() const;

  private:
	int hashId(const std::string &);
	void print_helper(const UPtr &) const;

	const int m_size = 26; //哈希表的总大小
	std::vector<UPtr> m_table;
};

HashNameTable::HashNameTable()
{
	for (int i = 0; i < m_size; i++) {
		m_table.emplace_back(UPtr(new std::list<std::string>()));
	}
}
void HashNameTable::insertName(const std::string &t_name)
{
	if (has(t_name)) {
		std::cout << t_name << "already exists." << std::endl;
		return;
	}

	int id = hashId(t_name);

	m_table[id]->emplace_front(t_name); //头插法
}

inline void HashNameTable::printTable() const
{
	int size = m_table.size();
	for (int i = 0; i < size; i++) {
		print_helper(m_table[i]);
	}
}

inline bool HashNameTable::has(const std::string &t_name)
{

	int id = hashId(t_name);
	if (m_table[id]->empty())
		return false;
	auto it = m_table[id]->begin();
	auto end = m_table[id]->end();
	for (; it != end; it++) {
		if (!(*it).compare(t_name))
			return true;
	}
	return false;
}

inline int HashNameTable::hashId(const std::string &t_name)
{ //设计一个哈希函数，这里简单使用首字母区分
	int A = t_name[0];
	if (A > 'a')
		A = A - 'a' + 'A';

	return A % m_size;
}

inline void HashNameTable::print_helper(const UPtr &t_ptr) const
{
	if (t_ptr->empty())
		return;
	auto it = t_ptr->begin();
	auto end = t_ptr->end();

	for (; it != end; it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl;
}

}; // namespace ds
