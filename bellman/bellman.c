/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : bellman.c
	DATE : 2/3/18
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

typedef struct vertex
{
	int parent;
	int dist;
}vertex;

typedef struct stack
{
	int data;
	struct stack *next;
}stack;


void bellman(graph *G,edge *E,int source);
void addEdge(edge *E,int source,int destination,int weight);
void printCycle(graph *G,vertex *V,int v);
void swap(int *a,int *b);

void printStack(stack **top,int key);
void push(stack **top,int newValue);
int pop(stack **top);
int isEmpty(stack **top);

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
	
	scanf("%d",&source);
	bellman(G,E,source);

}


void bellman(graph *G,edge *E,int source)
{
	int i,j,u,v;

	vertex *V = (vertex*)malloc(G->num_of_Vertices*sizeof(vertex));

	for(i = 0;i<G->num_of_Vertices;i++)
	{
		V[i].dist=INT_MAX;
		V[i].parent=-1;
	}

	V[source].dist=0;
	V[source].parent=-1;

	for(i = 1; i <= G->num_of_Vertices-1; i++)
    {
        for(j = 0; j < G->num_of_Edges; j++)
        {
            u = E[j].source;
            v = E[j].destination;

            if (V[u].dist != INT_MAX && V[u].dist + E[j].weight < V[v].dist)
            {
                V[v].dist = V[u].dist + E[j].weight;
                V[v].parent=u;
            }
        }
    }
 


    for(i = 0; i < G->num_of_Edges; i++)
    {
        u = E[i].source;
        v = E[i].destination;
        if (V[u].dist != INT_MAX && V[u].dist + E[i].weight < V[v].dist)
        {
            printf("Negative weight cycle is detected\n");
            printCycle(G,V,v);
            return;
        }
    }

    for(i = 0;i<G->num_of_Vertices;i++)
	{
		printf("\tDistance of %d is %d\t parent of %d is %d\n",i,V[i].dist,i,V[i].parent);
	}
	
}
void printCycle(graph *G,vertex *V,int v)
{
	int i,temp,visited[G->num_of_Vertices];

	stack *top=NULL;

	for(i=0;i<G->num_of_Vertices;i++)
	{
		visited[i]=-1;
	}

	visited[v]=1;
	push(&top,v);
	temp=V[v].parent;
	while(visited[temp]!=1)
	{
		push(&top,temp);
		visited[temp]=1;		
		temp=V[temp].parent;
	}

	printf("%d ",temp);
	printStack(&top,temp);

}
void addEdge(edge *E,int source,int destination,int weight)
{
	E->source = source;
	E->destination = destination;
	E->weight=weight;
}
void printStack(stack **top,int key)
{
	stack *temp;
	temp=*top;
	
	while(temp!=NULL && temp->data!=key )
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("%d\n",key);
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