#include <iostream>
using namespace std;


struct ListNode {
	int value;
	ListNode *next;
	ListNode(int x) : value(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode *head = new ListNode(0);	// 创建一个空结点作为头结点
	ListNode *p = l1, *q = l2, *cur = head;
	int carry = 0;	// 进位

	while (NULL != p || NULL != q) {
		int x = (NULL != p) ? p->value : 0;
		int y = (NULL != q) ? q->value : 0;
		int sum = x + y + carry;
		carry = sum / 10;
		cur->next = new ListNode(sum % 10);
		cur = cur->next;
		
		if (NULL != p)
			p = p->next;
		if (NULL != q)
			q = q->next;
	}

	if (carry > 0) 
		cur->next = new ListNode(carry);

	return head->next;
}
