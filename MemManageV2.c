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
void Analyze(void);
void memAlloc(int **);
void memFree(int **);
void clearScreen(void);

//global variables
FILE *fp;                //file pointer
char ch;                 //dummy used in clear screen
int *ptrA,*ptrB,*ptrC;   //demo pointers
unsigned memA,memB,memC; //allocated memory blocks
unsigned totalMemoryAlloc;   //total memory allocated

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

    fputs("                   Memory Allocation Details                  \n",fp);
    fputs(" _____________________________________________________________\n",fp);
    fputs("|                                                             |\n",fp);
    fputs("|Pointer Address | Memory Location | Blocks Allocated | Status|\n",fp);
    fputs(" ------------------------------------------------------------- \n",fp);

    fclose(fp);

	while(1)
	{
	    //main menu
		printf("\n");
		//printf("   Mem Alocated -> %d Bytes      \n",totalMemoryAlloc);
		printf(" _______________________________ \n");
		printf("|                               |\n");
		printf("|  1. Allocate Some memory      |\n");
		printf("|  2. Free Some memory          |\n");
		printf("|  3. Analyze                   |\n");
		printf("|  4. Exit                      |\n");
		printf("|_______________________________|\n");
	l1:	printf("\nEnter your choice -> ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				Alloc();
				clearScreen();
				break;
			case 2:
				Free();
				clearScreen();
				break;
            case 3:
                Analyze();
                clearScreen();
                break;
			case 4:
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

//this function analyze the memory allocation of all pointers
void Analyze(void)
{
    printf("\nAnalyzing...\n");
    if(totalMemoryAlloc != 0)
    {
        printf("Following Pointers Are Not Released \n");

        if(ptrA != NULL){
            printf("ptrA holds -> %d Bytes\n",&ptrA,memA);
        }
        if(ptrB != NULL)
        {
            printf("ptrB holds -> %d Bytes\n",&ptrB,memB);
        }
        if(ptrC != NULL)
        {
            printf("ptrC holds -> %d Bytes\n",&ptrC,memC);
        }

        printf("Total Memory Not Free -> %d Bytes\n",totalMemoryAlloc);
    }else
    {
        printf("Total Memory is Free.\n");
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
        printf("Memory allocated to ptrA -> %d Bytes\n",memblock);
    }
	else if(ptr == &ptrB)
    {
        memB = memblock*sizeof(int);
        printf("Memory allocated to ptrB -> %d Bytes\n",memblock);
    }
	else if(ptr == &ptrC)
    {
        memC = memblock*sizeof(int);
        printf("Memory allocated to ptrC -> %d Bytes\n",memblock);
    }



	totalMemoryAlloc = totalMemoryAlloc + memblock*sizeof(int);

	//log file handling for allocated memory
	sprintf(str,"    \t%d\t\t\t%d\t\t\t\t%d\t\t\t\tU\n",ptr,*ptr,memblock);
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
        sprintf(str,"    \t%d\t\t\t\t\t\t\t%d\t\t\tF\n",ptr,memA);
        totalMemoryAlloc -= memA*2;
    }
	else if(ptr == &ptrB)
    {
        printf("Memory freed of ptrB -> %d Byte\n",memB);
        sprintf(str,"   %d\t\t\t%d\t\t\tF\n",*ptr,memB);
        totalMemoryAlloc -= memB*2;
    }
	else if(ptr == &ptrC)
    {
        printf("Memory freed of ptrC -> %d Byte\n",memC);
        sprintf(str,"   %d\t\t\t%d\t\t\tF\n",*ptr,memC);
        totalMemoryAlloc -= memC*2;
    }

    free(*ptr);
    *ptr = NULL;

    //log file handling for deallocated memory
	fp = fopen(FILENAME,"a");
	fputs(str,fp);
	fclose(fp);
}

void clearScreen(void)
{
    printf("Press Enter to continue -> ");
    scanf("%c",&ch);
    scanf("%c",&ch);
    //system("clear");
    system("CLS");
}
