//Lawrence Wong 1001587603
#include "QueueLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// First parameter - Customer's name
// Second parameter - Address of QueueHead
// Third parameter - Address of QueueTail
void enQueue(char name[], QNODE **Head, QNODE **Tail)
{
	QNODE *NewNode = malloc(sizeof(QNODE));
	strcpy(NewNode->Name,name);
	NewNode->next_ptr = NULL;
	if(*Head == NULL)
	{
		*Head = *Tail = NewNode;
	}
	else
	{
		(*Tail)->next_ptr = NewNode;
		*Tail = NewNode;
	}	
}
// First parameter - Address of QueueHead
void deQueue(QNODE **Head)
{
	QNODE *TempPtr = *Head;
	if(*Head == NULL)
	{
		printf("Queue is empty");
	}
	else
	{
		free(*Head);
		*Head = TempPtr->next_ptr;
	}	
	
}
// First parameter - QueueHead 
void DisplayQueue(QNODE *Head)
{
	QNODE *TempPtr = Head;
	while(TempPtr != NULL)
	{
		printf("%s",TempPtr->Name);
		TempPtr = TempPtr->next_ptr;
	}
}
