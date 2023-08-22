#include <iostream>
#include <string>

using namespace std;

string max_length_subset(const string& s1) {
	string subs;
	if (s1.size() == 0) return subs;
	else
	{
		int hash_count[26] = {0};
		int max_length = 0;
		int max_length_start = 0;
		int head=0, rear=0;
		// 找到不重复子字符串  【head， rear】,每一次加入head
		while (head < int(s1.size()))
		{
			if (hash_count[s1[head] - 'a'] == 0) {
				hash_count[s1[head] - 'a']++;
				// 记录最大长度
				if ((head - rear + 1) > max_length){
					max_length = head - rear + 1;
					max_length_start = rear;
				}
				head++;
			}
			else if (hash_count[s1[head] - 'a'] == 1) {
				// 删除rear直到其等于0
				while (hash_count[s1[head] - 'a'] != 0)
				{
					hash_count[s1[rear] - 'a']--;
					rear++;
				}
			}
		}

		subs = s1.substr(max_length_start, max_length);
		return subs;
	}
}


int main()
{
	string s1 = "ababcdefg";
	string max_sub = max_length_subset(s1);
	cout << max_sub << endl;
	return 0;
}

