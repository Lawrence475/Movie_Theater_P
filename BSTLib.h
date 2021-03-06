//Lawrence Wong 1001587603
/* BSTLib For Coding Assignment 7 */

#ifndef _BST_LIB_H
#define _BST_LIB_H

typedef struct BNODE
{
    char MovieTheaterName[40];
    char ZipCode[6];
    char FileName[100];
    char Dimensions[6];	
    struct BNODE *left;
    struct BNODE *right;
} BNODE;

// First parameter - Address of BSTnode
// Second parameter - MovieTheaterName
// Third parameter - ZipCode
// Fourth parameter - FileName containing seat map (XXXOOOO)
// Fifth parameter - Dimensions of theater
void AddBSTNode(BNODE **Root, char TName[], char Zip[], char FName[], char Dimentions[]);

// First parameter - BST node
// Prints theater name and zip code
void InOrder(BNODE *);

// First parameter - BST node
// Second parameter - zipcode of movie theater being searched for
BNODE *SearchForBNODE(BNODE *, char []);



#endif
