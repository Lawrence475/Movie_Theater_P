//Lawrence Wong 1001587603
/* ListLib For Coding Assignment 7 */

#ifndef _LIST_LIB_H
#define _LIST_LIB_H

typedef struct LNODE
{
    char Ticket[3];
    struct LNODE *next_ptr;
} LNODE;

// First parameter - Address of linked list head
// Second parameter - Ticket being added to linked list
void InsertNode(LNODE **LLH, char ticket[]);

// First parameter - Address of linked list head
// Second parameter - One ticket that has been taken off the linked list (node was freed) 
void ReturnAndFreeLinkedListNode(LNODE **LLH, char tickets[]);

#endif
