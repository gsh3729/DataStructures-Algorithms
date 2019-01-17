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

void minHeapify(int array[],int index);
void buildHeap(int array[]);
int deleteMin(int array[]);
void insert(int array[],int newValue);
void swap(int *a,int *b);
void heapSort(int array[]);
void printArray(int array[]);
void printHeap(int array[]);
void print_spaces(int spaces);
int digits(int num);
void print_spaces(int spaces);
int heapSize;

void main()
{
	int array[100],i,newValue,option;

	printf(" Enter the number of elements: \n");
	scanf("%d",&heapSize);

	printf(" Enter the numbers :\n");

	for (i = 0; i < heapSize; i++)
	{
		scanf("%d",&array[i]);
	}

	buildHeap(array);

	while(option!=6)
	{
		printf("\n Menu\n 1.Insert\n 2.DeleteMin\n 3.Heapsort\n 4.printArray\n 5.PrintHeap\n 6.Exit");
		printf("\n..Enter the option :");
		scanf("%d",&option);
		if(option==1)
		{
			printf("..Enter the newValue you want to insert :");
			scanf("%d",&newValue);
			insert(array,newValue);
		}
		if(option==2)
		{
			if(heapSize!=0)
			{
				deleteMin(array);
			}
			else
			{
				printf("Cannot deleteMin since heapSize is 0\n");
			}
		}
		if(option==3)
		{
			heapSort(array);
			break;
		}
		if(option==4)
		{
			printArray(array);
			printf("\n");
		}
		if (option==5)
		{
			printHeap(array);
		}
		if (option!=1 && option!=2 && option!=3 && option!=4 && option!=5 && option!=6)
		{
			printf(" Please enter valid option\n");
		}
	}


}
void printArray(int array[])
{
	for (int i = 0; i <heapSize; ++i)
	{
		printf("%d ",array[i] );
	}
}
void heapSort(int array[])
{
	printf("Final sorted array is ");
	while(heapSize!=0)
	{
		printf("%d ",deleteMin(array));
	}
	printf("\n");
}
void minHeapify(int array[],int index)
{
	int leftChild=2*index+1;
	int rightChild=2*index+2;
	int smallestIndex=index;

	if(array[leftChild]<array[smallestIndex] && leftChild<heapSize)
	{
		smallestIndex=leftChild;
	}

	if(array[rightChild]<array[smallestIndex] && rightChild<heapSize)
	{
		smallestIndex=rightChild;
	}

	if(smallestIndex!=index)
	{
		swap(&array[index],&array[smallestIndex]);
		minHeapify(array,smallestIndex);
	}

}
void buildHeap(int array[])
{
	for(int i=(heapSize/2-1);i>=0;i--)
	{
		minHeapify(array,i);
	}
}
int deleteMin(int array[])
{
	int Min=array[0];
	array[0]=array[heapSize-1];
	(heapSize)--;
	
	minHeapify(array,0);

	return Min;
}
void printHeap(int array[])
{
    int counter = 64,i=0;
    int num_of_elements_in_level=1;						
    while(i<heapSize)
    {
        for(int j=0;j<num_of_elements_in_level && i<heapSize;j++)
        {										
            if(j==0)
            {
                print_spaces(counter-digits(array[i]));
                printf("%d",array[i]);
                i++;
            }
            else
            {
                print_spaces(2*counter-digits(array[i]));
                printf("%d",array[i]);
                i++;
            }
        }
        printf("\n\n\n");
        num_of_elements_in_level = num_of_elements_in_level*2;
        counter = counter /2;
    }
}
int digits(int num)
{
	int i=1;
	while(1)
	{
		num=num/10;
		if(num==0)
		{
			break;
		}
		i++;
	}
	return i;
}
void print_spaces(int spaces)
{
    while(spaces>0)
    {
        printf(" ");
        spaces--;
    }
}
void insert(int array[],int newValue)
{
	(heapSize)++;
	array[heapSize-1]=newValue;
	int index=heapSize-1;
	while(index>0 && array[index]<array[(index-1)/2])
	{
		swap(&array[index],&array[(index-1)/2]);
		index=(index-1)/2;
	}
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
