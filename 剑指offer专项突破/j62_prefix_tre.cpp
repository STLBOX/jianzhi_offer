#include <iostream>
#include <string>

using namespace std;

struct Node {
	Node* next{nullptr};
	bool isword[26]{0};
	bool charset[26]{0};
};

class prefixTree
{
private:
	Node* head = nullptr;
	//Node* creatNode();

public:
	void insert(string);
	bool search(string);
	bool startwith(string);
	prefixTree() = default;
	~prefixTree() = default;
};


void prefixTree::insert(string str) {
	// 如何recoder指向nullptr,创建新Node
	if (head == nullptr) {
		head = new Node;
	}
	Node* recoder = head;
	if (!str.empty())
	{
		recoder->charset[str[0] - 'a'] = true;
	}
	for (size_t i = 1; i < str.size(); ++i) {
		if (recoder->next == nullptr)
		{
			recoder->next = new Node;
		}
		recoder = recoder->next;
		// 如果不是null，直接赋值true
		recoder->charset[str[i] - 'a'] = true;
	}
	// 
	recoder->isword[str[str.size()-1] - 'a'] = true;
}


bool prefixTree::search(string str) {
	if (head == nullptr) return false;
	Node* recoder = head;
	Node* precoder = recoder;
	for (int i = 0; i < str.size(); ++i)
	{
		if (recoder != nullptr) {
			if (recoder->charset[str[i]-'a'] != true) return false;
		}
		else return false;
		precoder = recoder;
		recoder = recoder->next;
	}
	if (precoder->isword[str[str.size()-1] - 'a'] == false) return false;
 	return true;
}

bool prefixTree::startwith(string str) {
	if (head == nullptr) return false;
	Node* recoder = head;
	for (int i = 0; i < str.size(); ++i)
	{
		if (recoder != nullptr) {
			if (recoder->charset[str[i] - 'a'] != true) return false;
		}
		else return false;
		recoder = recoder->next;
	}
	return true;
}

#include<stdio.h>

int main(){
	int p, i;
	char messge[50] = "1";
	cout << sizeof(messge);
	return 0;
} 