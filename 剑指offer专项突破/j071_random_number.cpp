#include <iostream>
#include<cstdlib> 
#include<ctime> 
#include<vector>

using namespace std;

int pickIndex(int* nums, int size, int seed) {
	int sum = 0;
	for (int i = 0; i < size; ++i) { sum += *(nums + i); };
	vector<double> weight(size, 0.0);
	for (int i = 0; i < size; ++i) { 
		weight[i] = *(nums + i) / (double)sum;
		if (i > 0)
		{
			weight[i] += weight[i - 1];
		}
	};

	srand((unsigned)seed);  // 设置随机数种子
	//double randnum = rand();
	double randomweigth = (rand()%100)/99.0 ;  // [0-9] // [0 - RAND_MAX]
	
	int right = size - 1;
	int left = 0;
	while (left <= right)
	{
		if (left == right) return right;
		int mid = (right + left) >> 1;
		if (randomweigth >= weight[mid]) left = mid+1;
		else right = mid;
	}
	return -1;

}


struct A {
	int a;
	union {
		long b;
		short c;
	};
};

struct B {
	char e;
	struct A d;
	int f;
};


#include <stdio.h>
#define ADD(a, b) a+ b
#pragma pack(8)


struct One {
	double d;
	char c;
	int i;
};

struct Two {
	char c;
	double d;
	int i;
};




int main()
{
	unsigned long T = 3;
	unsigned int a[] = { 0, 1, 11 };
	for (int i = 0; i < T; i++)
	{
		if (a[i] <= 10) 
		{
			// 偶数牛大，jishu牛二
			if (a[i] % 2 == 0)
			{
				cout << 1 << endl;
			}
			else
			{
				cout << 2 << endl;
			}
		}
		if (a[i] > 10)  // 一直牛大
		{
			cout << 1 << endl;
		}
	}
	
	return 0;
}

