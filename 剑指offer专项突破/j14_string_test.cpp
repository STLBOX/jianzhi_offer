#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

int test_string()
{
	char site[7] = { 'R', 'U', 'N', '\0', 'O', 'B', '\0' };  // declare a string
	char site2[7] = "RUNOOB";
	char site3[7];
	strcpy_s(site3, site);
	cout << strlen(site3) << endl;  // len������'\0'��ֹͣ���Ҳ�ͳ��'\0'
	cout << strlen(site) << endl;  // len������'\0'��ֹͣ���Ҳ�ͳ��'\0'
	cout << strlen(site2) << endl;
	cout << site << endl;
	cout << site2 << endl;

	string str1 = "runoob";
	string str2 = "google";
	string str3;
	int len;
	// ���� str1 �� str3;
	str3 = str1;
	cout << "str3 : " << str3 << endl;

	// ���� str1 �� str2
	str3 = str1 + str2;
	cout << "str1 + str2 : " << str3 << endl;

	// ���Ӻ�str3 ���ܳ���
	len = str3.size();
	cout << "str3.size() :  " << len << endl;

	string str4;
	transform(str1.begin(), str1.end(), str1.begin(), toupper);
	cout << &str1[5] << endl;
	return 0;
}

int test_map(){

	map<string, string> namemap;
	namemap["����Ⱥ"] = "��ɽ�������ˣ��˳ƾ��ӽ�";
	namemap["������"] = "�䵱�����ˣ�̫��ȭ��ʼ��";
	namemap["��������"] = "��һ���֣���������";
	//���ҡ�
	if (namemap.find("����Ⱥ") != namemap.end()) {
		cout << namemap["����Ⱥ"] << endl;
	}
	return 0;
}

typedef struct str_hash {
	size_t operator()(const string& str) const
	{
		unsigned long __h = 0;
		for (auto it = str.begin(); it != str.end(); ++it) {
			__h = 5 * __h + *it;
		}
		return size_t(__h);
	}
}str_hash;


struct compare_str {
	bool operator()(const char* p1, const char* p2) const{
		return strcmp(p1, p2) == 0;
	}
};

int test_hash_test() {
	typedef unordered_map<const char*, string, hash<const char*>, compare_str> StrIntMap;
	StrIntMap namemap;
	namemap["����Ⱥ"] = "��ɽ�������ˣ��˳ƾ��ӽ�";
	namemap["������"] = "�䵱�����ˣ�̫��ȭ��ʼ��";
	string str = namemap["������"];
	cout << namemap["������"] << endl;
	return 0;
}

void str_count(int hash_table[], string& str) {
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		++hash_table[*it - 97];
	}
}

bool all_zero(const int a[])
{
	bool result = true;
	for (int i = 0; i < 26; i++)
	{
		result &= (a[i] == 0);
	}
	return result;
}

int main() {
	string s1 = "stop";
	string s2 = "potsstoptops";  // "a" 01100001	0d97	0x61
	int hash_table[26] = {0};
	str_count(hash_table, s1);
	for (int i = 0; i < int(s1.size()); i++)
	{
		--hash_table[s2[i] - 97];
	}
	if (all_zero(hash_table))
	{
		for (int j = 0; j < int(s1.size()); j++)
			cout << s2[j];
		cout << endl;
	}

	for (int i = s1.size(); i < int(s2.size()); i++)
	{
		int head = i - s1.size();  // del head contain rear�� namely i;  [head+1,..,rear]
		--hash_table[s2[i] - 97];
		++hash_table[s2[head] - 97];
		if (all_zero(hash_table))
		{
			for (int j = head + 1; j < i + 1; j++)
				cout << s2[j];
			cout << endl;
		}
	}
	return 0;
}