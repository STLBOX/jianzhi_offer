#include <iostream>
#include <list>

using namespace std;

void swap(int a[], int& i, int& j) {
	if (i != j)
	{
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

void recursion(int i, int a[], const int& nums_length, list<list<int>>& result, list<int>& subset, int* indexs)
{
	if (i == nums_length)
	{
		result.push_back(subset);
	}
	else
	{
		// 决定选择第几个，被选择了的直接跳过
		for (int choose = i; choose < nums_length; choose++)
		{
			// if (*(indexs + choose) == 0)
			subset.push_back(a[choose]);
			swap(a, choose, i);
			// *(indexs + choose) = 1;  // 锁住
			recursion(i + 1, a, nums_length, result, subset, indexs);
			swap(a, choose, i);
			subset.pop_back();
			// *(indexs + choose) = 0;  // 开锁

		}
	}
}


list<list<int>> find_all_permutation(int a[], const int& nums_length)
{
	list<list<int>> result;
	list<int> subset;
	int* indexs = new int[nums_length]();    // 默认的初始化为0
	recursion(0, a, nums_length, result, subset, indexs);
	delete[] indexs;
	return result;
}


int main() {
	int a[] = { 1,2,3 };
	int nums_length = int(sizeof(a) / sizeof(int));
	list<list<int>> subsets = find_all_permutation(a, nums_length);
	for (auto it = subsets.begin(); it != subsets.end(); ++it)
	{
		for (auto it_sub = (*it).begin(); it_sub != (*it).end(); ++it_sub)
		{
			cout << *(it_sub) << "\t";
		}
		cout << endl;
	}
}