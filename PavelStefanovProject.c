#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 32
#define STEP 3
#define binArrSize 5

typedef struct Person
{
    char name[SIZE];
    int age;
}person;

typedef struct ArrInfo
{
	person* adress;
	int size;
}info;

void makeDynArr();
void printArr(int size,int whichArr);
void addMemory(int numOfArr,int j);
void printMenu();
void printEverything();
void addElement();
void removeElement();
void sortArr();
int presonalizeSorting();
void removeArray();
void addArrFromBinFile();

static info *arr;
static int sizeOfTheBigArr=0;

int main()
{
    int choise;
    int j;//Counter to free all arrays dynamic memory and printf arr sizes

    do
    {

       printf("Press (1) to make new array.\nPress (2) to add element in an array.\nPress (3) to print all elements.\n");
       printf("Press (4) to remove element.\nPress (5) to sort an array.\nPress (6) to remove an array.\n");
       printf("Press (7) to add array from struct in binary file.\nPress (0) for exit:\n");
        scanf("%d",&choise);
        switch(choise)
        {
            case 1:
            {
                makeDynArr();
                printf("There is(are)%d array(s)\n",sizeOfTheBigArr);
                break;
            }
            case 2:
            {
                addElement();
                break;
            }
            case 3:
            {
                printEverything();
                break;
            }
            case 4:
            {
                removeElement();
                break;
            }
            case 5:
            {
                sortArr();
                break;
            }
            case 6:
            {
                removeArray();
                break;
            }
            case 7:
                {
                    addArrFromBinFile();
                    break;
                }
        }

    } while(choise!=0);

    for(j=0;j<sizeOfTheBigArr;j++)
    {
    	printf("The size of arr[%d]-%d\n",j,arr[j].size);
    }

    for(j=0;j<sizeOfTheBigArr;j++)
    {
    	free(arr[j].adress);
    }
    free(arr);

	return 0;
}
void makeDynArr()
{
    int choise;
	int j=0;
    int numOfArr;

    sizeOfTheBigArr++;
	if(sizeOfTheBigArr==1)
	{
		arr=(info*)malloc(sizeof(info));
	}
	else
    {
        arr=(info*)realloc(&arr[0],sizeof(info)*sizeOfTheBigArr);
	}

	numOfArr=sizeOfTheBigArr-1;
    arr[numOfArr].adress=(person*)malloc(sizeof(person)*3);
	arr[numOfArr].size =0;

    do
    {
        printf("Enter name:\n");
        scanf("%s",arr[numOfArr].adress[arr[numOfArr].size].name);
        printf("Enter age:\n");
        scanf("%d",&arr[numOfArr].adress[arr[numOfArr].size].age);
        arr[numOfArr].size++;
        j++;
        printf("Press (1) to continue: \nPress (0) to exit:\n");
        scanf("%d",&choise);
        if(choise==1){
            if(j==3)
            {
               addMemory(numOfArr,arr[numOfArr].size);
               j=0;
            }
        }
    }while(choise!=0);

    printArr(arr[numOfArr].size,numOfArr);
}

void printArr(int size,int whichArr)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%s\t",arr[whichArr].adress[i].name);
        printf("%d\n",arr[whichArr].adress[i].age);
    }
}

void addMemory(int numOfArr,int j)
{
    arr[numOfArr].adress=(person*)realloc(arr[numOfArr].adress,sizeof(person)*(j+STEP));
}

