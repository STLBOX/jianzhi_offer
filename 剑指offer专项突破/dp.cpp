#include <iostream>

using namespace std;


int helper(int pos, int* climb) {
	if (pos < 2) return climb[pos];
	return min(helper(pos - 1, climb), helper(pos - 2, climb)) + climb[pos];
}


// 计算爬山的最小开销
int main01() {
	int climb[6] = {1,100,1,1,100,1};
	int size = 6;
	int mincost = min(helper(size-1, climb),helper(size-2, climb));  // 等于size-1向上爬的成本或size-2向上爬的成本的最小值
	cout << mincost;
	return 0;
}


// 计算爬山最小开销，使用额外的heap保存递归的结果，每次先查询是否已经计算，算过直接取值而不是递归的方式


void helper1(int pos, int* climb, int* db) {
	if (pos < 2) *(db + pos) = *(climb + pos);
	if (*(db + pos) == 0)
	{
		helper1(pos - 1, climb, db); // 求db中的pos-1
		helper1(pos - 2, climb, db);
		*(db + pos) = min(db[pos-1], db[pos - 2]) + *(climb + pos);
	}
}


int main02() {
	int climb[6] = { 1,100,1,1,100,1 };
	int size = 6;
	int* db = new int[size] {0};  // db保存f(i)，即从i向上爬的成本
	helper1(5, climb, db);  // 等于size-1向上爬的成本或size-2向上爬的成本的最小值
	cout << *(db+5);
	delete[] db;
	return 0;
}

// 单序列问题，状态转移方程，避免重复计算

void maxmoney(int* money, int pos, int* recoder) {
	if (pos == 0) {
		*(recoder + pos) = *(money + pos);
	}
	else if (pos == 1) {
		*(recoder + pos) = max(*(money + pos), *(money + pos-1));  // 确定初始值;
	}
	if (*(recoder + pos) == 0) {
		maxmoney(money, pos - 1, recoder);  // 计算前一个
		maxmoney(money, pos - 2, recoder);  // 计算前两个
		*(recoder + pos) = max(*(recoder + pos - 1), *(recoder + pos - 2) + *(money + pos));
	}
}




int get_max_money(int* money, int num) {
	// 带缓存
	int* recoder = new int[num] {0};
	maxmoney(money, num-1, recoder);
	int res = *(recoder + num - 1);
	return res;
	delete[] recoder;
}


// 迭代代码，空间复杂度为O（1）
int get_max_money_iter(int* money, int num) {
	int mk_1 = *(money + 1);  // 1 
	int	mk_2 = *(money+0); // 0 记录前两次的f(i)
	int mk = 0;
	for (int i = 2; i < num; ++i) {
		mk = max(mk_1, (mk_2 + *(money + i)));
		mk_2 = mk_1;
		mk_1 = mk;
	}
	return mk;
}

// 小偷偷窃
int main89() {
	int money[5] = {2,3,4,5,3};
	int num = 5;
	int maxst = get_max_money_iter(money, num);
	cout << maxst;
	return 0;
}


// 环形房屋偷窃
// 粉刷房子91
  

int mainm001() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		cin >> *(arr + i);
	}
	int x, y;
	cin >> x >> y;

	int d_k = 0;
	int d_k1 = 0;
	int dete = false;
	for (int i = 0; i < n; ++i) {
		d_k = *(arr + i);  // 记录值
		if ((d_k == x && d_k1 == y) || (d_k == y && d_k1 == x)) {
			dete = true;
			break;
		}
		d_k1 = d_k;
	}
	cout << dete;
	return 0;
}


int get_min_dis(int* dis, int size, int x, int y) {
	// 正 x ++ ->y
	int distS = 0;
	int x_next = x;
	int y_next = y;
	while (x != y) {
		distS += *(dis + x);
		x++;
		if (x == size) { x = 0; };
	}
	// 逆 x -- ->y
	int distN = 0;

	while (x_next != y_next) {
		x_next--;
		if (x_next == -1) { x_next = size-1; };
		distN += *(dis + x_next);
	}
	return min(distN, distS);
}


