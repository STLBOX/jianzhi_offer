#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <array>
#include <unordered_set>
#include <algorithm>
#include <string>


using namespace std;


unordered_set<string>  getNeibors(string item) {
	unordered_set<string> set1;
	for (int i = 0; i < item.size(); ++i) 
	{
		char old = item[i];
		for (int j = 0; j < 26; j++)
		{
			char replace = 'a'+j;
			if (old != replace) item[i] = replace;
			set1.insert(item);
		}
		item[i] = old;  // 恢复现场 
	}
	return set1;
}

int GetSL(unordered_set<string> word_list, string beginword, string endword)
{
	// 当前单词入队，前后各入队，并从未查找的集合中删除；方便查询，采用unordered_set
	unordered_set<string> set1;
	unordered_set<string> set2;
	unordered_set<string> set3;
	unordered_set<string> neibors;

	set1.insert(beginword);
	set2.insert(endword);
	int length = 1;

	while (!set1.empty())
	{
		for (auto item : set1)
		{
			if (set2.find(item) != set2.end()) return length;
			else
			{
				neibors = getNeibors(item);
				word_list.erase(item);  // 只剩下没有访问的元素
				for (auto neibor : neibors)  // 单词表中的neibor
				{
					if (word_list.find(neibor) != word_list.end())
						set3.insert(neibor);
				}
				neibors.clear();
			}
		}

		// 找到set1的邻居set3
		set1.clear();
		set1.swap(set3);
		// 处理最短的队为set1
		if (set1.size() > set2.size()) set1.swap(set2);
		++length;
	}

	return -1;
}

int main() {
	string beginword = "hit";
	string endword = "lot";
	unordered_set<string> word_dict;
	word_dict.insert("hit");
	word_dict.insert("hot");
	word_dict.insert("dot");
	//word_dict.insert("dog");
	//word_dict.insert("log");
	word_dict.insert("lot");
	word_dict.insert("cog");
	// word_dict.insert("hahaha");
	int shortest_length = GetSL(word_dict, beginword, endword);
	cout << shortest_length;
	return 0;
}