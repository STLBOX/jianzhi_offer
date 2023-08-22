#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <queue>
#include <unordered_map>

using namespace std;

/*�º���*/
class myCompare//int����Ƚϴ�С���࣬Ҳ�ɳ�Ϊ��������
{
public:
	bool operator()(int v1, int v2) const//�º����ķ���ֵ��bool���ͣ�������() �����
	{
		return v1 < v2;
	}
};

multiset<int, myCompare> getFriendCircles(const unordered_map<int, vector<int>>& relationships) {
	multiset<int,myCompare> circles;
	bool* visited = new bool[relationships.size()]{false};
	int friends;  // ͳ������
	queue<int> q;
	// BFS �㷨
	for (auto itm : relationships)
	{
		if (!visited[itm.first]) {
			friends = 0;
			visited[itm.first] = true;
			q.push(itm.first); // ����������Ȧ
		}
		while (!q.empty())
		{
			auto itr = relationships.find(q.front());
			for (auto it : (*itr).second) {
				if (!visited[it]) {
					q.push(it);
					visited[it] = true;
				}
			}
			q.pop();
			friends++;
		}
		if (friends != 0)
		{
			circles.insert(friends);
			friends = 0;
		}
	}
	delete[] visited;
	return circles;
}



int main(){
	unordered_map<int, vector<int>> relationships;
	relationships.insert(make_pair(0, vector<int> {1}));
	relationships.insert(make_pair(1, vector<int> {0}));
	relationships.insert(make_pair(2, vector<int> {3}));
	relationships.insert(make_pair(3, vector<int> {2}));
	relationships.insert(make_pair(4, vector<int> {}));
	multiset<int, myCompare> circles = getFriendCircles(relationships);
	for (auto it : circles) {
		cout << it << " ";
	}
	return 0;
}