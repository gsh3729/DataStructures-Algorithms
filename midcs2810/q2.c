/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : q2.c
	DATE : 27/2/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct stack //nodes of stack
{
	int data;
	struct stack *next;
}stack;

typedef struct node //nodes of linked list
{
	int data;
	int weight;
	int repair;
	struct node *next;
}node;

typedef struct graph //graph information
{
	int num_of_Vertices;
	int num_of_Edges;
}graph;

typedef struct vertex //vertex properties
{
	int visited;
	int parent;
	int vertexPosition;
	int distance;
}vertex;

typedef struct Adjlist //maintains head pointers of all vertices 
{
	node *head;
}Adjlist;

typedef struct Heap  //heap structure
{
	int heapSize;
	int *heap_element;
	int *heap_distArray;
}Heap;

typedef struct repair_edges //struct that maintains repair edges
{
	int source;
	int destination;
}Re_Edges;

void push(stack **top,int newValue); //stack functions
int pop(stack **top);
void printStack(stack **top);
int isEmpty(stack **top);

void dijkstra(graph *G,vertex *V,Adjlist *AdjlistArray,int source,int destination);
void decreaseKey(vertex *V,Heap *H,int index,int key);
int deleteMin(vertex *V,Heap *H);
void minHeapify(vertex *V,Heap *H,int index);
void addEdge(Adjlist *AdjlistArray,int i,int j,int weight);
void swap(int *a,int *b);
void buildHeap(vertex *V,Heap *H);


void main()
{
	int i,j,k,no_of_rounds,no_of_edges_repair,source,destination;
	int src,dest;
	int weight;

	graph *G = (graph*)malloc(sizeof(graph));   //creating graph
	scanf("%d",&G->num_of_Vertices);
	scanf("%d",&G->num_of_Edges);
	
	vertex *V = (vertex*)malloc(G->num_of_Vertices*sizeof(vertex));
	
	Adjlist *AdjlistArray = (Adjlist*)malloc(G->num_of_Vertices*sizeof(Adjlist));

	for(k = 0;k<G->num_of_Edges;k++)
	{
		scanf("%d %d %d",&i,&j,&weight); 
		addEdge(AdjlistArray,i,j,weight); //adding edges to the graph
	}
	
	scanf("%d",&no_of_rounds);

	for(i = 0; i < no_of_rounds;i++)
	{
		scanf("%d",&no_of_edges_repair);
		Re_Edges *E = (Re_Edges *)malloc(no_of_edges_repair*sizeof(Re_Edges)); //array to store repair edges
		for(j = 0; j < no_of_edges_repair;j++)
		{
			scanf("%d",&source);
			scanf("%d",&destination);
			E[j].source=source;
			E[j].destination=destination;
			node *temp=AdjlistArray[source].head;
        	while(temp!=NULL)
        	{
        		if(temp->data == destination)
        		{
        			temp->repair=1; //assigning repair 1 when that edge is under repair
        			break;
        		}
        		temp=temp->next;
        	}
        }
        scanf("%d",&src);
		scanf("%d",&dest);

		dijkstra(G,V,AdjlistArray,src,dest); //calling dijkstra to get shortest paths

		for(j = 0; j < no_of_edges_repair;j++)
		{
			node *temp=AdjlistArray[E[j].source].head;
        	while(temp!=NULL)
        	{
        		if(temp->data == E[j].destination)
        		{
        			temp->repair=0; //assigning repair to 0 for further rounds
        			break;
        		}
        		temp=temp->next;
        	}
        }
        free(E);
	}

}

void dijkstra(graph *G,vertex *V,Adjlist *AdjlistArray,int source,int destination)
{
	int i,x,totaldistance=0,j,v;
	
	Heap *H = (Heap*)malloc(sizeof(Heap));
	H->heap_distArray = (int*)malloc(G->num_of_Vertices * sizeof(int)); //array which maintains heap property
	H->heap_element = (int*)malloc(G->num_of_Vertices * sizeof(int)); 
	//array which tells what vertex is situated in a particular position of the heap

	for(i = 0;i<G->num_of_Vertices;i++)
	{		
		V[i].visited=0;
		V[i].parent=-1;
		V[i].vertexPosition = i; //vertexposition tells the position of that vertex in the heap
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
        if(u==destination)
        {
        	break;
        }
 		V[u].visited=1;
        node *temp=AdjlistArray[u].head;
        while(temp!=NULL)
        {
            int v = temp->data;
            if(V[v].visited==0 && temp->weight + x < H->heap_distArray[V[v].vertexPosition] && V[u].distance!=INT_MAX && temp->repair!=1)
            {  
        		V[v].parent=u;
           		V[v].distance= temp->weight + x;
            	decreaseKey(V,H,V[v].vertexPosition,temp->weight + x);    	
            }
            temp = temp->next;
        }
	}

	

	if (V[destination].distance==INT_MAX)
	{
		printf("No route found\n");
	 	return;
	}
	
	i=destination;
	stack *top=NULL;
	while(1)
	{
		push(&top,i);
		j=V[i].parent;
		node *temp=AdjlistArray[j].head;
		while(temp!=NULL)
        {
            v = temp->data;
            if(v==i)
            {
            	totaldistance = totaldistance + temp->weight;
            	break;
            }
            temp=temp->next;
        }
		i=j;
		if( V[i].parent == -1)
		{
			push(&top,i);
			break;
		}
	}
	printf("The shortest route is ");
	printStack(&top);
	printf("Total distance :%d\n",totaldistance);
	free(top);
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
	newnode->repair=0;
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


void printStack(stack **top)
{
	stack *temp;
	temp=*top;
	while(temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\n");
}
void push(stack **top,int newValue)//function to push the element in to stack
{
	stack *temp;
	temp=(stack *)malloc(sizeof(stack));
	temp->data=newValue;
	temp->next=*top;
	*top=temp;
}
int pop(stack **top)//function to pop out the element
{
	int popValue;
	stack *temp;	
	if( isEmpty(top) )
	{
		temp=*top;
		popValue=temp->data;
		*top=(*top)->next;
		free(temp);
		return popValue;
	}
	else
	{
		printf("\n Stack is empty");
		return -1;
	}
}	
int isEmpty(stack **top)//checking whether the stack is empty or not
{
	if (*top == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}