int mainm002() {
	int states = 3;
	
	int dis[3] = {1,2,2};

	int x=2, y=3;
	int distmin = get_min_dis(dis, states, x-1, y-1);
	cout << distmin;
	return 0;
}

int get_min_m(int* arr, int n, int m) {
	// 横 n > 1
	// 每一行的美味度
	int dist_min_n = INT_MAX;
	int* arrn = new int[n];
	for (int i = 0; i < n; ++i) {
		// arr 0-2 i*m i*m+m-1
		int temp = 0;
		for (int col = 0; col < m; ++col) {
			temp += *(arr + i * m + col);
		}
		*(arrn + i) = temp;
	}
	// 开始切 n -1dao
	if (n == 1) { dist_min_n = *arrn;}
	else {
		int S1 = *arrn;  // qian
		int S2 = 0;  // hou
		for (int i = 1; i < n; ++i) { S2 += *(arrn + i);}
		for (int i = 1; i < n; ++i) {
			dist_min_n = min(dist_min_n, abs(S1 - S2));
			S1 += *(arrn + i);
			S2 -= *(arrn + i);
		}
	}

	// 竖 m 》 1
	// 每一column的美味度
	int dist_min_m = INT_MAX;
	int* arrm = new int[m];
	for (int i = 0; i < m; ++i) {
		// arr 0-2 i*m i*m+m-1
		int temp = 0;
		for (int row = 0; row < n; ++row) {
			temp += *(arr + i + row*m);
		}
		*(arrm + i) = temp;
	}
	// 开始切 n -1dao
	if (m == 1) { dist_min_m = *arrm; }
	else {
		int S1 = *arrm;  // qian
		int S2 = 0;;  // hou
		for (int i = 1; i < m; ++i) { S2 += *(arrm + i); }
		for (int i = 1; i < m; ++i) {
			dist_min_m = min(dist_min_m, abs(S1 - S2));
			S1 += *(arrm + i);
			S2 -= *(arrm + i);
		}
	}
	return min(dist_min_n, dist_min_m);
}


int mainm03() {
	int n = 2, m=3;
	int arr[6] = { 1,1,4,5,1,4 };
	int min_m = get_min_m(arr, n, m);
	cout << min_m;
	return 0;
}


#include <list>
#include <vector>
int mainm04() {
	int n = 3;
	int W[3] = { 3,3,12 };
	vector<list<int>> graph(n);
	graph[0].push_back(1);
	graph[1].push_back(2);
	bool* C = new bool[3]{false};  // 0 bai ；1 hong
	return 0;
}

int get_min(int* arr, int size) {
	int minv = *arr;
	for (int i = 1; i < size; ++i) {
		minv = min(minv, *(arr + i));
	}
	return minv;
}

// 确定状态转移方程
// 缓存的方式
int get_min_cost(int* costs, int size, int colors) {
	int* cost_k1 = new int[colors] {0};
	int* cost_k = new int[colors] {0};
	// init cost_k1 for 0 position
	for (int i = 0; i < colors; ++i) {
		*(cost_k1) = *(costs + i * size);
	}
	// state tansfer
	for (int i = 1; i < size; ++i) {
		*(cost_k + 0) = min(*(cost_k + 1), *(cost_k + 2)) + *(costs + i);  // 0
		*(cost_k + 1) = min(*(cost_k + 0), *(cost_k + 2)) + *(costs + i + 1*size);  // 1
		*(cost_k + 2) = min(*(cost_k + 0), *(cost_k + 1)) + *(costs + i + 2*size);  // 2
	}
	memcpy(cost_k1, cost_k, sizeof(int)*colors);
	return get_min(cost_k, colors);
}


int mainj092(){
	int costs[] = { 17,2,16,15,14,5,13,3,1};
	int size = 3;
	int colors = 3;
	int min_cost = get_min_cost(costs, size, colors);
	cout << min_cost;
	return 0;
}

int get_max_exchange(int a) {
	int count = 0;
	while (a>=3)
	{
		int changenums = a / 3;
		int leftnums = a%3;
		count += changenums;
		a = changenums + leftnums;

	}
	if (a == 2) count++;
	return count;
}

