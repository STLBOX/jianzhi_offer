// ����������Ӧ�� ��������
// ���������洢<key, value> ��ֵ��  set�ļ�ֵ����ͬ same
// ���ι������� �� ��ϣ�ṹ��������
/* ����
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
	bool operator() (const int& a, const int& b) const{  // ��Ҫע�⴫�����key
		return (a < b) ;
	}
};

auto fun = [](const int& a, const int& b) {return a < b;};

void test_map() {

	map<int, int> mymap;  // less<int> greater<int> ��key����
	// ����Ԫ��
	mymap.insert(make_pair(0, 10));
	pair<map<int,int>::iterator, bool> a = mymap.insert(make_pair(1,9));
	cout << a.second << endl;
	cout << (*(a.first)).second << endl;
	cout << mymap[1] << endl;
	cout << mymap[0] << endl;
	// cout << mymap.at(3) << endl;
	cout << "pair compare:" << (make_pair(1, 2) < make_pair(0, 3)) << endl;
	mymap.insert(a.first, make_pair(2, 8));  // �ڲο�λ��iterator����pair
	list<pair<int, int>> mylist;
	mylist.push_back(make_pair(3, 7));
	mylist.push_back(make_pair(4, 6));
	mymap.insert(mylist.begin(), mylist.end());  // [ ) ע��ǰbi������
	cout << mymap.at(4) << endl;
	mymap[5] = 5;  // Ҳ�ܲ���,�ȴ������޸�
	cout << mymap.at(5) << endl;
	mymap.emplace(6, 4);  // ��ѵĲ��뷽ʽ
	cout << mymap.at(6) << endl;  // ������Ҫ���ڶ�ӦԪ�صĹ��캯��

	// ###ɾ��Ԫ��
	// ɾ��ָ��λ�õ�Ԫ��
	mymap.erase(mymap.find(6));  // find ����itr������eraseɾ��.
	// cout << mymap.at(6) << endl;  // ����
	mymap.emplace(6, 4);  // ����
	mymap.erase(6); // ����ֱ��ɾ��keyΪ6��Ԫ��  Ҳ����ɾ��[itrs�� itre)�����е�Ԫ��

	// map.swap ��������map�� ��Ԫ��
	// map.clear 
	// iterator find(const key_type& x)  Ҳ���Դ���const����
	int num = mymap.count(7);
	cout << num << endl;
	for (auto it : mymap) {  // ��������õ�����
		cout << it.first << "--" ;
	}
	// �Զ������򷽷����Զ��庯��������ָ�룬����Ҫ�Զ���pair������lambda����
	// �Զ��庯��, 
	// ����������
	cout << endl << (*(mymap.begin())).first << endl;
}


// lambda��������
#include <functional>

void test_lambda(){
	// ������ʽ  auto func = [capture] (params) opt->ret{func_body;};
	// opt��mutable �����޸İ�ֵ���������Ĳ�����exception throw()
	auto func1 = [](int a) -> int {return a + 1; };
	auto func2 = [](int a)mutable {return a + 1; };
	cout << func1(1) << " " << func2(2) << endl;
	// [&] �����ⲿ���ã�����Ϊ�����ں�������ʹ��
	// [=] �����ⲿ�������ں������ڴ��ڸ��������ǲ����޸ĵ�
	int a = 10, b = 20;
	auto f2 = [&]() {return a++; };  // �����ò�����ͬ�ڴ�ռ�
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
// string ���ܽᣬ���ո���߰����ŷָ����γ�string����ȡ�
void test_string() {
	// ���췽��
	string s0 = "fageqwepgh";
	string s1;
	string s2("hello,���");  // ��c�ַ�������
	string s3(10, 'a');  // 10��a�������
	string s4(s2);  // ��������
	string s5(s2, 2);  // "110"
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
	cout << s4.c_str() << endl;
	cout << s5.c_str() << endl;

	char c[20];
	strcpy_s(c, s2.c_str());
	cout << c << endl;
	cout << "size():\t" << s2.size() << endl;  // ���ռ�����ֽ�
	cout << "length():\t" << s2.length() << endl;
	cout << s2[4] << s2[5] << '\0' << s2[3] << endl;  // s2[5]ɶ��û�� '\0' ��������size��
	cout << "##########################################" << endl;
	s0 = "fqfq";
	cout << "capacity():\t" << s0.capacity() << "  " << s0.size() << endl;
	cout << s0.empty() << endl;
	// clear(), resize(), reserve()
	// string �����ķ��� []
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
		cout << "�ļ������ں�׺" << endl;
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
	//find�Ҳ�������-1��������size_t����finish��һ���ܴ������
	size_t finish = url.find('/', start + 3);
	cout << url.substr(start + 3, finish - start - 3) << endl;
	//ɾ��url��ǰ׺
	int pos = url.find("://");
	url.erase(0, pos + 3);
	cout << url << endl;
}


#include <cassert>
#pragma warning(disable : 4996)
// sring�Ĺ��졢�������졢��ֵ���������
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

	// ��������
	String(const String& s) {
		// ���_str �Ƿ�Ϊ��
		if (_str) {
			delete[] _str;
			_str = nullptr;
		}
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}

	// ��ֵ��������� = 
	String& operator=(const String& s) {
		// ������Լ���ֱ�ӷ���
		if (_str == s._str) return *this;
		else
		{
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
			return *this;   //������ֵ 
		};
	};

	friend ostream& operator<< (ostream& out, String s){  //����Ϊ��Ԫ����
		// ������Լ���ֱ�ӷ���
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
	// ��Ԫ������ ����Ԫ�����ڳ�Ա����

	return 0;
}