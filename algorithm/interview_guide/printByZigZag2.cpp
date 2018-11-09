#include <iostream>
#include <deque>
#include <queue>
using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
	Node(int x) : value(x), left(NULL), right(NULL) {}
};

void printByZigZag(Node* head) {
	if (NULL == head) 
		return;
	deque<Node*> dq;
	int level = 1;
	Node* last = head;
	dq.push_front(head);
	cout << "Level " << level << " from left to right: ";
	while (!dq.empty()) {
		if (1 == level % 2) {
			// 从左往右遍历
			// 1)从队头出队
			// 2)从队尾入队:先左孩子,后右孩子
			head = dq.front();
			cout << head->value << " ";
			dq.pop_front();
			if (NULL != head->left)
				dq.push_back(head->left);
			if (NULL != head->right)
				dq.push_back(head->right);

			if (head == last && !dq.empty()) {
				last = dq.front();
				++level;
				cout << endl;
				cout << "Level " << level << " from right to left: ";
			}
		} else {
			// 从右往左遍历
			// 1)从队尾出队
			// 2)从队头入队:先右孩子,后左孩子
			head = dq.back();
		   	cout << head->value << " ";	   
			dq.pop_back();
			if (NULL != head->right)
				dq.push_front(head->right);
			if (NULL != head->left)
				dq.push_front(head->left);

			if (head == last && !dq.empty()) {
				last = dq.back();
				++level;
				cout << endl;
				cout << "Level " << level << " from left to right: ";
			}
		}
	}
	cout << endl;
}

Node* generateNode(int value) {
	if (-1 == value)
		return NULL;
	return new Node(value);
}

Node* reconByLevel(int values[]) {
	int index = 0;
	queue<Node*> mq;
	Node* head = generateNode(values[index++]);
	if (NULL == head)
		return NULL;
	mq.push(head);

	while (!mq.empty()) {
		Node* cur = mq.front();
		mq.pop();
		cur->left = generateNode(values[index++]);
		cur->right = generateNode(values[index++]);
		if (NULL != cur->left)
			mq.push(cur->left);
		if (NULL != cur->right)
			mq.push(cur->right);
	}
	return head;
}

int main() {
	int values[] = {1, 2, 3, 4, -1, 5, 6, -1, -1, 7, 8, -1, -1, -1, -1, -1, -1};
	Node* head = reconByLevel(values);
	printByZigZag(head);
	return 0;
}
