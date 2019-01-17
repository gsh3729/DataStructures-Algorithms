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
	int distance;
}vertex;

typedef struct Adjlist
{
	node *head;
}Adjlist;

typedef struct Heap 
{
	int heapSize;
	int *heap_element;
	int *heap_distArray;
}Heap;



void dijkstra(graph *G,vertex *V,Adjlist *AdjlistArray,int source);
void decreaseKey(vertex *V,Heap *H,int index,int key);
int deleteMin(vertex *V,Heap *H);
void minHeapify(vertex *V,Heap *H,int index);
void addEdge(Adjlist *AdjlistArray,int i,int j,int weight);
void swap(int *a,int *b);
void buildHeap(vertex *V,Heap *H);


void main()
{
	int i,j,k;
	int weight;

	graph *G = (graph*)malloc(sizeof(graph));
	scanf("%d",&G->num_of_Vertices);
	scanf("%d",&G->num_of_Edges);
	
	vertex *V = (vertex*)malloc(G->num_of_Vertices*sizeof(vertex));
	
	Adjlist *AdjlistArray = (Adjlist*)malloc(G->num_of_Vertices*sizeof(Adjlist));

	for(k = 0;k<G->num_of_Edges;k++)
	{
		scanf("%d %d %d",&i,&j,&weight);
		addEdge(AdjlistArray,i,j,weight);
		addEdge(AdjlistArray,j,i,weight);
	}
	
	
	dijkstra(G,V,AdjlistArray,1);

}

void dijkstra(graph *G,vertex *V,Adjlist *AdjlistArray, int source)
{
	int i,x;
	
	Heap *H = (Heap*)malloc(sizeof(Heap));
	H->heap_distArray = (int*)malloc(G->num_of_Vertices * sizeof(int));
	H->heap_element = (int*)malloc(G->num_of_Vertices * sizeof(int));

	for(i = 0;i<G->num_of_Vertices;i++)
	{		
		V[i].visited=0;
		V[i].parent=-1;
		V[i].vertexPosition = i;
		V[i].distance = INT_MAX;
		H->heap_distArray[i]=INT_MAX;
		H->heap_element[i] = i;
	}

	H->heapSize=G->num_of_Vertices;

	swap(&V[H->heap_element[0]].vertexPosition,&(V[H->heap_element[source]].vertexPosition));
	swap(&H->heap_element[0],&H->heap_element[source]);

	H->heap_distArray[0]=0;
	V[source].distance= 0;
	
	while(H->heapSize>0)
    {
    	x = H->heap_distArray[0];
        int u=deleteMin(V,H);
 		V[u].visited=1;
        node *temp=AdjlistArray[u].head;
        while(temp!=NULL)
        {
            int v = temp->data;
            if(V[v].visited==0 && temp->weight + x < H->heap_distArray[V[v].vertexPosition] &&V[u].distance!=INT_MAX)
            {  
        		V[v].parent=u;
           		V[v].distance= temp->weight + x;
            	decreaseKey(V,H,V[v].vertexPosition,temp->weight + x);    	
            }
            temp = temp->next;
        }
	}

	for(i = 0; i < G->num_of_Vertices;i++)
	{
		printf("\tDistance of %d is %d , parent of %d is %d\n",i,V[i].distance,i,V[i].parent);
	}
}
void decreaseKey(vertex *V,Heap *H,int index,int key)
{
	if (index<=0)
	{
		return;
	}
	
	H->heap_distArray[index] = key;
	
	if(key<H->heap_distArray[(index-1)/2])
	{
		swap(&V[H->heap_element[index]].vertexPosition,&(V[H->heap_element[(index-1)/2]].vertexPosition));
		swap(&H->heap_element[index],&H->heap_element[(index-1)/2]);
		swap(&H->heap_distArray[index],&H->heap_distArray[(index-1)/2]);

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
	H->heap_distArray[0]=H->heap_distArray[H->heapSize-1];
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

	if(H->heap_distArray[leftChild]<H->heap_distArray[smallestIndex] && leftChild<H->heapSize)
	{
		smallestIndex=leftChild;
	}

	if(H->heap_distArray[rightChild]<H->heap_distArray[smallestIndex] && rightChild<H->heapSize)
	{
		smallestIndex=rightChild;
	}

	if(smallestIndex!=index)
	{
		swap(&V[H->heap_element[index]].vertexPosition,&V[H->heap_element[smallestIndex]].vertexPosition);
		swap(&H->heap_element[index],&H->heap_element[smallestIndex]) ;
		swap(&H->heap_distArray[index],&H->heap_distArray[smallestIndex]);
		
		minHeapify(V,H,smallestIndex);
	}

}


void addEdge(Adjlist *AdjlistArray,int i,int j,int weight)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->data=j;
	newnode->weight=weight;
	if(AdjlistArray[i].head==NULL)
	{
		newnode->next=NULL;
	}
	else
	{
		newnode->next=AdjlistArray[i].head;
	}
	AdjlistArray[i].head=newnode;
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