void printEverything()
{
    if(sizeOfTheBigArr==0)
    {
        printf("There are still not arrays to print.\n");
        return;
    }
    int i;
    for(i=0;i<sizeOfTheBigArr;i++)
    {
        printf("\nArray %d: \n",i);
        printArr(arr[i].size,i);
    }
}
void addElement()
{
	int arrNumber;
	printf("In which arr you want to add element: \n");
    scanf("%d", &arrNumber);
    addMemory(arrNumber,arr[arrNumber].size-2);//pisha -2 za da dobavi pamet samo za edin element, zashtoto funkciqta addMemory dobavq 3.
    printf("Enter name:\n");
    scanf("%s",arr[arrNumber].adress[arr[arrNumber].size].name);
    printf("Enter age:\n");
    scanf("%d", &arr[arrNumber].adress[arr[arrNumber].size].age);
    arr[arrNumber].size++;
	printArr(arr[arrNumber].size,arrNumber);
}
void removeElement()
{
    int elementToRemove;
    int numOfArr;
    int i;

    printf("Enter in which array.\n");
    scanf("%d",&numOfArr);
    printf("Enter number of the element to remove.\n");
    scanf("%d",&elementToRemove);

    for(i=elementToRemove;i<arr[numOfArr].size-1;i++)
    {
        arr[numOfArr].adress[i]=arr[numOfArr].adress[i+1];
    }
    arr[numOfArr].size--;
    arr[numOfArr].adress=(person*)realloc(arr[numOfArr].adress,sizeof(person)*arr[numOfArr].size);
    printArr(arr[numOfArr].size,numOfArr);
}
int personalizeSorting()
{
	int choise;
	printf("If you want to sort by age press (1).\n");
	printf("If you want to sort by name press (2).\n");
	scanf("%d",&choise);
	return choise;

}
void sortArr()
{
	int numOfArr;
	printf("Which arr to sort,starting from (0): \n");
	scanf("%d",&numOfArr);
	person temp;

	int i;
	int j;
	int k=personalizeSorting();//the return of the function personalize sorting.

	for(j=0;j<arr[numOfArr].size-1;j++)
	{
		for(i=j+1;i<arr[numOfArr].size;i++)
		{
		    if(k==1)
            {
               if(arr[numOfArr].adress[j].age>arr[numOfArr].adress[i].age)
			{
				temp=arr[numOfArr].adress[j];
				arr[numOfArr].adress[j]=arr[numOfArr].adress[i];
				arr[numOfArr].adress[i]=temp;
			}
            }
            if(k==2)
            {
                if(strcmp(arr[numOfArr].adress[j].name,arr[numOfArr].adress[i].name)>1);
			{
				temp=arr[numOfArr].adress[j];
				arr[numOfArr].adress[j]=arr[numOfArr].adress[i];
				arr[numOfArr].adress[i]=temp;
			}
            }

		}
	}
	printArr(arr[numOfArr].size, numOfArr);
}

void removeArray()
{
	int choise;
	int i;

    if(sizeOfTheBigArr==0)
	{
		printf("There are no arrays to remove.\n");
		return;
	}
	printf("Which arr to remove: \n");
	printf("Enter number from 0 to %d\n",sizeOfTheBigArr-1);
	scanf("%d",&choise);
	free(arr[choise].adress);
	for(i=choise;i<sizeOfTheBigArr-1;i++)
	{
		arr[i]=arr[i+1];
	}
	sizeOfTheBigArr--;
	arr=(info*)realloc(arr,sizeof(info)*sizeOfTheBigArr);
}
void addArrFromBinFile()
{
    int numOfArr;
    sizeOfTheBigArr++;
    if(sizeOfTheBigArr==1)
    {
        arr=(info*)malloc(sizeof(info)*1);
    }
    else
    {
         arr=(info*)realloc(arr,sizeof(info)*sizeOfTheBigArr);
    }
    numOfArr=sizeOfTheBigArr-1;
    arr[numOfArr].adress=(person*)malloc(sizeof(person)*binArrSize);
    arr[numOfArr].size=binArrSize;
    FILE *fptr;
    fptr=fopen("C:/Users/hp/Desktop/binaryFileForTheProject/binaryFile.bin","rb");

    if(fptr!=NULL)
    {
        fread(arr[numOfArr].adress,sizeof(person),binArrSize,fptr);
    }
    else
    {
        printf("Error opening the binary file.\n");
        return;
    }
   printArr(binArrSize,numOfArr);
    fclose(fptr);


}
