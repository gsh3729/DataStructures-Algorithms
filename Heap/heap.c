/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : heap.c
	DATE : 23/1/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minHeapify(int array[],int *heapSize,int index);
void buildHeap(int array[],int *heapSize);
int deleteMin(int array[],int *heapSize);
void insert(int array[],int *heapSize,int newValue);
void swap(int *a,int *b);
void heapSort(int array[],int *heapSize);
void printArray(int array[],int *heapSize);
void printHeap(int array[],int heapSize);
void print_spaces(int spaces);

void main()
{
	int array[100],i,heapSize,newValue,option;

	printf(" Enter the number of elements: \n");
	scanf("%d",&heapSize);

	printf(" Enter the numbers :\n");

	for (i = 0; i < heapSize; i++)
	{
		scanf("%d",&array[i]);
	}

	buildHeap(array,&heapSize);

	while(option!=6)
	{
		printf("\n Menu\n 1.Insert\n 2.DeleteMin\n 3.Heapsort\n 4.printArray\n 5.PrintHeap\n 6.Exit");
		printf("\n..Enter the option :");
		scanf("%d",&option);
		if(option==1)
		{
			printf("..Enter the newValue you want to insert :");
			scanf("%d",&newValue);
			insert(array,&heapSize,newValue);
		}
		if(option==2)
		{
			if(heapSize!=0)
			{
				deleteMin(array,&heapSize);
			}
			else
			{
				printf("Cannot deleteMin since heapSize is 0\n");
			}
		}
		if(option==3)
		{
			heapSort(array,&heapSize);
			break;
		}
		if(option==4)
		{
			printArray(array,&heapSize);
			printf("\n");
		}
		if (option==5)
		{
			printHeap(array,heapSize);
		}
		if (option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6)
		{
			printf(" Please enter valid option\n");
		}
	}

// 	for ( i = 0; i < heapSize; ++i)
// 	{
// 		printf("%d ",array[i] );
// 	}
// 	printf("%d\n",deleteMin(array,&heapSize));
// 	for ( i = 0; i < heapSize; ++i)
// 	{
// 		printf("%d ",array[i] );
// 	}

// 	insert(array,&heapSize,0);
// printf("\n");
// 	for ( i = 0; i < heapSize; ++i)
// 	{
// 		printf("%d ",array[i] );
// 	}
// 	heapSort(array,&heapSize);

}
void printArray(int array[],int *heapSize)
{
	for (int i = 0; i <*heapSize; ++i)
	{
		printf("%d ",array[i] );
	}
}
void heapSort(int array[],int *heapSize)
{
	printf("Final sorted array is ");
	while(*heapSize!=0)
	{
		printf("%d ",deleteMin(array,heapSize));
	}
	printf("\n");
}
void minHeapify(int array[],int *heapSize,int index)
{
	int leftChild=2*index+1;
	int rightChild=2*index+2;
	int smallestIndex=index;

	if(array[leftChild]<array[smallestIndex] && leftChild<*heapSize)
	{
		smallestIndex=leftChild;
	}

	if(array[rightChild]<array[smallestIndex] && rightChild<*heapSize)
	{
		smallestIndex=rightChild;
	}

	if(smallestIndex!=index)
	{
		swap(&array[index],&array[smallestIndex]);
		minHeapify(array,heapSize,smallestIndex);
	}

}
void buildHeap(int array[],int *heapSize)
{
	for(int i=(*heapSize/2-1);i>=0;i--)
	{
		minHeapify(array,heapSize,i);
	}
}
int deleteMin(int array[],int *heapSize)
{
	int Min=array[0];
	array[0]=array[*heapSize-1];
	(*heapSize)--;
	int index=0;
	int smallestIndex=index;
	
	minHeapify(array,heapSize,0);
	return Min;
}
void insert(int array[],int *heapSize,int newValue)
{
	(*heapSize)++;
	array[*heapSize-1]=newValue;
	int index=*heapSize-1;
	while(index>0 && array[index]<array[(index-1)/2])
	{
		swap(&array[index],&array[(index-1)/2]);
		index=(index-1)/2;
	}
}
void print_spaces(int spaces)
{
    while(spaces>0)
    {
        printf(" ");
        spaces--;
    }
}
void printHeap(int array[],int heapSize)
{
    int counter = 64,i=0;
    int num_of_elements_in_level=1;						
    while(i<heapSize)
    {
        for(int j=0;j<num_of_elements_in_level && i<heapSize;j++)
        {										
            if(j==0)
            {
                print_spaces(counter);
                printf("%d",array[i]);
                i++;
            }
            else
            {
                print_spaces(2*counter);
                printf("%d",array[i]);
                i++;
            }
        }
        printf("\n\n");
        num_of_elements_in_level = num_of_elements_in_level*2;
        counter = counter /2;
    }

}


void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}