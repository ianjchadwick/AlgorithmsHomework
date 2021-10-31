#include "ListNode.h"
#include <algorithm>
using namespace std;

//got hint/help from geeksforgeeks at https://www.geeksforgeeks.org/linked-list-in-zig-zag-fashion/

SListNode* zigzagSort(SListNode* head) {

	//set up a flag variable to toggle back and forth
	int flag = true;
	
	/*int temp = 0; intially tried to use a temp variable to swap instead of swap function, 
	but it wouldn't work so I changed it to swap lines 23 and 29*/
	
	
	//set a variable to track our current node
	SListNode* current = head;

	//loop through the linked list until we're at the end
	while (current->next != NULL)
	{
		if(flag) //if we're expecting the < relationship
		{
			if ((current->val >= current->next->val))
				//swap the values if the current value is > the next one
				swap(current->val, current->next->val);
		}
		else //if we're expecting > relationship
		{
			if ((current->val <= current->next->val))
				//swap the values if the current value is < the next one
				swap(current->val, current->next->val);
		}

		//move to the next node
		current = current->next;
		//toggle the flag
		flag = !(flag);
	}
	return head;
}