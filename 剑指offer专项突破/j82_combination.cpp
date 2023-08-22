#include <iostream>
#include <list>
using namespace std;

int find_next_index(int const nums[], int index, int const& nums_lenght) {
	int number = nums[index];
	while (nums[index] == number)
	{
		++index;
		if (index == nums_lenght) return index;
	}
	return index;
}

void helper(int const nums[], int index, list<int>& subset, list<list<int>>& result, int const& nums_lenght, int target)
{
	if (target == 0)
	{
		// list<int> subset_new(subset);
		result.push_back(subset);
	}
	else if (target > 0 && index < nums_lenght)
	{
		int next_index = find_next_index(nums, index, nums_lenght);
		helper(nums, next_index, subset, result, nums_lenght, target); // 跳过当前值？，之后的所有相同值
		subset.push_back(nums[index]);  // 添加e
		helper(nums, index+1, subset, result, nums_lenght, target - nums[index]);
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
	int a[] = { 2, 2, 2, 4, 3, 3};
	int nums_lenght = int(sizeof(a) / sizeof(int));
	list<list<int>> subsets = find_subsets(a, nums_lenght, 8);
	for (auto it = subsets.begin(); it != subsets.end(); ++it)
	{
		for (auto it_sub = (*it).begin(); it_sub != (*it).end(); ++it_sub)
		{
			cout << *(it_sub) << "\t";
		}
		cout << endl;
	}
}