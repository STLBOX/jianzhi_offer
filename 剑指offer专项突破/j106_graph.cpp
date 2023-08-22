/*
* sequence containers: vector, Deque, queue, array
* properties:1. fasr insert/remove at end and begin O(1)
* 
* random containers: list  compared with deque;  forward_list
*/
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <array>
#include <algorithm>

using namespace std;

typedef stack<int> myqs;

void test_list() {
	list<int> mylist = {5,2,9};
	mylist.push_back(6);
	mylist.push_front(4);  // {4,5,2,9,6}
	list<int>::iterator itr = find(mylist.begin(), mylist.end(), 2); 
	mylist.insert(itr, 8); // 插在itr前面 O(1)  {4,5,8,2,9,6}

	itr++;
	mylist.erase(itr);  // 删除掉itr指向  {4,5,8,2,6}
	for (auto& it: mylist)
	{
		cout << it << "\t";
	}
	list<int> mylist2 = { 5,2,9 };
	// mylist.splice(itr, mylist2, itr_a, itr_b)  [itr_a, itr_b) 前bi后开； 

}
/*
* associative container: always soted by <
* set: 没有多个相同记录，duplicates
*/
template<typename T>
void print(T container)
{
	for (auto& it : container)
	{
		cout << it << "\t";
	}
}

#include <set>
void test_set() {
	set<int> myset;
	myset.insert(3);
	myset.insert(1);
	myset.insert(7);   // myset{1,3,7}
	print(myset);
	set<int>::iterator it = myset.find(10);  // sequence containers dont have the member fun  find()
	if(it!=myset.end()) cout << *it;
}

bool colorGrap(vector<vector<int>> graph, int* color,const int& i){
	// 是否能依据二分图上色，失败返回false，采用BFS
	myqs qs;
	qs.push(i);
	color[i] = 1;
	while (!qs.empty()) 
	{
		int current = qs.top();
		qs.pop();
		// 相邻节点颜色为相反数。
		if (!graph[current].empty())
		{
			for (auto item : graph[current]) 
			{
				if (color[item] == color[current]) return false;
				else if (color[item] == 0)
				{
					color[item] = -color[current];
					qs.push(item);
				}
			}
		}
	}
	return true;
}

bool colorGrapRCS(vector<vector<int>> graph, int* color, const int& i, int t_color)
{
	if (*(color + i) != 0) return *(color + i) == t_color;
	*(color + i) = t_color;  // color
	for (auto item : graph[i])
	{
		if(!colorGrapRCS(graph, color, item, -t_color)) return false;
	}
	return true;
}

bool isBipartite(vector<vector<int>> graph) {
	// 颜色vector
	int* color = new int[graph.size()]();
	for (unsigned int i = 0; i < graph.size(); ++i)
	{
		if (*(color+i) == 0)  // 未上色，DFS
		{
			if (!colorGrapRCS(graph, color, i , 1)) return false;  // 递归
		}
	}
	delete[] color;
	return true;
}

int main(){
	vector<vector<int>> graph;
	vector<int> a0 = { 1,2,3 };
	vector<int> a1 = { 0,2 };
	vector<int> a2 = { 0,1,3 };
	vector<int> a3 = { 0,2 };
	graph.push_back(a0);
	graph.push_back(a1);
	graph.push_back(a2);
	graph.push_back(a3);
	bool isbigraph = isBipartite(graph);
	cout << isbigraph;
	return 0;
}