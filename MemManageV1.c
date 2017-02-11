/*
    Allocation and logging of memory details.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "MemoryDetails.txt"

//function prototypes
void Alloc(void);
void Free(void);
void memAlloc(int **);
void memFree(int **);

//global variables
FILE *fp;                //file pointer
int *ptrA,*ptrB,*ptrC;   //demo pointers
unsigned memA,memB,memC; //allocated memory blocks
unsigned memory_alloc;   //total memory allocated

int main()
{
    int choice;

    //opening and initializing file
    fp = fopen(FILENAME,"w+");

    if(fp == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }

    fputs("         Memory Details              \n",fp);
    fputs(" ____________________________________\n",fp);
    fputs("|                                    |\n",fp);
    fputs("|Location | Blocks Allocated | Status|\n",fp);
    fputs(" ------------------------------------ \n",fp);

    fclose(fp);

	while(1)
	{
	    //main menu
		printf("\n");
		printf("   Mem Alocated -> %d Bytes      \n",memory_alloc);
		printf("|-------------------------------|\n");
		printf("|  1. Allocate Some memory      |\n");
		printf("|  2. Free Some memory          |\n");
		printf("|  3. Exit                      |\n");
		printf("|_______________________________|\n");
	l1:	printf("\nEnter your choice -> ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				Alloc();
				break;
			case 2:
				Free();
				break;
			case 3:
				return 0;
			default:
				printf("Please enter correct choice\n");
				goto l1;
		}
	}

    return 0;
}

//function to choose which pointer you wanted to allocate memory
void Alloc(void)
{
	int choice;

	printf(" _______________________________\n");
	printf("|                               |\n");
	printf("|  1. Allocate memory to ptrA   |\n");
	printf("|  2. Allocate memory to ptrB   |\n");
	printf("|  3. Allocate memory to ptrC   |\n");
	printf("|_______________________________|\n");
l2: printf("\nEnter your choice -> ");
	scanf("%d",&choice);

	switch (choice)
	{
		case 1:
			memAlloc(&ptrA);
			break;
		case 2:
			memAlloc(&ptrB);
			break;
		case 3:
			memAlloc(&ptrC);
			break;
		default:
			printf("Please enter correct choice\n");
			goto l2;
	}
}

//function to choose which location to be freed
void Free(void)
{
	int choice;

	printf(" _______________________________\n");
	printf("|                               |\n");
	printf("|  1. Free memory of ptrA       |\n");
	printf("|  2. Free memory of ptrB       |\n");
	printf("|  3. Free memory of ptrC       |\n");
	printf("|_______________________________|\n");
l3:	printf("\nEnter your choice -> ");
	scanf("%d",&choice);

	switch (choice)
	{
		case 1:
			memFree(&ptrA);
			break;
		case 2:
			memFree(&ptrB);
			break;
		case 3:
			memFree(&ptrC);
			break;
		default:
			printf("Please enter correct choice\n");
			goto l3;
	}
}

//function allocate memory
void memAlloc(int **ptr)
{
    char str[100];
	unsigned memblock = 0;

    if(*ptr!=NULL)
    {
        printf("Already allocated\n");
        return;
    }

	printf("Enter the number of memory block you want's to allocate\n");
	scanf("%d",&memblock);

    *ptr = (int*) malloc(memblock * sizeof(int));  //memory allocated using malloc

    if(*ptr== NULL)
    {
        printf("Error! memory not allocated.");
        return;
    }

	if(ptr == &ptrA)
    {
        memA = memblock*sizeof(int);
        printf("Memory allocated to ptrA -> %d Byte\n",memA);
    }
	else if(ptr == &ptrB)
    {
        memB = memblock*sizeof(int);
        printf("Memory allocated to ptrB -> %d Byte\n",memB);
    }
	else if(ptr == &ptrC)
    {
        memC = memblock*sizeof(int);
        printf("Memory allocated to ptrC -> %d Byte\n",memC);
    }

	memory_alloc = memory_alloc + memblock*sizeof(int);

	//log file handling for allocated memory
	sprintf(str,"   %d\t\t\t%d\t\t\tU\n",*ptr,memblock*(sizeof(int)));
	fp = fopen(FILENAME,"a");
	fputs(str,fp);
	fclose(fp);
}

//function deallocate memory
void memFree(int **ptr)
{
    char str[100];

    if(*ptr == NULL)
    {
        printf("Memory already free\n");
        return;
    }

    if(ptr == &ptrA)
    {
        printf("Memory freed of ptrA -> %d Byte\n",memA);
        sprintf(str,"   %d\t\t\t%d\t\t\tF\n",*ptr,memA);
        memory_alloc -= memA;
    }
	else if(ptr == &ptrB)
    {
        printf("Memory freed of ptrB -> %d Byte\n",memB);
        sprintf(str,"   %d\t\t\t%d\t\t\tF\n",*ptr,memB);
        memory_alloc -= memB;
    }
	else if(ptr == &ptrC)
    {
        printf("Memory freed of ptrC -> %d Byte\n",memC);
        sprintf(str,"   %d\t\t\t%d\t\t\tF\n",*ptr,memC);
        memory_alloc -= memC;
    }

    free(*ptr);
    *ptr = NULL;

    //log file handling for deallocated memory
	fp = fopen(FILENAME,"a");
	fputs(str,fp);
	fclose(fp);
}
