#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

int unLockBFS(const unordered_set<string>& lock_state, string init_state, const string& password) {
	int least_nums = 0;
	queue<string> trypassword;
	queue<string> nextpassword;
	unordered_set<string> traverse_state;
	// BFS
	trypassword.push(init_state);
	while (!trypassword.empty())
	{
		int slen = trypassword.size();
		for (int count = 0; count < slen; ++count)
		{
			string pw = trypassword.front();
			traverse_state.insert(pw);
			trypassword.pop();
			if (pw == password) return least_nums;
			else if (lock_state.find(pw) == lock_state.end())  // 未死锁
			{
				// 获得接下来的状态入队
				for (int i = 0; i < 4; ++i)
				{
					char old = pw[i];
					if (old == '0')
					{
						pw[i] = '9';
						if (traverse_state.find(pw) == traverse_state.end()) nextpassword.push(pw);
						pw[i] = '1';
						if (traverse_state.find(pw) == traverse_state.end()) nextpassword.push(pw);
						pw[i] = old;
					}
					else if (old == '9')
					{
						pw[i] = '0';
						if (traverse_state.find(pw) == traverse_state.end()) nextpassword.push(pw);
						pw[i] = '8';
						if (traverse_state.find(pw) == traverse_state.end()) nextpassword.push(pw);
						pw[i] = old;
					}
					else
					{
						pw[i] -= 1;
						if (traverse_state.find(pw) == traverse_state.end()) nextpassword.push(pw);
						pw[i] += 2;
						if (traverse_state.find(pw) == traverse_state.end()) nextpassword.push(pw);
						pw[i] = old;
					}
				}
			}
		}
		trypassword.swap(nextpassword);
		++least_nums;
	}
	return -1;
}

int main() {
	unordered_set<string> lock_state = {"0102", "0201"};
	string password = "0202";
	string init_state = "0000";
	int least_nums = unLockBFS(lock_state, init_state, password);
	cout << least_nums;
	return 0;
}