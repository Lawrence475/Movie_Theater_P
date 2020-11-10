//Lawrence Wong 1001587603
/* ListLib For Coding Assignment 7 */
#include "ListLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// First parameter - Address of linked list head
// Second parameter - Ticket being added to linked list
void InsertNode(LNODE **LLH, char ticket[])
{
	LNODE *NewNode, *PrevPtr, *TempPtr;
	TempPtr = *LLH;
	while ((TempPtr != NULL) && strcmp(TempPtr->Ticket,ticket) < 0)
	{//while the LLH isn't null and when the value of the ticket is less than that of the one in the node
		PrevPtr = TempPtr;
		TempPtr = TempPtr->next_ptr;
	}
	NewNode = malloc(sizeof(LNODE));
	strcpy(NewNode->Ticket,ticket);
	NewNode->next_ptr = TempPtr;
	if (PrevPtr == NULL) //if the LL was empty then the NewNode is the head
	{
		*LLH = NewNode;
	}
	else //otherwise the NewNode becomes the LinkedListHead
	{
		PrevPtr->next_ptr = NewNode;
	}
}

// First parameter - Address of linked list head
// Second parameter - One ticket that has been taken off the linked list (node was freed) 
void ReturnAndFreeLinkedListNode(LNODE **LLH, char tickets[])
{
	LNODE *TempPtr;
	TempPtr = *LLH;
	strcpy(tickets,TempPtr->Ticket);
	*LLH = TempPtr->next_ptr;
	free(TempPtr);
}
