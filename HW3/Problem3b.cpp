#include "ListNode.h"
#include <algorithm>
using namespace std;

DListNode* twowayBubble(DListNode* head) {

	//to track the size and # of passes made
	int size = 0;
	int passes = 0;

	//to track current node
	DListNode *current = head;

	//find the length of the list
	while (current->next != NULL)
	{
		size +=1;
		current = current->next;
	}

	//reset current node to beginning
	current = head;

	//while the number of passes < half the size +1 (in case size is odd)
	while (passes < (size/2 +1))
	{
		//loop forward until the end
		while (current->next != NULL)
		{
			//if the next value is > then current value, swap
			if(current->val > current->next->val)
				{
					swap (current->val, current->next->val);
				}
			//move to next node
			current = current->next;
		}
		//loop back to the beginning
		while (current->prev != NULL)
		{
			//if the current value is less than the previous value, swap
			if(current->val < current->prev->val)
				{
					swap (current->val, current->prev->val);
				}
			//move to the previous node
			current = current->prev;
		}
		//increment passes by 1
		passes +=1;
	}

	return head;
}