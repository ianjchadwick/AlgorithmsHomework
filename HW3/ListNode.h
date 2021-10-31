#ifndef _LISTNODE
#include <cstddef>
#define _LISTNODE

struct SListNode {
	int val;
	SListNode *next;
	SListNode(int x) : val(x), next(NULL) {}
};

struct DListNode {
	int val;
	DListNode *prev;
	DListNode *next;
	DListNode(int x) : val(x), prev(NULL), next(NULL) {}
};

#endif
