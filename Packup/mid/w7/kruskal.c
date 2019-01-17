/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : kruskal.c
	DATE : 15/2/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct graph //graph information
{
	int num_of_Vertices;
	int num_of_Edges;
}graph;

typedef struct edge
{
	int source;
	int destination;
	int weight;	
}edge;

typedef struct Heap 
{
	int heapSize;
	int *heap_costArray;
}Heap;

typedef struct Heapnode
{
	int source;
	int destination;
	int weight;
}Heapnode;

typedef struct subset
{
	int parent;
	int rank;
}subset;

void kruskal(graph *G,edge *E);
int find(subset *S,int u);
void Union(subset *S,int u,int v);
subset* makeset(graph *G);
void addEdge(edge *E,int source,int destination,int weight);

void minHeapify(Heap *H,Heapnode *Hnode,int index);
Heapnode* deleteMin(Heap *H,Heapnode *Hnode);
void buildHeap(Heap *H,Heapnode *Hnode);
void swapnodes(Heapnode *a,Heapnode *b);
void swap(int *a,int *b);

void main()
{
	int i,j,k;
	int source,weight;

	graph *G = (graph*)malloc(sizeof(graph));
	scanf("%d",&G->num_of_Vertices);
	scanf("%d",&G->num_of_Edges);
	
	edge *E = (edge*)malloc(G->num_of_Edges*sizeof(edge));

	for(k = 0;k<G->num_of_Edges;k++)
	{
		scanf("%d %d %d",&i,&j,&weight);
		addEdge(&E[k],i,j,weight);
		//printf("%d %d %d\n",E[k].source,E[k].destination,E[k].weight );

	}
	
	kruskal(G,E);

}

int find(subset *S,int u)
{
	if (S[u].parent==u)
	{
		return u;
	}
	int v=find(S,S[u].parent);
	S[u].parent = v;
	return v;

	// int v=u;
	// while(v!=S[v].parent)
	// {
	// 	v=S[v].parent;
	// }
	// return v;
}

void Union(subset *S,int x,int y)
{

	if(S[x].rank==S[y].rank)
	{
		S[y].parent = x;
		S[x].rank++;
	}
	else if(S[x].rank > S[y].rank)
	{
		S[y].parent = x;
	}
	else
	{
		S[x].parent = y;	
	}

}
subset* makeset(graph *G)
{
	subset *S = (subset*)malloc(G->num_of_Vertices*sizeof(subset));
	for(int i = 0;i<G->num_of_Vertices;i++)
	{
		S[i].rank=0;
		S[i].parent=i;
	}
	return S;
}
void kruskal(graph *G,edge *E)
{
	int i,x;

	subset *S = makeset(G);
		
	Heap *H = (Heap*)malloc(sizeof(Heap));

	H->heap_costArray = (int*)malloc(G->num_of_Edges*sizeof(subset));

	Heapnode *Hnode = (Heapnode*)malloc(G->num_of_Edges*sizeof(Heapnode));

	for(i = 0;i<G->num_of_Edges;i++)
	{	
		//printf(" %d-%d-%d\n",E[i].source,E[i].destination,E[i].weight );
		Hnode[i].source=E[i].source;
		Hnode[i].destination=E[i].destination;
		Hnode[i].weight=E[i].weight;
		H->heap_costArray[i] = E[i].weight;
	}

	H->heapSize=G->num_of_Edges;
	
	buildHeap(H,Hnode);

	Heapnode **MSTedges = (Heapnode**)malloc((G->num_of_Vertices-1)*sizeof(Heapnode*));

	Heapnode *e;
	i=0;
	while(i<(G->num_of_Vertices-1))
	{
		e=deleteMin(H,Hnode);
		
		int x = find(S,e->source);
		int y = find(S,e->destination);

		if(x!=y)
		{
			Union(S,x,y);
			MSTedges[i]=e;
			i++;
		}
	}
	int totalWeight=0;
	printf("\nThe minimum spanning tree of the given graph contains the following edges \n");
	for(i = 0; i < G->num_of_Vertices-1;i++)
	{		
		totalWeight=totalWeight+MSTedges[i]->weight;
		printf("\t%d - %d \n",MSTedges[i]->source,MSTedges[i]->destination);
 	}
 	printf(" TotalWeight%d\n",totalWeight );
}

Heapnode* deleteMin(Heap *H,Heapnode *Hnode)
{
	if (H->heapSize ==0)
	{
		return NULL;
	}
	Heapnode *minHeapNode=(Heapnode*)malloc(sizeof(Heapnode));
	minHeapNode->source=Hnode[0].source;
	minHeapNode->destination=Hnode[0].destination;
	minHeapNode->weight=Hnode[0].weight;
	//printf("%d--%d--%d\n",minHeapNode->source,minHeapNode->destination,minHeapNode->weight );
	H->heap_costArray[0]=H->heap_costArray[H->heapSize-1];
	Hnode[0]=Hnode[H->heapSize-1];
	(H->heapSize)--;
	minHeapify(H,Hnode,0);
	return minHeapNode;
}
void minHeapify(Heap *H,Heapnode *Hnode,int index)
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
		swapnodes(&Hnode[index],&Hnode[smallestIndex]);
		swap(&H->heap_costArray[index],&H->heap_costArray[smallestIndex]);
		
		minHeapify(H,Hnode,smallestIndex);
	}

}

void buildHeap(Heap *H,Heapnode *Hnode)
{
	for(int i=(H->heapSize/2-1);i>=0;i--)
	{
		minHeapify(H,Hnode,i);
	}
}
void addEdge(edge *E,int source,int destination,int weight)
{
	E->source = source;
	E->destination = destination;
	E->weight=weight;
}
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void swapnodes(Heapnode *a,Heapnode *b)
{
	Heapnode *temp = (Heapnode*)malloc(sizeof(Heapnode));
	temp=a;
	a=b;
	b=temp;
}