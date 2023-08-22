#include <iostream>
#include <queue>

using namespace std;


template <class T>
struct compare {
	bool operator()(const T& x, const T& y) const { return x > y; }
};


void test_default_priority_queue(priority_queue <float, vector<float>, greater<float>> q)
{
	q.push(4.4);
	q.push(22.4);
	q.push(55.4);
	while (!q.empty())
	{
		cout << q.top() << ' ';
		q.pop();
	}
}


// 最小堆
int find_k_max(priority_queue <int, vector<int>, greater<int>>& q, int k, int& insert_value) {
	if (q.size() < k) { 
		q.push(insert_value);
		return 0;
	}
	else if (q.top() < insert_value)
	{	
		q.pop();
		q.push(insert_value);
	}
	return q.top();
}



int main001(){
	int a[6] = { 4,5,8,2,3,5 };
	int size = 6;
	int k = 3;
	priority_queue <int, vector<int>, greater<int>> q;
	for (int i = 0; i < size; ++i) {
		cout << find_k_max( q, k, *(a+i)) << endl;
		cout << "size of q:" << q.size() << endl;
	}
	return 0;
}


string decode_string(string& str, int& index) {
	if (str.empty()) return "";
	string substr;
	while(index < str.size())
	{
		string nums;
		if (str[index] >= '0' && str[index] <= '9') {
			nums += str[index];
			while (str[index + 1] >= '0' && str[index + 1] <= '9') {
				++index;
				nums += str[index];
			}
			// point to 3, 递归
			index += 2;
			string strinter = decode_string(str, index);
			// 
			int num = 0;
			for (int j = 0; j < nums.size(); ++j) {
				num += (int)(nums[j] - '0') * pow(10, j);
			}
			while (num != 0) {
				substr.append(strinter);
				--num;
			}

		}
		else if(str[index] == ']')
		{
			++index;
			return substr;
		}
		else
		{
			substr += str[index];
			++index;
		}
		
	}

	return substr;
}


int main003() {
	string str = "3[a]2[bc]x";
	int index = 0;
	string res = decode_string(str, index);
	cout << res;
	return 0;
};



#include <algorithm>
#define INF 0x3f3f3f3f

int cost_fun(vector<int>& houses, int i, int j) {
	int mid = (i + j) >> 1;
	int cost = 0;
	for (int h = i; h <= j; ++h) 
	{
		cost += abs(houses[h] - houses[mid]);
	}
	return cost;
}

int dp_fun(vector<int>& dp, vector<vector<int>>& cost, int i) {
	int minv = cost[0][i];
	for (int m = 1; m <= i; ++m) {
		minv = min(minv, dp[m - 1] + cost[m][i]);  // [0---m-1]分配j-1  [m---i]分配1
	}
	return minv;
}

int minTotalDistance(vector<int>& houses, int k) {
	// 计算cost数组
	vector<vector<int>> cost(houses.size(), vector<int>(houses.size(), 0));
	for (int i = 0; i < houses.size(); i++)
	{
		for (int j = i; j < houses.size(); j++)
		{
			cost[i][j] = cost_fun(houses, i, j);
		}

	}
	// dp数组 init 仅与 j-1
	vector<int> dp(houses.size(), INF);  // [i,j=0]
	for (int j = 1; j < k + 1; ++j) {
		for (int i = houses.size()-1; i >= 0; --i) {
			// 求得最小值
			dp[i] = dp_fun(dp, cost, i);
		}
		dp[0] = 0;
	}
	return dp[houses.size()-1];
}

int main005() {
	vector<int> houses = { 1,4,8,10,20 };
	int k = 3;
	cout << minTotalDistance(houses, k);
	return 0 ;
}


#include <map>
#include <vector>

vector<int> findSubstring(string s, vector<string>& words) {
	// write code here
	int k = words[0].size();
	int n = words.size();
	int i = 0;
	// map记录words
	map<string, int> dict;
	for (auto item : words) {
		if (dict.find(item) == dict.end()) {
			dict.emplace(item, 1);
		}
		else ++dict[item];
	}

	vector<int> res;
	int start = 0;
	i = n * k;
	// 用前n个字符串初始化
	for (int j = 0; j < i; j += k)
	{
		string substr = s.substr(j, k);
		if (dict.find(substr) != dict.end()) --dict[substr];
	}
	bool judge = true;
	for (auto it : dict)
	{
		judge &= (it.second == 0);
	}
	if (judge) res.push_back(start);

	while (i < s.size())
	{
		// 处理当前字符串
		string substr = s.substr(i, k);
		if (dict.find(substr) != dict.end()) --dict[substr];
		substr = s.substr(start, k);
		if (dict.find(substr) != dict.end()) ++dict[substr];
		i += k;
		start += k;

		bool judge = true;
		for (auto it : dict)
		{
			judge &= (it.second == 0);
		}
		if (judge) res.push_back(start);
	}
	return res;
}


int main() {
	string s = "barfoofoobarthefoobarman";
	vector<string> words;
	words.push_back("bar");
	words.push_back("foo");
	words.push_back("the");
	vector<int> res = findSubstring(s, words);
	for (int i = 0; i < res.size(); ++i) cout << res[i];
	return 0;
}