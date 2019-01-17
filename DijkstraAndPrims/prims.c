/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : dijkstra.c
	DATE : 30/1/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



typedef struct node //nodes of linked list
{
	int data;
	int weight;
	struct node *next;
}node;

typedef struct graph //graph information
{
	int num_of_Vertices;
	int num_of_Edges;
}graph;

typedef struct vertex
{
	int visited;
	int parent;
	int vertexPosition;
	node *vertexHeadPointer;
	int cost;
}vertex;

typedef struct Heap 
{
	int heapSize;
	int *heap_element;
	int *heap_costArray;
}Heap;

void prims(graph *G,vertex *V);
void decreaseKey(vertex *V,Heap *H,int index,int key);
int deleteMin(vertex *V,Heap *H);
void minHeapify(vertex *V,Heap *H,int index);
void addEdge(vertex *V,int i,int j,int weight);
void swap(int *a,int *b);


void main()
{
	int i,j,k;
	int source,weight;

	graph *G = (graph*)malloc(sizeof(graph));
	scanf("%d",&G->num_of_Vertices);
	scanf("%d",&G->num_of_Edges);
	
	vertex *V = (vertex*)malloc(G->num_of_Vertices*sizeof(vertex));
	
	for(k = 0;k<G->num_of_Edges;k++)
	{
		scanf("%d %d %d",&i,&j,&weight);
		addEdge(V,i,j,weight);
		addEdge(V,j,i,weight);
	}
	
	
	prims(G,V);

}

void prims(graph *G,vertex *V)
{
	int i,x;
	
	Heap *H = (Heap*)malloc(sizeof(Heap));
	H->heap_costArray = (int*)malloc(G->num_of_Vertices * sizeof(int));
	H->heap_element = (int*)malloc(G->num_of_Vertices * sizeof(int));

	for(i = 0;i<G->num_of_Vertices;i++)
	{		
		V[i].visited=0;
		V[i].parent=-1;
		V[i].vertexPosition = i;
		V[i].cost = INT_MAX;
		H->heap_costArray[i]=INT_MAX;
		H->heap_element[i] = i;
	}

	H->heapSize=G->num_of_Vertices;

	H->heap_costArray[0]=0;
	V[0].cost= 0;
	
	while(H->heapSize>0)
    {
    	x = H->heap_costArray[0];
        int u=deleteMin(V,H);
       
 		V[u].visited=1;
        node *temp=V[u].vertexHeadPointer;
        while(temp!=NULL)
        {
            int v = temp->data;
            if(V[v].visited==0 && temp->weight < H->heap_costArray[V[v].vertexPosition] && V[u].cost!=INT_MAX)
            {         	
	            V[v].parent=u;
	            V[v].cost= temp->weight;
                decreaseKey(V,H,V[v].vertexPosition,temp->weight);
            }
            temp = temp->next;
        }
	}

	printf("\nThe minimum spanning tree of the given graph contains the following edges \n");
	for(i = 1; i < G->num_of_Vertices;i++)
	{
		if (V[i].parent!=-1)
		{
			printf("\t%d - %d \n",i,V[i].parent);
 		}
	}
}
void decreaseKey(vertex *V,Heap *H,int index,int key)
{
	if (index<=0)
	{
		return;
	}
	
	H->heap_costArray[index] = key;
	
	if(key<H->heap_costArray[(index-1)/2])
	{
		swap(&V[H->heap_element[index]].vertexPosition,&(V[H->heap_element[(index-1)/2]].vertexPosition));
		swap(&H->heap_element[index],&H->heap_element[(index-1)/2]);
		swap(&H->heap_costArray[index],&H->heap_costArray[(index-1)/2]);

		decreaseKey(V,H,(index-1)/2,key);
	}
	else
	{
		return;
	}
}
int deleteMin(vertex *V,Heap *H)
{
	int min_dist_vertex=H->heap_element[0];
	H->heap_costArray[0]=H->heap_costArray[H->heapSize-1];
	V[H->heap_element[H->heapSize-1]].vertexPosition =0;
	V[H->heap_element[0]].vertexPosition=H->heapSize-1;
	swap(&H->heap_element[0],&H->heap_element[H->heapSize-1]);
	
	(H->heapSize)--;
	minHeapify(V,H,0);
	return min_dist_vertex;
}
void minHeapify(vertex *V,Heap *H,int index)
{
	int leftChild=2*index+1;
	int rightChild=2*index+2;
	int smallestIndex=index;

	if(H->heap_costArray[leftChild]<H->heap_costArray[smallestIndex] && leftChild<H->heapSize)
	{
		smallestIndex=leftChild;
	}

	if(H->heap_costArray[rightChild]<H->heap_costArray[smallestIndex] && rightChild<H->heapSize)
	{
		smallestIndex=rightChild;
	}

	if(smallestIndex!=index)
	{
		swap(&V[H->heap_element[index]].vertexPosition,&V[H->heap_element[smallestIndex]].vertexPosition);
		swap(&H->heap_element[index],&H->heap_element[smallestIndex]) ;
		swap(&H->heap_costArray[index],&H->heap_costArray[smallestIndex]);
		
		minHeapify(V,H,smallestIndex);
	}

}

void addEdge(vertex *V,int i,int j,int weight)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->data=j;
	newnode->weight=weight;
	if(V[i].vertexHeadPointer==NULL)
	{
		newnode->next=NULL;
	}
	else
	{
		newnode->next=V[i].vertexHeadPointer;
	}
	V[i].vertexHeadPointer=newnode;
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
