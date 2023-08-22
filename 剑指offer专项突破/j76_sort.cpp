#include <iostream>


using namespace std;
void swap(int* a, int recoder, int explorer) {
	if (recoder != explorer) {
		int temp = *(a + explorer);
		*(a + explorer) = *(a + recoder);
		*(a + recoder) = temp;
	}
}

void quickSort(int* a, int s, int e) { 
	int explorer = s;
	int recoder = s - 1;
	// 不随机选取，就选择最后一个进行排序
	if (s < e) {
		for (explorer ; explorer < e; ++explorer)
		{
			if (*(a + explorer) < *(a + e))
			{
				++recoder;
				swap(a, recoder, explorer);
			}
		}

		++recoder;
		swap(a, recoder, e);
		quickSort(a, s, recoder - 1);
		quickSort(a, recoder + 1, e);
	}
}

int quickSort1(int* a, int s, int e) {
	int explorer = s;
	int recoder = s - 1;
	// 不随机选取，就选择最后一个进行排序
	if (s < e) {
		for (explorer; explorer < e; ++explorer)
		{
			if (*(a + explorer) <= *(a + e))
			{
				++recoder;
				swap(a, recoder, explorer);
			}
		}
	}
	++recoder;
	swap(a, recoder, e);
	return recoder;
}


int quickSortFindMaxK(int* a, int n, int k) {
	int* arr = new int[n];
	memcpy(arr, a, sizeof(int)*n);

	int recoder = quickSort1(arr, 0, n-1);
	int s = 0;
	int e = n - 1;
	while ((n - recoder) != k)
	{
		if ((n - recoder) < k) {
			e = recoder - 1;
			recoder = quickSort1(arr, s, e);
		}
		else {
			s = recoder + 1;
			recoder = quickSort1(arr, s, e);
		}
	}
	//delete[] arr;
	int res = *(arr + recoder);
	return res;
}



void mergeSort(int* src, int n) {
	int* dst = new int[n];
	for (int seg = 1; seg < n; seg+=seg)  // 每一段长度 (1,1)  (2,2)  (4,4)中1,2,4,8
	{
		for (int start = 0; start < n; start += 2 * seg)  // +2*seg
		{
			int mid = min(start+seg, n);
			int end = min(start + 2 * seg, n);
			int i = start, j = mid, k = start;
			while (i < mid || j < end) {
				if (j == end || (*(src + i) < *(src + j) && (i < mid)))
				{
					*(dst+(k++)) = *(src + (i++));
				}
				else
				{
					*(dst + (k++)) = *(src + (j++));
				}
			}
		}
		//int* temp = src;
		//src = dst;
		//dst = temp;
		memcpy(src, dst, sizeof(int)*n);
	}
	delete[] dst;
	return;
}

void sortFun(int* scr, int* dst, const int& n, int seg)
{
	for (int start = 0; start < n; start += seg * 2)
	{
		int mid = min(start + seg,n);
		int end = min(start + 2 * seg, n);
		int i = start, j = mid, k = start;
		while (i < mid || j < end)
		{
			if (j == end || (i<mid && *(scr + j)>*(scr + i)))  // i
			{
				*(dst + k++) = *(scr + i++);
			}
			else  // j
			{
				*(dst + k++) = *(scr + j++);
			}
		}
	}
	memcpy(scr, dst, sizeof(int) * n);
}

void mergeFun(int* src, int* dst, const int& n, int seg) {
	if (seg == 1) // 排序
	{
		sortFun(src, dst, n, seg);
		return;
	}
	else
	{
		mergeFun(src, dst, n, seg>>1); // 对于seg/2长的序列已经排序完毕，下面对seg长的序列排序
		sortFun(src, dst, n, seg);
		return;
	}

}



void mergeFun1(int* src, int* dst, int s, int e, int& n) {
	if (s + 1 >= e) return;

	int mid = (s+e)>>1;
	mergeFun1(src, dst, s, mid, n);
	mergeFun1(src, dst, mid, e, n);


	int i = s, j = mid, k = s;
	while (i < mid || j < e)
	{
		if (j == e || (i < mid && *(src + j)>*(src + i)))  // i
		{
			*(dst + k++) = *(src + i++);
		}
		else  // j
		{
			*(dst + k++) = *(src + j++);
		}
	}
	memcpy(src, dst, sizeof(int)*n);
}


// 归并排序递归方法
void mergeSortRecursion(int* src, int n) {
	int* dst = new int[n];
	//int seg = (n+1) >> 1;
	memcpy(dst, src, sizeof(int) * n);
	mergeFun1(src, dst, 0, n, n);
	delete[] dst;
}


int main() {
	int a[] = { 3,2,3,1,2,5,2 };  //  第三大的数字
	int n = sizeof(a) / sizeof(a[0]);
	//int k = 5;
	//int kmax = quickSortFindMaxK(a, n, k);  // []
	//cout << kmax;
	mergeSortRecursion(a, n);
	for (int i = 0; i < n; i++)
	{
		cout << *(a + i) << " ";
	}
}
