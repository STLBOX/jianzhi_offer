#include <iostream>

using namespace std;

int getTopPos(int* nums, int size) {
	int right = size - 1;
	int left = 0;
	while (left <= right)
	{
		// mid
		int mid = (right + left) >> 1;
		// ȷ��midӦ��ǰ������
		// mid����ֵ������
		if (*(nums + mid) > *(nums + mid - 1) && *(nums + mid) > *(nums + mid + 1)) return mid;

		// mid�����£�l = m��
		else if (*(nums + mid) > *(nums + mid - 1)) left = mid + 1;
		// mid�����£�r = m��
		else if (*(nums + mid) > *(nums + mid + 1)) right = mid - 1;
	}
	return -1;
}


int getOnce(int* nums, int size) {
	int right = size - 1;
	int left = 0;
	while (left <= right)
	{
		if (right == left)   return *(nums + right); // �˳�����

		int mid = (right + left) >> 1;

		if ((mid%2)==0 && *(nums + mid) != *(nums + mid - 1)) left = mid;

		else if ((mid % 2) == 0 && *(nums + mid) == *(nums + mid - 1)) right = mid;

		else if ((mid % 2) != 0 && *(nums + mid) == *(nums + mid - 1)) left = mid + 1;

		else if ((mid % 2) != 0 && *(nums + mid) == *(nums + mid + 1)) right = mid - 1;
	}

	return -1;
}
int main()
{
	int nums[] = {0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,9,9};
	int size = sizeof(nums) / sizeof(nums[0]);
	int top = getOnce(nums, size);
	cout << top;
	return 0;
}