#include <iostream>
#include <list>

using namespace std;


void helper(int const nums[], int index, list<int>& subset, list<list<int>>& result, int const& nums_lenght)
{
    if (subset.size() == 3)
	{
		list<int> subset_new(subset);
		result.push_back(subset_new);  // 自动构造了新对象？
	}
	else if(index < nums_lenght)
	{
		helper(nums, index + 1, subset, result, nums_lenght);
		subset.push_back(nums[index]);
		helper(nums, index + 1, subset, result, nums_lenght);
		subset.pop_back();
	}
} 

list<list<int>> find_subsets(int const nums[], int const& nums_lenght) {
	list<int> subset;
	list<list<int>> result;
	if (nums_lenght == 0)
	{
		return result;
	}
	else
	{
		helper(nums, 0, subset, result, nums_lenght);
		return result;
	}
}

int main() {
	int a[] = { 1,2,3,4};
	int nums_lenght = int(sizeof(a) / sizeof(int));
	list<list<int>> subsets = find_subsets(a, nums_lenght);
	for (auto it = subsets.begin(); it != subsets.end(); ++it)
	{
		for (auto it_sub = (*it).begin(); it_sub != (*it).end(); ++it_sub)
		{
			cout << *(it_sub) << "\t";
		}
		cout << endl;
	}
}