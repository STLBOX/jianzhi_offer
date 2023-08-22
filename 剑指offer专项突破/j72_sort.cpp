#include <iostream>
#include <algorithm>

using namespace std;

bool compare(int a, int b) {
    return a > b;
}

// �������� O(n^2)

// �������� O(n^2)���ݹ�
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
        while (*(arr + j) >= *(arr + begin) && i < j) --j;  // �ҵ���һ��С��begin��Ԫ��

        while (*(arr + i) <= *(arr + begin) && i < j) ++i;  // �ҵ���һ�δ���begin��Ԫ�� 

        if (i < j) swap(arr, i ,j);
    }
    swap(arr, begin, i);
    Quick_Sort(arr, begin, i - 1);  // ���ַ�
    Quick_Sort(arr, i+1, end);  // ���ַ�
}

int main()
{
    int a[10] = { 9,6,3,8,5,2,7,4,1,0 };
    sort(a, a + 10, compare); //compareָ���������
    for (int i = 0; i < 10; i++)
        cout << a[i] << endl;
    return 0;
}
