/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION :
	PROGRAM NAME : dfs.c
	DATE : 2/1/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>








void main()
{
	int n,start,count=0;
	char filename[30];

	printf("\n..Enter the input graph:");
	scanf("%s",filename);

	FILE *p;
	p=fopen(filename,"r");

	if(p==0)
	{
		printf("\n..Error in opening the file");
		exit();
	}

	fscanf(p,"%d",)

	
	mergesort();
}
void mergesort()
{
	merge();
}
void merge()
{

}
void merge(int a[],int n1,int n2)
{
	int i=0,j=0,k=0;
	while(i<n1 && j<n2) 
	{
		if(left[i] <= right[j])
		{
			a[k]=left[i]; 
			k++;
			i++;
		}
		else
		{
			a[k]=right[j];
			k++;
			j++;
		}
	}
	while(i<n1) 
	{
		a[k]=left[i];
		k++;
		i++;
	}
	while(j<n2) 
	{
		a[k]=right[j];
		k++;
		j++;
	}
}
// 		while(1)
// 		{
// 			fscanf(p,"%d",&temp);
// 			if(temp!=-1)
// 			{
// 				struct node *temp;
// 				temp->data=(node)malloc(sizeof(node));
// 				temp->next=NULL;
// 			}
// 			else
// 			{
// 				break;
// 			}
// 	}
// 	DepthFirstSearch(vertexPointer,n,start,visited,count)
// }

// void DepthFirstSearch(int *vertexPointer[],int n,int start,int visited[n],int count)
// {
// 	int j;
// 	visited[start]=1;
// 	count++;
// 	pre[start]=count;                                                                                                                                                                                                                    
// 	{
// 		if(visited[head->data]==0)
// 		{
			
// 			b[start][j]='r';
// 			b[j][start]='r';
// 			DepthFirstSearch(a,n,b,j,visited);
// 		}
// 	}
// }


// #include "stack.h"
// #include "readWrite.h"

// int DepthFirstSearch(char a[100][100],int n,int n1,int parent[],char b[n][n]);
// void copyMatrix(char a[100][100],int n,char b[n][n],int parent[n],int start);

// void main()
// {



// 	char a[100][100];
// 	int n,start,i=0,j=0;
	
// 	n=readmatrix(a); //function to read adjacent matrix from the input file
// 	char b[n][n];
// 	int parent[n];

// 	for(i=0;i<n;i++)
// 	{
// 		for(j=0;j<n;j++)
// 		{
// 			b[i][j]=a[i][j];
// 		}
// 	}
// 	printf("\n Enter the starting node :");
// 	scanf("%d",&start);

// 	DepthFirstSearch(a,n,start,parent,b);
	
// 	//printf("%d parent \n",parent[start] );
// 	// for(i=0;i<n;i++)
// 	// {
// 	// 	printf(" %d",parent[i] );
// 	// }
// 	copyMatrix(a,n,b,parent,start);
// 	writeDotfile(n,b);
// }
// int DepthFirstSearch(char a[100][100],int n,int n1,int parent[],char b[n][n])//Graph01.txt
// {
// 	int i,j,current,flag=0;
// 	stack *top;
// 	int visited[n];
	
// 	parent[n1]=-1;
// 	for(i=0;i<n;i++)
// 	{
// 		visited[i]=0;
// 	}
	
// 	pushStack(&top,n1);
// 	while(isEmpty(&top))
// 	{
// 		current=popStack(&top);
// 		if(visited[current]==0)
// 		{
// 			//printf(" %d",current );
// 			visited[current]=1;
// 			for(j=0;j<n;j++)
// 			{
// 				if(a[current][j]=='1' && visited[j]==0)
// 				{
// 					parent[j]=current;
// 					pushStack(&top,j);
// 				}
// 			}
// 		}		
// 	}
	
// 	return 1;
// }
// void copyMatrix(char a[100][100],int n,char b[n][n],int parent[n],int start)
// {
// 	int i;
// 	for(i=0;i<n;i++)
// 	{
// 		if(i!=start)
// 		{
// 			b[i][parent[i]]='r';
// 			b[parent[i]][i]='r';
// 		}
// 	}	
// }