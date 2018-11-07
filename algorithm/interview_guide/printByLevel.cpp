#include <iostream>
#include <queue>
using namespace std;

struct Node{
	int value;
	Node* left;
	Node* right;
	Node(int x) : value(x), left(NULL), right(NULL) {}
};

void printByLevel(Node* head) {
	if (head == NULL)
		return;
	
	queue<Node*> mq;
	Node* last = head;	// 每层最右边的结点
	int level = 1;		

	mq.push(head);	// 先把根结点入队
	cout << "Level " << level << ": ";
	while (!mq.empty()) {
		Node* cur = mq.front();
		cout << cur->value << " ";
		// 把当前结点的孩子结点入队
		if (NULL != cur->left)
			mq.push(cur->left);
		if (NULL != cur->right)
			mq.push(cur->right);
		// 当前结点是这一层的最后一个结点
		// level加1

		if (cur == last) {
			last = mq.back();	// 下一层最后结点
			++level;
			cout << endl;
			if (cur != last)
				cout << "Level " << level << ": ";
		}

		// 当前结点出队
		mq.pop();

	}

}

Node* generateNode(int value) {
	if (-1 == value)
		return NULL;
	return new Node(value);
}

// 层序遍历反序列化
Node* reconTreeByLevel(int values[]) {
	int index = 0;
	Node* head = generateNode(values[index++]);
	queue<Node*> q;
	if (NULL != head)
		q.push(head);
	Node* node = NULL;
	while (index < 15) {
		node = q.front();
		node->left = generateNode(values[index++]);
		node->right = generateNode(values[index++]);
		if (NULL != node->left)
			q.push(node->left);
		if (NULL != node->right)
			q.push(node->right);

		q.pop();
	}
	return head;
}

int main() {
	Node* head = NULL;
	int values[] = {1, 2, 3, 4, -1, 5, 6, -1, -1, 7, 8, -1, -1, -1, -1};
	head = reconTreeByLevel(values);
//	head = generateNode(1);
	printByLevel(head);

	return 0;

}
