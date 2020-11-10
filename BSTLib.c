//Lawrence Wong 1001587603
/* BSTLib For Coding Assignment 7 */
#include "BSTLib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

    //char MovieTheaterName[40];
    //char ZipCode[6];
    //char FileName[100];
    //char Dimensions[6];	
    //struct BNODE *left;
    //struct BNODE *right;

// First parameter - Address of BSTnode
// Second parameter - MovieTheaterName
// Third parameter - ZipCode
// Fourth parameter - FileName containing seat map (XXXOOOO)
// Fifth parameter - Dimensions of theater
void AddBSTNode(BNODE **Root, char TName[], char Zip[], char FName[], char Dimensions[]) //might need to change this as we're comparing the zip code as integers to atoi needed
{
	//making space and storing all the passed values into the NewNode
	BNODE *NewNode = malloc(sizeof(BNODE));
	strcpy(NewNode->ZipCode,Zip);
	strcpy(NewNode->FileName,FName);
	strcpy(NewNode->MovieTheaterName,TName);
	strcpy(NewNode->Dimensions,Dimensions);
	NewNode->left = NULL;
	NewNode->right = NULL;
	if(*Root == NULL)
	{
		*Root = NewNode;
	} 
	else if(strcmp((*Root)->ZipCode,NewNode->ZipCode) < 0) //will return a negative number if the first strings before the second
	{
		if((*Root)->right == NULL)
		{
			(*Root)->right = NewNode;
		}
		else
		{
			AddBSTNode(&(*Root)->right, TName, Zip, FName, Dimensions);
		}
	}
	else if(strcmp((*Root)->ZipCode,NewNode->ZipCode) > 0)
	{
		if((*Root)->left == NULL)//if empty then set the value equal to the NewNode
		{
			(*Root)->left = NewNode;
		}
		else //otherwise traverse the BST to the right and repeat
		{
			AddBSTNode(&(*Root)->left, TName, Zip, FName, Dimensions); 
		}
	}
	
}

// First parameter - BST node
void InOrder(BNODE *Root)
{ //traverse BST in the inorder sort
	//recursive function to go through the bst
	if(Root != NULL)
	{
		InOrder(Root->left);
		printf("%-30s\t%-5s\n", Root->MovieTheaterName, Root->ZipCode); //%-30 is for spacing purposes
		InOrder(Root->right);
	}
}

// First parameter - BST node
// Second parameter - zipcode of movie theater being searched for
BNODE *SearchForBNODE(BNODE *Root, char ZipCode[])
{
	BNODE *Found = NULL;
	if(Root == NULL)
	{
		return Found;
	}
	
	if(strcmp(Root->ZipCode,ZipCode) == 0)
	{
		Found = Root;
	}
	else if(strcmp(Root->ZipCode,ZipCode) < 0) //will return a negative number if the first strings before the second
	{
		Found = SearchForBNODE(Root->right, ZipCode);
	}
	else if(strcmp(Root->ZipCode,ZipCode) > 0)
	{
		Found = SearchForBNODE(Root->left,ZipCode); 
	}

	return Found; //returns the BNODE location of where the node was found
}
