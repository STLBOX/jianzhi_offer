#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

// unodered_map  count f;
// sort by f;  不需要全部排序，只要找到最大的k个元素，考虑为min_heap  pair<int, int>  重载"<"

unordered_map<int, int> cout_frequence(const int* arr, const int& len) {
	unordered_map<int, int> dict_freq;
	for (int i = 0; i < len; ++i)
	{
		if (dict_freq.find(*(arr + i)) == dict_freq.end()) dict_freq.insert(make_pair<const int&,int>(*(arr+i),1));
		else dict_freq[*(arr + i)] ++;
	}
	return dict_freq;
}

template<class T>
class mypair{
public:
	T first;
	T second;
public:
	mypair(int a, int b);
	bool operator< (const mypair<T> &) const;
};


template<class T>
mypair<T>::mypair(int a, int b){
	// mypair<T>::pair(a, b);
	first = a;
	second = b;
}

template<class T>
bool mypair<T>::operator< (const mypair<T>& other) const {
	return (*this).second < other.second;
}


priority_queue<mypair<int>> find_highest_freq_k(const unordered_map<int, int>& dict_freq, const int& k) {
	priority_queue<mypair<int>> min_heap;
	for (auto it : dict_freq) {
		if (min_heap.size() < k) min_heap.emplace(it.first, it.second);
		else if (it.second > min_heap.top().second){
			min_heap.pop();
			min_heap.emplace(it.first, it.second);
		}
	}
	return min_heap;
}


int main() {
	int arr[6] = { 1,2,2,1,3,1 };
	int k = 2;
	int len = 6;
	unordered_map<int, int> dict_freq = cout_frequence(arr, len);
	// 最小堆排序
	priority_queue<mypair<int>> min_heap = find_highest_freq_k(dict_freq, k);
	int size = min_heap.size();
	for (int i = 0; i < size; ++i) {
		mypair<int> h = min_heap.top();
		cout << "value:" << h.first << "\tfreq:" << h.second;
		min_heap.pop();
	}
}