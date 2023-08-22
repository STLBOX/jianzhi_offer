#include <iostream>
#include <list>

using namespace std;

void helper(int const nums[], int index, list<int>& subset, list<list<int>>& result, int const& nums_lenght)
{
	if (index == nums_lenght) 
	{
		result.push_back(subset);
	}
	else 
	{
		helper(nums, index + 1, subset, result, nums_lenght);
		subset.push_back(nums[index]);
		helper(nums, index + 1, subset, result, nums_lenght);
		subset.pop_back();
	}
} 1

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
	int a[] = { 1,2};
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