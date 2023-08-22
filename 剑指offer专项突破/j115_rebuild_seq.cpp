#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;


bool reBuild(const vector<int>& seq, const list<vector<int>>& subseqs, const int& n) {
	if (seq.size() < n) return false;
	// 获得graph
	vector<unordered_set<int>> graph(n+1, unordered_set<int>());  // 0没用到
	unordered_map<int, int> indegrees;
	for (int i = 1; i < n + 1; ++i) indegrees.insert(make_pair(i, 0));
	for (auto its : subseqs) {
		for (auto itr = its.begin(); itr != its.end()-1; ++itr) {
			if (graph[*itr].find(*(itr + 1)) == graph[*itr].end()) {
				graph[*itr].insert(*(itr + 1));
				indegrees[*(itr + 1)] ++;
			}
		}
	}
	// 获得拓扑排序
	queue<int> sort;
	for (int i = 1; i < n + 1; ++i) {
		if (indegrees[i] == 0) sort.push(i);
	}
	if (sort.size() > 1) return false;

	for (int i = 1; i < n + 1; ++i) {
		int curr = sort.front();
		if (curr != seq[i - 1]) return false;
		sort.pop();
		for (auto it : graph[curr]) {
			indegrees[it]--;
			if (indegrees[it] == 0) sort.push(it);
		}
		if (sort.size() > 1) return false;
	}
	return true;
}

int main(){
	int n = 6;
	vector<int> seq = { 4,1,5,2,6,3 };
	list<vector<int>> subseqs;
	subseqs.push_back(vector<int>{5,2,6,3});
	subseqs.push_back(vector<int>{4,1,5,2});
	bool res = reBuild(seq, subseqs, n);
	cout << res;
	return 0;
}