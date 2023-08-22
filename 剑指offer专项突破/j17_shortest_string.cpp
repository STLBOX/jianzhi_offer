#include <iostream>
#include <map>

using namespace std;

bool good_array(map<int, int> arraymap, const int& k) {
	for (auto it = arraymap.begin(); it != arraymap.end(); it++) {
		if ((*it).second > k / 2) {
			return true;
		}
	}
	return false;
}

int main() {
	int n = 5, k = 3;
	int a[] = {3,4,5,4,4};

	int good_array_nums = 0;
	int max_length = 0;
	int max_length_key = 0;
	if (k > n) return 0 ;
	map<int, int> arraymap;
	for (int i = 1; i < k; i++)
	{
		if (arraymap.find(a[i]) == arraymap.end())
		{
			arraymap[a[i]]=1;
		}
		else
		{
		    arraymap[a[i]] ++;
		}
	}
	// 获得最大长度的key
	for (auto it = arraymap.begin(); it != arraymap.end(); it++) {
		if ((*it).second > max_length_key) {
			max_length = (*it).second;
			max_length_key = (*it).first;
		}
	}
	// 判断
	if (max_length>= k/2) good_array_nums++;

	for (int i = k; i < n; i++)
	{
		arraymap[a[i - k]]--;  // 删除
		// 获得最大长度的key

		if (arraymap[a[i - k]] == 0) arraymap.erase(a[i - k]);
		if (arraymap.find(a[i]) == arraymap.end())  // 增加
		{
			arraymap[a[i]] = 1;
		}
		else
		{
		    arraymap[a[i]] ++;
		}
		if (good_array(arraymap, k)) good_array_nums++;
	}

	cout << good_array_nums;
}
