// 序列容器对应的 关联容器
// 关联容器存储<key, value> 键值对  set的键值对相同 same
// 树形关联容器 和 哈希结构关联容器
/* 树形
map
set
multimap
multiset
*/

/* hash
unordered_set
unordered_map
*/
#include <map>
#include <list>
#include <iostream>

using namespace std;

struct mycompare
{
	bool operator() (const int& a, const int& b) const{  // 需要注意传入的是key
		return (a < b) ;
	}
};

auto fun = [](const int& a, const int& b) {return a < b;};

void test_map() {

	map<int, int> mymap;  // less<int> greater<int> 按key排序
	// 插入元素
	mymap.insert(make_pair(0, 10));
	pair<map<int,int>::iterator, bool> a = mymap.insert(make_pair(1,9));
	cout << a.second << endl;
	cout << (*(a.first)).second << endl;
	cout << mymap[1] << endl;
	cout << mymap[0] << endl;
	// cout << mymap.at(3) << endl;
	cout << "pair compare:" << (make_pair(1, 2) < make_pair(0, 3)) << endl;
	mymap.insert(a.first, make_pair(2, 8));  // 在参考位置iterator插入pair
	list<pair<int, int>> mylist;
	mylist.push_back(make_pair(3, 7));
	mylist.push_back(make_pair(4, 6));
	mymap.insert(mylist.begin(), mylist.end());  // [ ) 注意前bi后开区间
	cout << mymap.at(4) << endl;
	mymap[5] = 5;  // 也能插入,先创建再修改
	cout << mymap.at(5) << endl;
	mymap.emplace(6, 4);  // 最佳的插入方式
	cout << mymap.at(6) << endl;  // 但是需要存在对应元素的构造函数

	// ###删除元素
	// 删除指定位置的元素
	mymap.erase(mymap.find(6));  // find 返回itr，交给erase删除.
	// cout << mymap.at(6) << endl;  // 报错
	mymap.emplace(6, 4);  // 插入
	mymap.erase(6); // 可以直接删除key为6的元素  也可以删除[itrs， itre)区间中的元素

	// map.swap 交换两个map中 的元素
	// map.clear 
	// iterator find(const key_type& x)  也可以处理const对象
	int num = mymap.count(7);
	cout << num << endl;
	for (auto it : mymap) {  // 中序遍历得到有序
		cout << it.first << "--" ;
	}
	// 自定义排序方法。自定义函数。重载指针，但需要自定义pair。或者lambda函数
	// 自定义函数, 
	// 迭代器测试
	cout << endl << (*(mymap.begin())).first << endl;
}


// lambda函数测试
#include <functional>

void test_lambda(){
	// 基本形式  auto func = [capture] (params) opt->ret{func_body;};
	// opt：mutable 可以修改按值拷贝过来的参数，exception throw()
	auto func1 = [](int a) -> int {return a + 1; };
	auto func2 = [](int a)mutable {return a + 1; };
	cout << func1(1) << " " << func2(2) << endl;
	// [&] 捕获外部作用；并作为引用在函数体内使用
	// [=] 捕获外部作用域，在函数体内存在副本并且是不能修改的
	int a = 10, b = 20;
	auto f2 = [&]() {return a++; };  // 按引用捕获，相同内存空间
	cout << a << endl;
	auto f3 = [=]() {return a; };
	// auto f6 = [=] {return a++; };
	auto f6 = [=]()mutable {return a++; };  // ok
	f6();
	cout << a << endl;
	auto f5 = [&a]() {a=5;}; 
	f5();
	// auto f6 = [a, &b] {return a + (b++); };
	auto f7 = [=, &b] {return a + (b++); };
	cout << a << endl;

	// 
	function<int(int)> f10 = [](int a) {return a; };
	function<int(int)> f11 = bind([](int a) {return a; }, placeholders::_1);
	cout << f10(100) << endl;
	cout << f11(100) << endl;
}

#include <string>
// string 类总结，按空格或者按逗号分隔，形成string数组等。
void test_string() {
	// 构造方法
	string s0 = "fageqwepgh";
	string s1;
	string s2("hello,你好");  // 用c字符串构造
	string s3(10, 'a');  // 10个a构造对象
	string s4(s2);  // 拷贝构造
	string s5(s2, 2);  // "110"
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
	cout << s4.c_str() << endl;
	cout << s5.c_str() << endl;

	char c[20];
	strcpy_s(c, s2.c_str());
	cout << c << endl;
	cout << "size():\t" << s2.size() << endl;  // 你好占两个字节
	cout << "length():\t" << s2.length() << endl;
	cout << s2[4] << s2[5] << '\0' << s2[3] << endl;  // s2[5]啥都没有 '\0' 不计算在size中
	cout << "##########################################" << endl;
	s0 = "fqfq";
	cout << "capacity():\t" << s0.capacity() << "  " << s0.size() << endl;
	cout << s0.empty() << endl;
	// clear(), resize(), reserve()
	// string 类对象的访问 []
	for (int i = 0; i < 100; ++i) {
		s0.push_back('a');
	}
	cout << s0 << endl;
	size_t position = s0.find('a', 0);
	cout << position << endl;
	// --------------------
	string new_str = s0 + s2;
	cout << new_str;
	// substr(size_t pos=0,size_t n=npos) 
	// erase (size_t pos = 0, size_t len = npos)

}


void test3()
{
	string file("test.cpp");
	size_t pos = file.rfind('.');
	if (pos == string::npos)
	{
		cout << "文件不存在后缀" << endl;
	}
	else {
		cout << file.substr(pos, file.size() - pos) << endl;
		cout << pos << endl;  // file.size() - pos
	}
}


void test4()
{
	string url("http://www.baidu.com/");
	size_t start = url.find("://");
	cout << start << endl;
	if (start == string::npos) {
		cout << "url error" << endl;
		return;
	}
	//find找不到返回-1，但是用size_t接收finish是一个很大的数字
	size_t finish = url.find('/', start + 3);
	cout << url.substr(start + 3, finish - start - 3) << endl;
	//删除url的前缀
	int pos = url.find("://");
	url.erase(0, pos + 3);
	cout << url << endl;
}


#include <cassert>
#pragma warning(disable : 4996)
// sring的构造、拷贝构造、赋值运算符重载
class String {
public:
	String(const char* str=nullptr)
	{
		if (str == nullptr) {
			assert(false);
			return;
		};
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);

	}

	~String() {
		if (_str) {
			delete[] _str;
			_str = nullptr;
		}
	}

	// 拷贝构造
	String(const String& s) {
		// 检测_str 是否为空
		if (_str) {
			delete[] _str;
			_str = nullptr;
		}
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}

	// 赋值运算符重载 = 
	String& operator=(const String& s) {
		// 如果是自己就直接返回
		if (_str == s._str) return *this;
		else
		{
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
			return *this;   //连续赋值 
		};
	};

	friend ostream& operator<< (ostream& out, String s){  //声明为友元函数
		// 如果是自己就直接返回
		out << s._str;
		return out;
	}

private:
	char* _str=nullptr;
};


int main() {
	// test_lambda();
	// test_map();
	String str("sfagag");
	cout << str;
	// 友元函数， 类友元，类内成员函数

	return 0;
}