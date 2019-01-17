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
	int *visited;
	int *parent;
	//int *dist;
	node **vertexPointer;
}graph;

void printll(graph *G);
void dijkstra(graph *G,int source);
void decreaseKey(int heap_distArray[],int v,int key);
int deleteMin(int heap_distArray[]);
void minHeapify(int heap_distArray[],int index);
void buildHeap(int heap_distArray[]);
void addEdge(graph *G,int i,int j,int weight);
void swap(int *a,int *b);

int heapSize,vertexPosition[100],heap_element[100];

void main()
{
	int i,j,k,n;
	int source,weight;

	scanf("%d",&n);
	graph *G = (graph*)malloc(sizeof(graph));
	scanf("%d",&G->num_of_Edges);
	
	G->num_of_Vertices=n;
	G->visited=(int *)malloc(n*sizeof(int));
	G->parent=(int *)malloc(n*sizeof(int));

	G->vertexPointer=(node **)malloc(n*sizeof(node *));
	
	for(k = 0;k<G->num_of_Edges;k++)
	{
		scanf("%d %d %d",&i,&j,&weight);
		addEdge(G,i,j,weight);
		addEdge(G,j,i,weight);
	}
	//printll(G);
	
	scanf("%d",&source);
	
	dijkstra(G,source);

}

void dijkstra(graph *G,int source)
{
	int i,heap_distArray[G->num_of_Vertices],distance[G->num_of_Vertices];
	int x;
	for(i = 0;i<G->num_of_Vertices;i++)
	{
		heap_distArray[i]=INT_MAX;
		G->visited[i]=0;
		G->parent[i]=-1;
		vertexPosition[i] = i;
		heap_element[i] = i;
		distance[i] = INT_MAX;
	}

	heapSize=G->num_of_Vertices;

	heap_distArray[source]=0;
	distance[source] = 0;

	vertexPosition[source]=0;
	heap_element[0]=source;
	buildHeap(heap_distArray);

	while(heapSize>0)
    {
    	
    	x = heap_distArray[0];
        int u=deleteMin(heap_distArray);
       
 		G->visited[u]=1;
        node *temp=G->vertexPointer[u];
        while(temp!=NULL)
        {
            int v = temp->data;
 	
            if(G->visited[v]==0 && temp->weight + x< heap_distArray[vertexPosition[v]])
            {            	
	            G->parent[v]=u;
	            distance[v] = temp->weight + x;
                decreaseKey(heap_distArray,vertexPosition[v],temp->weight + x);
            }
            temp = temp->next;
        }
	}

	for(i = 0; i < G->num_of_Vertices;i++)
	{
		printf("\tDistance of %d is %d , parent of %d is %d\n",i,distance[i],i,G->parent[i]);
	}
}
void decreaseKey(int heap_distArray[],int v,int key)
{
	if (v<=0)
	{
		return;
	}
	
	heap_distArray[v] = key;
	
	if(key<heap_distArray[(v-1)/2])
	{
		swap(&vertexPosition[heap_element[v]],&( vertexPosition[heap_element[(v-1)/2] ] ));
		swap(&heap_element[v],&heap_element[(v-1)/2]);
		swap(&heap_distArray[v],&heap_distArray[(v-1)/2]);

		decreaseKey(heap_distArray,(v-1)/2,key);
	}
	else
	{
		return;
	}
}
int deleteMin(int heap_distArray[])
{
	int min_dist_vertex=heap_element[0];
	heap_distArray[0]=heap_distArray[heapSize-1];
	vertexPosition[heap_element[heapSize-1]] =0;
	vertexPosition[heap_element[0]]=heapSize-1;
	swap(&heap_element[0],&heap_element[heapSize-1]);
	
	(heapSize)--;
	minHeapify(heap_distArray,0);
	return min_dist_vertex;
}
void minHeapify(int heap_distArray[],int index)
{
	int leftChild=2*index+1;
	int rightChild=2*index+2;
	int smallestIndex=index;

	if(heap_distArray[leftChild]<heap_distArray[smallestIndex] && leftChild<heapSize)
	{
		smallestIndex=leftChild;
	}

	if(heap_distArray[rightChild]<heap_distArray[smallestIndex] && rightChild<heapSize)
	{
		smallestIndex=rightChild;
	}

	if(smallestIndex!=index)
	{
		swap(&vertexPosition[heap_element[index]],&vertexPosition[heap_element[smallestIndex]]);
		swap(&heap_element[index],&heap_element[smallestIndex]) ;
		swap(&heap_distArray[index],&heap_distArray[smallestIndex]);
		
		minHeapify(heap_distArray,smallestIndex);
	}

}
void buildHeap(int heap_distArray[])
{
	for(int i=(heapSize/2-1);i>=0;i--)
	{
		minHeapify(heap_distArray,i);
	}
}

void addEdge(graph *G,int i,int j,int weight)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->data=j;
	newnode->weight=weight;
	if(G->vertexPointer[i]==NULL)
	{
		newnode->next=NULL;
	}
	else
	{
		newnode->next=G->vertexPointer[i];
	}
	G->vertexPointer[i]=newnode;
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void printll(graph *G)//to print the linked list nodes
{
	int i;
	node *temp;
	for(i = 0;i<G->num_of_Vertices;i++) //to print only head nodes all  vertices
	{
		printf("%d%d\n",i,G->vertexPointer[i]->data );
	}
	printf("\nScanned input file\n");
	for(i = 0;i<G->num_of_Vertices;i++) //to print entire linked lists of all vertices
	{
		temp=G->vertexPointer[i];
		while(temp!=NULL)
		{
			printf("%d->",temp->data);
			temp=temp->next;
		}
		printf("NULL\n");
	}
}