#include<set>
int mainh02() {
	int a = 81;
	set<int, less<int>> sets;
	cout << get_max_exchange(a);
	return 0;
}


int otod(string s) {
	int res = 0;
	int size = s.size();
	for (int i = 2; i < size; ++i) {
		char first = s[i];
		if (first >= 'A') res += (first - 'A' + 10) * (1 << (4*(size - 1 - i)));
		else res += (first - '0') * (1 << (4 * (size - 1 - i)));
	}
	return res;
}

int mainh03() {
	string s = "0xAA";
	cout << otod(s);
	return 0;
}


/*
* 输入两个字符串，请求出它们的最长公共子序列的长
度。如果从字符串s1中删除若干字符之后能得到字符串s2，那么字
符串s2就是字符串s1的一个子序列。 95
*/
int max_length(string s1, string s2) {
	// s1小
	int* arr = new int[s1.size()+1]{0}; // 0对应-1  index 1 对应 0
	int curr = 0;
	for (int i = 0; i < (int)s2.size(); ++i) {
		int prev = 0;
		int j;
		for (j = 0; j < (int)s1.size(); ++j) {
			if (s1[i] == s2[j])  curr = *(arr + j) + 1;
			else  curr = max(prev, *(arr + j + 1));
			*(arr + j) = prev;  
			prev = curr;
		}
		*(arr + j) = curr;;
	}
	delete[] arr;
	return curr;
}


int get_max_common_length(string s1, string s2) {
	if (s1.size() < s2.size()) {
		return max_length(s1, s2);
	}
	else {
		return max_length(s2, s1);
	}

}


int mainj095() {
	string s1 = "abcde";
	string s2 = "badfe";
	cout << get_max_common_length(s1, s2);
	return 0;
}


int get_subsequence_nums(string s1, string s2) {
	return 0;
}


int mainj100() {
	string s1 = "appplep";
	string s2 = "apple";
	cout << get_subsequence_nums(s1, s2);
	return 0;
}

bool seprate_equal(int* arr, int size){
	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += *(arr + i);
	}
	if (sum % 2 == 1) return false;
	int target = sum / 2;
	vector<bool > k(target+1, 0), k1(target+1, 0);
	k1[0] = 1;
	k[0] = 1;
	for (int j = 1; j < size + 1; ++j) {
		for (int i = 1; i < target + 1; ++i) {
			if (((i - *(arr + j - 1) >= 0) && k1[i - *(arr + j -1)] == true) || k1[i] == true)
				k[i] = true;
			else k[i] = false;
		}
		k1.swap(k);
	}
	return k[size];
}

int main101() {
	int arr[] = {1,2,3,5};
	int size = 4;
	cout << seprate_equal(arr, size);
	return 0;
}



// 给定正整数数组coins表示硬币的面额和一个目标总额
// t，请计算凑出总额t至少需要的硬币数目。

int find_at_least_num(int* coins, int target, int size) {
	// int* arrk = new int[target + 1]{0};
	int* arrk1 = new int[target + 1]{0};
	// init  0 is unrealise
	for (int j = 0; j < target + 1; ++j) {
		if ((j % (*coins)) == 0) *(arrk1 + j) = j/(*coins);
		else *(arrk1 + j) = -1;  // 无法实现
	}
	// transfer
	for (int i = 1; i < size; ++i) {  // 从第二个开始
		for (int j = target; j >= 1; --j) {
			// find max k
			int maxk = 0;
			for (int k = 0; j >= k * (*(coins + i)); ++k) {
				if (*(arrk1 + j - k * (*(coins + i))) != -1) {
					maxk = k;
					*(arrk1 + j) = min(*(arrk1 + j), *(arrk1 + j - maxk * (*(coins + i))) + maxk);
				}
			}
			// min coins satify target  // 这里有问题
		}
	}
	int temp = *(arrk1 + target);
	delete[] arrk1;
	return temp;
}


// 排列的数目 可重复
int main(){
	int target = 15;
	int coins[] = {1,3,9,10};
	int size = 4;
	cout << find_at_least_num(coins, target, size);
}



