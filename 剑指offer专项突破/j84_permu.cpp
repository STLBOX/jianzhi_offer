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

void helper(int index, int a[], list<list<int>>& result, const int& length)
{
	if (index == length) {
		list<int> subset;
		for (int i = 0; i < length; i++)
		{
			subset.push_back(a[i]);
		}
		result.push_back(subset);
	}
	else {
		for (int pad = index; pad < length; pad++)
		{
			if ((pad == index) || (a[pad] != a[index])) 
			{
				swap(a, pad, index);
				helper(index + 1, a, result, length);
				swap(a, pad, index);
			}
		}
	}

}

list<list<int>> permutation(int a[], int length)
{
	list<list<int>> result;
	helper(0, a, result, length);
	return result;
}

int main() {
	int a[] = { 1,1,3 };
	int length = int(sizeof(a) / sizeof(int));
	list<list<int>> result = permutation(a, length);
	for (list<list<int>>::iterator it = result.begin(); it != result.end(); it++)
	{
		for( list<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
		{
			cout << *(it2) << "\t";
		}
		cout << endl;

	}

	return 0;
}