//Collaborated with Liron Dubin


#include <iostream>
#include "ListNode.h"
// your includes here
using namespace std;

DListNode* twowayBubble(DListNode* head) {

	// your implementation goes here
	DListNode* tail;
	DListNode* itr;
	while (itr != NULL)
	{
		tail = itr;
		itr = itr -> next;
	}
	
	while (head != NULL && tail != NULL)
	{
		int tempHead;
    	if ( (head -> val) > (head ->next ->val) ) 
    	{
    		 tempHead = head -> next -> val;
    	
    		head -> next -> val = head -> val;
    		head -> val = tempHead;
    		head = head -> next;
    	}
    	else 
    	{
    		head = head ->next; //already in order 
    	}

    
    		//do the same thing for tail and prev
    	int tempTail;
    	if ( (tail -> val) < (tail -> next -> val) )
    		{
    			tempTail = tail -> prev -> val;
    			tail -> prev ->val = tail -> val;
    			tail -> val = tempTail; 
    			tail = tail -> prev;
    		}
    	
    	else 
    		{
    			tail = tail -> prev;
    		}
	
	}


	return tail;; // don't forget to change this
}

/*
int main()
{




	return 0;
}
*/