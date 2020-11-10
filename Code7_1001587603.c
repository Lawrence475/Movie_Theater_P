//Lawrence Wong 1001587603 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueLib.h"
#include "BSTLib.h"
#include "ListLib.h"
#include "StackLib.h"
#define MAX 1000
#define ROW 26
#define COLUMN 20
void PrintSeatMap(int Row, int Column, char SeatMapDisplay[][COLUMN], char OpenSeats[], char Alpha[])//function to printout seat map
{
	int i,j,k,l;
	i = 0;
	for(j = 0; j < Row; j++) //nested for loop to store values into 2d array
	{
		for(k = 0; k < Column; k++)
		{
			SeatMapDisplay[j][k] = OpenSeats[i++]; //setting the array equal to the string at index i
		}
	}
	for(j = 0; j <Column; j++)
	{
		printf("\tSeat%d",j+1);
	}
	printf("\n");
	for(j = 0; j < Row; j++) //nested for loop to printout the seat map
	{
		printf("Row %c\t",Alpha[j]);
		for(k = 0; k < Column; k++)
		{
			printf("%-5c\t", SeatMapDisplay[j][k]);
		}
		printf("\n");
	}
	printf("\n");
}
int get_command_line_parameter(char *argv[], char ParamName[], char ParamValue[]) //function to get the parameters for the names of the files
{
	int found = 0;
	int i = 0;
	while (argv[++i] != NULL)
	{
		if (!strncmp(argv[i], ParamName, strlen(ParamName)))
		{	
			strcpy(ParamValue, strchr(argv[i], '=') + 1);
			found = 1;
		}
	}
	return found;
}
int main(int argc, char *argv[])
{
	char Queue[MAX];
	char Zip[MAX];
	char RNum[MAX];
	int RNumber;
	int i;
	SNODE *StackT = NULL;
	/* Read command line parameters */
	if(get_command_line_parameter(argv,"QUEUE",Queue) == 0)
	{
		printf("error no queue\n");
		exit(0);
	}
	if(get_command_line_parameter(argv,"ZIPFILE",Zip) == 0)
	{
		printf("error no zipfile\n");
		exit(0);
	}
	if(get_command_line_parameter(argv,"RECEIPTNUMBER",RNum) == 0)
	{
		printf("error no number\n");
		exit(0);
	}
	RNumber = atoi(RNum); //converting the receipt number into an int
	printf("%s,%s,%d\n", Queue, Zip, RNumber);
	
	
	
	//Read queue file
	QNODE *QHead = NULL;
	QNODE *QTail = NULL;
	FILE *QFILE;
	QFILE = fopen(Queue, "r");
	char line[MAX];
	while(fgets(line, MAX, QFILE) != NULL) //while loop to go through all elements
	{
		if(ferror(QFILE))
		{
			perror("Error reading file");
			exit(0);
		}
		else
		{	
			enQueue(line, &QHead, &QTail);
		}
	}
	
	//Read the Theater file
	BNODE *Root = NULL;
	FILE *Zipfiles;
	Zipfiles = fopen(Zip, "r");
	char MTname[MAX];
	char Zcode[MAX];
	char Fname[MAX];
	char Dimen[MAX];
	while(fgets(line, MAX, Zipfiles) != NULL) //while loop to go through all elements
	{
		if(ferror(Zipfiles))
		{
			perror("Error reading file");
			exit(0);
		}
		else
		{	
			char *word;
			char delim[] = {'|', '\n', '\0'}; //setting an array for the token
			word = strtok(line, delim);
			strcpy(MTname, word);
			word = strtok(NULL, delim);
			strcpy(Zcode, word);
			word = strtok(NULL, delim); 
			strcpy(Fname, word);
			word = strtok(NULL, delim);
			strcpy(Dimen, word);
			AddBSTNode(&Root,MTname,Zcode,Fname,Dimen);
		}
	}	
	LNODE *LLH;
	int choice, ticketcount;
	int true = 1;
	char UserZip[6];
	BNODE *UserNode;
	FILE *SMap, *NewSMap;
	char Seats[MAX], SeatDimen[MAX], SeatRowString[MAX], SeatColumnString[MAX], UserSeatChoice[MAX];
	int SeatRow, SeatColumn, SeatsLength, NewSeatRow, NewSeatColumn;
	char SeatMap[ROW][COLUMN];
	//variables for printout of the seat map
	char Alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char SeatRowCharacter;
	char blank[MAX];
	while(QHead != NULL) //fix this, needs to end when the queue is empty
	{
		LLH = NULL; 
		printf("1.\tSell tickets to next customer\n\n");
		printf("2.\tSee who's next in line\n\n");
		printf("3.\tSee the seat map for a given theater\n\n");
		printf("4.\tPrint today's receipts\n\n");
		printf("Choice: ");
		scanf(" %d",&choice);
		if(choice == 1)
		{
			char CustName[MAX];
			strcpy(CustName,QHead->Name); //copying the name of the customer from the queue head
			printf("\nHello, %s\n", CustName);
			InOrder(Root); // calling function to print out the theater inorder
			printf("\n"); 
			printf("Enter zip code to select theater: ");
			scanf("%s", UserZip); //taking the zip input from the function
			printf("\n");
			UserNode = SearchForBNODE(Root ,UserZip); //calling search function to find the zip code that the user entered
			if(UserNode == NULL){} //if the UserNode is null then that means that there was no zip code that the user entered
			else 
			{
				SMap = fopen(UserNode->FileName, "r"); //opening the file that's in the file
				if(SMap == NULL)
				{
					printf("Error : Seat map is empty\n");
				}
				else
				{
					int j,k,l,z = 0; //variables for the nested for loop
					char *token;
					char delimiters[] = {'x'};
					strcpy(SeatDimen,UserNode->Dimensions); //copying dimentions to the SeatDimen
					token = strtok(SeatDimen, delimiters); //tokening the string and spliting them into the two strings holding the row and column strings
					strcpy(SeatRowString, token);
					token = strtok(NULL, delimiters);
					strcpy(SeatColumnString, token);
					SeatRow = atoi(SeatRowString); //converting string into integers
					SeatColumn = atoi(SeatColumnString);
					fgets(Seats, MAX-1,SMap); //storing what's inside the file inside the Seats array
					if(strlen(Seats) > (SeatColumn*SeatRow))
					{
						printf("Error: Seat Map dimensions don't aline, please select another theater\n");
					}
					else
					{
						fclose(SMap);
						i = 0;
						for(j = 0; j < SeatRow; j++) //nested for loop to store values into 2d array
						{
							for(k = 0; k < SeatColumn; k++)
							{
								SeatMap[j][k] = Seats[i++]; //setting the array equal to the string at index i
							}
						}
						for(j = 0; j <SeatColumn; j++)
						{
							printf("\tSeat%d",j+1);
						}
						printf("\n");
						for(j = 0; j < SeatRow; j++) //nested for loop to printout the seat map
						{
							printf("Row %c\t",Alphabet[j]);
							for(k = 0; k < SeatColumn; k++)
							{
								printf("%-5c\t", SeatMap[j][k]);
							}
							printf("\n");
						}
						printf("\nHow many movie tickets would you like to buy? ");
						scanf(" %d", &ticketcount);
						printf("\n");
						for(j = 0; j <SeatColumn; j++)
							{
								printf("\tSeat%d",j+1);
							}
							printf("\n");
							for(j = 0; j < SeatRow; j++) //nested for loop to printout the seat map
							{
								printf("Row %c\t",Alphabet[j]);
								for(k = 0; k < SeatColumn; k++)
								{
									printf("%-5c\t", SeatMap[j][k]);
								}
								printf("\n");
							}
						for(z = 0; z<ticketcount; z++) //loop to get all the tickets sold 
						{
							printf("Pick a seat (Row seat) ");
							scanf("%s", UserSeatChoice); //getting input of the user seat
							UserSeatChoice[0] = toupper(UserSeatChoice[0]); //making it uppercase
							int slen = strlen(UserSeatChoice);
							if(slen < 3) //if the length is less than three then it's "a1" and then it will uppercase the input
							{
								strncpy(SeatRowString,UserSeatChoice,1);
								strcpy(SeatColumnString,UserSeatChoice+1);
								
							}
							else
							{
								strncpy(SeatRowString,UserSeatChoice,1);
								strcpy(SeatColumnString,UserSeatChoice+1);
							}
							strcat(SeatRowString,SeatColumnString); //concatinating the two strings
							InsertNode(&LLH, UserSeatChoice);
							NewSeatRow = NewSeatColumn = 0; //reseting values of the variables
							SeatRowCharacter = SeatRowString[0]; //changing the string into a character
							NewSeatRow = SeatRowCharacter - 'A'; //subtracting A from the variable to get the numberical value of the row number
							NewSeatColumn = atoi(SeatColumnString); //converting value of the string into an integer
							if(SeatMap[NewSeatRow][NewSeatColumn-1] == 'X')
							{
								printf("That seat is already sold! Try again.\n");
								--z; //decreasing z by one to reset the count 
							}
							else
							{
								SeatMap[NewSeatRow][NewSeatColumn-1] = 'X'; //setting the seat to X
							}
							for(j = 0; j <SeatColumn; j++)
							{
								printf("\tSeat%d",j+1);
							}
							printf("\n");
							for(j = 0; j < SeatRow; j++) //nested for loop to printout the seat map
							{
								printf("Row %c\t",Alphabet[j]);
								for(k = 0; k < SeatColumn; k++)
								{
									printf("%-5c\t", SeatMap[j][k]);
								}
								printf("\n");
							}
						}
						int NAMElength = strlen(CustName);
						NAMElength = NAMElength-2;
						int Start;
						printf("\nThank you "); //printing out an extra next line for the name 
						for(Start = 0; Start < NAMElength; Start++)
						{
							printf("%c",CustName[Start]);
						}
						printf(" - enjoy your movie!\n");
						NewSMap = fopen(UserNode->FileName, "w+"); //reopening filename to update information
						for(j = 0; j < SeatRow; j++) //nested for loop to printout the seat map
						{
							for(k = 0; k < SeatColumn; k++)
							{
								fprintf(NewSMap,"%c",SeatMap[j][k]); //fprintf to move info into the file
							}
						}
						fclose(NewSMap);
						push(&StackT,LLH,RNumber,UserNode->MovieTheaterName); //adding the ticket to the stack
						deQueue(&QHead);//dequeue to remove customer
						RNumber++; //incrementing the receipt number to make sure the printout is correct
					}
				}
			}
			printf("\n");
		}
		else if(choice == 2)
		{
			printf("Customer Queue\n");
			DisplayQueue(QHead); //printing out the queue
			printf("\n");
		}
		else if(choice == 3)
		{
			UserNode = NULL; //reseting the values of the variables
			InOrder(Root); // calling function to print out the theater inorder
			printf("\n"); 
			printf("Enter zip code to select theater: ");
			scanf("%s", UserZip); //taking the zip input from the function
			printf("\n");
			UserNode = SearchForBNODE(Root ,UserZip);
			
			char *token;
			char delimiters[] = {'x'};
			strcpy(SeatDimen,UserNode->Dimensions); //copying dimentions to the SeatDimen
			token = strtok(SeatDimen, delimiters); //tokening the string and spliting them into the two strings holding the row and column strings
			strcpy(SeatRowString, token);
			token = strtok(NULL, delimiters);
			strcpy(SeatColumnString, token);
			SeatRow = atoi(SeatRowString); //converting string into integers
			SeatColumn = atoi(SeatColumnString);
			SMap = fopen(UserNode->FileName, "r");
			fgets(Seats, MAX-1, SMap);
			fclose(SMap);
			PrintSeatMap(SeatRow, SeatColumn, SeatMap, Seats, Alphabet); //function to printout the seat map
			
		}	
		else if(choice == 4)
		{
			if(StackT == NULL)
			{
				printf("There are no receipts\n\n");
			}
			else
			{
				printf("Today's receipts\n");
				while(StackT != NULL && StackT->TicketList != NULL)
				{
//while the stacktop is not null AND if the ticketlist is not null then execute
//we check if the Stack is empty first since if it is then there's no need to go into the ticketlist					
					printf("Receipt #%d\n\t%s\n\t",StackT->ReceiptNumber, StackT->MovieTheaterName);
					while((StackT->TicketList)->Ticket != NULL)
					{//while loop to go through the linked list to print out all the tickets
						ReturnAndFreeLinkedListNode(&StackT->TicketList,blank);
						printf("%s ",blank); //printout for the ticket
						strcpy(blank,"");
					}
					pop(&StackT);
					printf("\n");
					//RNumber++; //increment the receiptnumber
				}
				printf("\n");
			}
		}
	}
	printf("Good job - you sold tickets to all of the customers in line.\n"); //Code for printing out all the remaining receipts
	printf("Today's receipts\n");
	while(StackT != NULL && StackT->TicketList != NULL)
	{
		printf("Receipt #%d\n\t%s\n\t",StackT->ReceiptNumber, StackT->MovieTheaterName);
		while((StackT->TicketList)->Ticket != NULL)
		{//while loop to go through the linked list to print out all the tickets
			ReturnAndFreeLinkedListNode(&StackT->TicketList,blank);
			printf("%s ",blank); //printout for the ticket
			strcpy(blank,"");
		}
		pop(&StackT);
		printf("\n");
	}	
	return 0;
}
