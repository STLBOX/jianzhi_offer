#include <iostream>
#include <list>

using namespace std;

// 允许重复选择元素的组合
void helper(int const nums[], int index, list<int>& subset, list<list<int>>& result, int const& nums_lenght, int target)
{
	if (target == 0 && index < nums_lenght)
	{
		// list<int> subset_new(subset);
		result.push_back(subset);  
	}
	else if (target > 0 && index < nums_lenght)
	{
		helper(nums, index + 1, subset, result, nums_lenght, target); // 不做操作index+1
		subset.push_back(nums[index]);  // 添加e
		helper(nums, index, subset, result, nums_lenght, target- nums[index]);
		subset.pop_back();
	}
}

list<list<int>> find_subsets(int const nums[], int const& nums_lenght, int target) {
	list<int> subset;
	list<list<int>> result;
	helper(nums, 0, subset, result, nums_lenght, target);
	return result;

}

int main() {
	int a[] = { 1,2,3,4 };
	int nums_lenght = int(sizeof(a) / sizeof(int));
	list<list<int>> subsets = find_subsets(a, nums_lenght, 4);
	for (auto it = subsets.begin(); it != subsets.end(); ++it)
	{
		for (auto it_sub = (*it).begin(); it_sub != (*it).end(); ++it_sub)
		{
			cout << *(it_sub) << "\t";
		}
		cout << endl;
	}
}