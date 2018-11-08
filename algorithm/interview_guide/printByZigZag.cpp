#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node{
	int value;
	Node* left;
	Node* right;
	Node(int x) : value(x), left(NULL), right(NULL) {}
};

void printByZigZag(Node* head){
	if (NULL == head)
		return;
	queue<Node*> mq;
	mq.push(head);
	int level = 1;
	// 用栈保存下一层的全部结点
	stack<Node*> ms;


	while (!mq.empty()) {
		Node* cur = mq.front();
		// 从左往右入栈
		if (1 == level % 2) {
			cout << "Level " << level << " from left to right: ";
			while (!mq.empty()) {
				if (NULL != cur->left)
					ms.push(cur->left);
				if (NULL != cur->right)
					ms.push(cur->right);

				cout << cur->value << " ";
				mq.pop();
				cur = mq.front();
			}
		} else {	// 从右往左入栈
			cout << "Level " << level << " from right to left: ";
			while (!mq.empty()) {
				if (NULL != cur->right)
					ms.push(cur->right);
				if (NULL != cur->left)
					ms.push(cur->left);

				cout << cur->value << " ";
				mq.pop();
				cur = mq.front();
			}
		}

		cout << endl;
		// 把栈中元素入队
		while (!ms.empty()) {
			mq.push(ms.top());
			ms.pop();
		}

		++level;
	}
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
	mq.push(head);

	while (!mq.empty()) {
		Node* cur = mq.front();
		cur->left = generateNode(values[index++]);
		cur->right = generateNode(values[index++]);

		if (NULL != cur->left)
			mq.push(cur->left);
		if (NULL != cur->right)
			mq.push(cur->right);

		mq.pop();
	}

	return head;
}

int main() {
	Node* head = NULL;
	int values[] = {1, 2, 3, 4, -1, 5, 6, -1, -1, 7, 8, -1, -1, -1, -1, -1, -1};
	head = reconByLevel(values);
	printByZigZag(head);

	return 0;
}
