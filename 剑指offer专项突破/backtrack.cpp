#include <iostream>
#include <list>
#include <vector>

using namespace std;


void recursion_tree(list<list<int>>& solves, list<int>& solve, int num, int sum, int* arr, int size)
{
	if (sum == 8) {
		solves.push_back(solve);
	}

	while (sum < 8 && num < size) {
		solve.push_back(*(arr + num));
		sum += *(arr + num);
		recursion_tree(solves, solve, num, sum, arr, size);
		sum -= *(arr + num);
		solve.pop_back();
		num++;
	}
	return;
}

list<list<int>> find_all_set(int* arr, int target, int size) {
	list<list<int>> solves;
	list<int> solve;
	int num = 0;
	recursion_tree(solves, solve, num, 0, arr, size);
	return solves;
}


// 回溯，给定一个没有重复数字的正整数集合，请列举出所有元素之和等于某个给定值的所有组合。
int main1() {
	int arr[3] = { 2,3,4 };
	int target = 8;
	int size = 3;
	list<list<int>> solves = find_all_set(arr, target, size);
	for (auto it : solves) {
		for (auto its : it) {
			cout << its << " ";
		}
		cout << endl;
	}
	return 0;
}

// 这个也是DFS
void subsets_BFS(int* arr, int size, int num, list<list<int>>& subsets, list<int>& subset) {
	if (num == size) {
		subsets.push_back(subset);
		return;
	}
	subsets_BFS(arr, size, num+1, subsets, subset);
	subset.push_back(*(arr + num));
	subsets_BFS(arr, size, num+1, subsets, subset);
	subset.pop_back();  // 特别注意如果按照引用传递，这里必须要写。
	return;
}


list<list<int>> find_all_subsets(int* arr, int size) {
	list<list<int>> subsets;
	list<int> subset;
	subsets_BFS(arr, size, 0, subsets, subset);
	return subsets;
}


// 回溯，求集合的所有子集 BFS
int main2() {
	int arr[3] = {1,2,3};
	int size = 3;
	list <list<int>> res = find_all_subsets(arr, size);

	for (auto it : res) {
		for (auto its : it) {
			cout << its << " ";
		}
		cout << endl;
	}
	return 0;
}


void comber(int n, int k, int index, list<list<int>>& combs, list<int>& comb) {
	if (comb.size() == 2) {
		combs.push_back(comb);
		return;
	}
	if (index == n + 1) return;

	comber(n, k, index+1, combs, comb);  // 不考虑index
	comb.push_back(index);
	comber(n, k, index + 1, combs, comb);  // 考虑index
	comb.pop_back();
}

list<list<int>> find_all_combination(int n, int k) {
	list<list<int>> combs;
	list<int> comb;
	comber(n, k, 1, combs, comb);
	return combs;
}

// 回溯，求给定集合[1,..,n]中指定数量k的组合
int main80() {
	int k = 2;
	int n = 4;
	list<list<int>> res = find_all_combination(n , k);
	for (auto it : res) {
		for (auto its : it) {
			cout << its << " ";
		}
		cout << endl;
	}
	return 0;
}

void sum_eq(int* arr, int size, int target, list<list<int>>& combs, list<int>& comb, int& sum, int index) {
	if (sum == target) {
		combs.push_back(comb); 
	}
	if (sum > target) {
		return;
	}
	while (index < size) {
		comb.push_back(*(arr + index));
		sum += *(arr + index);
		sum_eq(arr, size, target, combs, comb, sum, index); // 需要更新comb，sum，index
		comb.pop_back();
		sum -= *(arr + index);
		index++;
	}
	return;
}


void sum_eq2(int* arr, int size, int target, list<list<int>>& combs, list<int>& comb, int& sum, int index) {
	if (sum == target) {
		combs.push_back(comb);
	}
	if (sum < target && index < size) {
		sum_eq2(arr, size, target, combs, comb, sum, index+1);  // 不要 index
		comb.push_back(*(arr + index)); // 要index
		sum += *(arr + index);
		sum_eq2(arr, size, target, combs, comb, sum, index);  // 不要 index
		comb.pop_back();
		sum -= *(arr + index);
	}

	return;
}

list<list<int>> find_sum_eq(int* arr, int size, int target)
{
	list<list<int>> combs;
	list<int> comb;
	int sum = 0;
	int index = 0;
	sum_eq2(arr, size, target, combs, comb, sum, index);
	return combs;
}

// 允许重复选择元素的组合
int main81() {
	int arr[3] = { 2, 3, 5 };
	int size = 3;
	int target = 8;
	list<list<int>> res = find_sum_eq(arr, size, target);
	for (auto it : res) {
		for (auto its : it) {
			cout << its << " ";
		}
		cout << endl;
	}
	return 0;
}

void swap(int* arr, int a, int b) {
	if (a == b) return;
	else {
		int temp = *(arr + a);
		*(arr + a) = *(arr + b);
		*(arr + b) = temp;
	}
	return;
}

int nextelement(int* arr, int size, int index) {
	for (int i = index + 1; i < size; ++i) {
		if (*(arr + index) == *(arr + i)) {
			swap(arr, index + 1, i);
			index++;
		}
	}
	return index;
}

void repeat_combs(int* arr, int size, int target, int index, list<list<int>>& combs, list<int>& comb, int& sum){
	if (target == sum) {
		combs.push_back(comb);
		return;
	}
	if (index < size && target > sum) {  // 决定跳过某个元素就跳过全部相同的元素
		// 跳过所有相同元素，改变原始arr
		int jumpindex = nextelement(arr, size, index);
		repeat_combs(arr, size, target, jumpindex+1, combs, comb, sum);
		// 保留该元素
		comb.push_back(*(arr+index));
		sum += *(arr + index);
		repeat_combs(arr, size, target, index+1, combs, comb, sum);
		comb.pop_back();
		sum -= *(arr + index);
	}
	return;
}


list<list<int>> find_repeat_combs(int* arr, int size, int target) {
	list<list<int>> combs;
	list<int> comb;
	int sum = 0;
	repeat_combs(arr, size, target, 0, combs, comb, sum);
	return combs;
}


int main44() {
	int arr[6] = { 2,4,2,3,2,3 };
	int size = 6;
	int target = 8;
	list<list<int>> res = find_repeat_combs(arr, size, target);
	for (auto it : res) {
		for (auto its : it) {
			cout << its << " ";
		}
		cout << endl;
	}
	return 0;
}

// deal with struct


