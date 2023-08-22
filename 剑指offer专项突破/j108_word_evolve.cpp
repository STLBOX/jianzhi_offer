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
		item[i] = old;  // �ָ��ֳ� 
	}
	return set1;
}

int GetSL(unordered_set<string> word_list, string beginword, string endword)
{
	// ��ǰ������ӣ�ǰ�����ӣ�����δ���ҵļ�����ɾ���������ѯ������unordered_set
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
				word_list.erase(item);  // ֻʣ��û�з��ʵ�Ԫ��
				for (auto neibor : neibors)  // ���ʱ��е�neibor
				{
					if (word_list.find(neibor) != word_list.end())
						set3.insert(neibor);
				}
				neibors.clear();
			}
		}

		// �ҵ�set1���ھ�set3
		set1.clear();
		set1.swap(set3);
		// ������̵Ķ�Ϊset1
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