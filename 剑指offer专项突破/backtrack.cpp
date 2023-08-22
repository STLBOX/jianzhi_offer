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


// ���ݣ�����һ��û���ظ����ֵ����������ϣ����оٳ�����Ԫ��֮�͵���ĳ������ֵ��������ϡ�
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

// ���Ҳ��DFS
void subsets_BFS(int* arr, int size, int num, list<list<int>>& subsets, list<int>& subset) {
	if (num == size) {
		subsets.push_back(subset);
		return;
	}
	subsets_BFS(arr, size, num+1, subsets, subset);
	subset.push_back(*(arr + num));
	subsets_BFS(arr, size, num+1, subsets, subset);
	subset.pop_back();  // �ر�ע������������ô��ݣ��������Ҫд��
	return;
}


list<list<int>> find_all_subsets(int* arr, int size) {
	list<list<int>> subsets;
	list<int> subset;
	subsets_BFS(arr, size, 0, subsets, subset);
	return subsets;
}


// ���ݣ��󼯺ϵ������Ӽ� BFS
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

	comber(n, k, index+1, combs, comb);  // ������index
	comb.push_back(index);
	comber(n, k, index + 1, combs, comb);  // ����index
	comb.pop_back();
}

list<list<int>> find_all_combination(int n, int k) {
	list<list<int>> combs;
	list<int> comb;
	comber(n, k, 1, combs, comb);
	return combs;
}

// ���ݣ����������[1,..,n]��ָ������k�����
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
		sum_eq(arr, size, target, combs, comb, sum, index); // ��Ҫ����comb��sum��index
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
		sum_eq2(arr, size, target, combs, comb, sum, index+1);  // ��Ҫ index
		comb.push_back(*(arr + index)); // Ҫindex
		sum += *(arr + index);
		sum_eq2(arr, size, target, combs, comb, sum, index);  // ��Ҫ index
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

// �����ظ�ѡ��Ԫ�ص����
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
	if (index < size && target > sum) {  // ��������ĳ��Ԫ�ؾ�����ȫ����ͬ��Ԫ��
		// ����������ͬԪ�أ��ı�ԭʼarr
		int jumpindex = nextelement(arr, size, index);
		repeat_combs(arr, size, target, jumpindex+1, combs, comb, sum);
		// ������Ԫ��
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


