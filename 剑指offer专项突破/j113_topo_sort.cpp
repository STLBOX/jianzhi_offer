#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;

queue<int> getFesibleSquence(const int* prerequisities, int curriculums, int relations) {
	queue<int> seq;
	unordered_multiset<int> inset;  // 记录入度
	vector<vector<int>> outlist(curriculums);  // 记录出度
	unordered_set<int> unvisited;  // 记录剩余元素

	for (int i = 0; i < relations; ++i)
	{
		inset.insert(*(prerequisities + i * 2 + 0));
		outlist[*(prerequisities + i * 2 + 1)].push_back(*(prerequisities + i * 2 + 0));
	}
	for (int i = 0; i < curriculums; ++i) unvisited.insert(i);


	// 找到入度为0的课；insert  seq；记录之后将不考虑;
	while (!unvisited.empty())
	{
		// unordered_set<int>::const_iterator i;
		bool none_cicle = true;
		for (int i : unvisited)  // O(n)
		{

			if (inset.find(i) == inset.end())
			{
				seq.push(i);  // 选中
				unvisited.erase(i);  // O(1)
				for (int del = 0; del < outlist[i].size(); ++del) inset.erase(inset.find(outlist[i][del]));  //O(1)
				none_cicle = false;
				break;
			}
		}
		if (none_cicle == true) return queue<int>();
	}
	return seq;

}


queue<int> findOrder(const int* prerequisites, int curriculums, int relations) {
	unordered_map<int, list<int>> graph;
	int* indegrees = new int[curriculums]();

	for (int i = 0; i < curriculums; ++i) {
		graph.insert(make_pair(i, list<int>()));

	}
	for (int i = 0; i < relations; ++i) {
		graph[*(prerequisites+i*2+1)].push_back(*(prerequisites + i * 2));
		indegrees[*(prerequisites + i*2)]++;
	}
	queue<int> zeroindegrees;
	for (int i = 0; i < curriculums; ++i) {
		if (indegrees[i] == 0) zeroindegrees.push(i);
	}

	queue<int> order;
	while (!zeroindegrees.empty()) {
		int course = zeroindegrees.front();
		zeroindegrees.pop();
		order.push(course);
		for (auto it : graph[course]) {
			indegrees[it]--;
			if (indegrees[it] == 0) {
				zeroindegrees.push(it);
			}
		}
	}
	return order.size()==curriculums? order:queue<int>();
}


int main() {
	int prerequisities[6][2] = { {1,0},{2,0},{3,1},{3,2}};
	queue<int> feasible_sqc = findOrder(&prerequisities[0][0], 4, 4);
	if (!feasible_sqc.empty())
	{
		for (int i = 0; i < 4; ++i)
		{
			cout << "->" << feasible_sqc.front();
			feasible_sqc.pop();
		}
	}
	return 0;
}