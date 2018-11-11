#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int value;
	Node* left;
	Node* right;
	Node(int x) : value(x), left(NULL), right(NULL) {}
};


// 中序遍历
void morrisInOrder(Node* head) {
	if (NULL == head)
		return;
	Node* cur1 = head;
	Node* cur2 = NULL;
	while (NULL != cur1) {
		cur2 = cur1->left;
		if (NULL != cur2) {
			while (NULL != cur2->right && cur2->right != cur1) {
				cur2 = cur2->right;
			}
			if (cur2->right == NULL) {
				cur2->right = cur1;
				cur1 = cur1->left;
				continue;
			} else {
				cur2->right = NULL;
			}
		}
		
		cout << cur1->value << " ";
		cur1 = cur1->right;
	}	
	cout << endl;
}

// 先序遍历
void morrisPreOrder(Node* head) {
	if (NULL == head)
		return;
	Node* cur1 = head;
	Node* cur2 = NULL;
	while (NULL != cur1) {
		cur2 = cur1->left; // 左子树根结点
		if (NULL != cur2) {
			// 左子树不空，找到左子数的最右结点
			while (NULL != cur2->right && cur2->right != cur1) {
				cur2 = cur2->right;
			}
			if (NULL == cur2->right) {
				cur2->right = cur1;
				cout << cur1->value << " ";
				cur1 = cur1->left;
				continue;
			} else {
				cur2->right = NULL;
			}
		} else {
			cout << cur1->value << " ";
		}
		cur1 = cur1->right;
	}
	cout << endl;
}

// 后序遍历
Node* reverseEdge(Node* head) {
	Node *pre = NULL;
	Node *next = NULL;
	while (NULL != head) {
		next = head->right;
		head->right = pre;
		pre = head;
		head = next;
	}
	return pre;
}

void printEdge(Node *head) {
	Node* tail = reverseEdge(head);
	Node* cur = tail;
	while (NULL != cur) {
		cout << cur->value << " ";
		cur = cur->right;
	} 
	reverseEdge(tail);
}

void morrisPosOrder(Node* head) {
	if (NULL == head)
		return;
	Node *cur1 = head;
	Node *cur2 = NULL;

	while (NULL != cur1) {
		cur2 = cur1->left;
		if (NULL != cur2) {
			while (NULL != cur2->right && cur2->right != cur1) {
				cur2 = cur2->right;
			}
			if (NULL == cur2->right) {
				cur2->right = cur1;
				cur1 = cur1->left;
				continue;
			} else {
				cur2->right = NULL;
				printEdge(cur1->left);
			}
		}
		cur1 = cur1->right;
	}
	printEdge(head);
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
	int values[] = {4, 2, 6, 1, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1};
	Node* head = reconByLevel(values);
	morrisInOrder(head);
	morrisPreOrder(head);
	morrisPosOrder(head);
	return 0;
}
