#include <iostream>
#include <algorithm>

using namespace std;

bool compare(int a, int b) {
    return a > b;
}

// 插入排序 O(n^2)

// 快速排序 O(n^2)，递归
void swap(int* arr, int a, int b) {
    int temp = *(arr + a);
    *(arr + a) = *(arr + b);
    *(arr + b) = temp;
}

void Quick_Sort(int* arr, int begin, int end)
{
    if (begin >= end) return;
    int i = begin;
    int j = end;
    while (i!=j)
    {
        while (*(arr + j) >= *(arr + begin) && i < j) --j;  // 找到第一次小于begin的元素

        while (*(arr + i) <= *(arr + begin) && i < j) ++i;  // 找到第一次大于begin的元素 

        if (i < j) swap(arr, i ,j);
    }
    swap(arr, begin, i);
    Quick_Sort(arr, begin, i - 1);  // 二分法
    Quick_Sort(arr, i+1, end);  // 二分法
}

int main()
{
    int a[10] = { 9,6,3,8,5,2,7,4,1,0 };
    sort(a, a + 10, compare); //compare指定排序规则
    for (int i = 0; i < 10; i++)
        cout << a[i] << endl;
    return 0;
}
