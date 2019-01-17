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

typedef struct node //nodes of linked list
{
	int data;
	struct node *next;
}node;

typedef struct graph //graph information
{
	int num_of_Vertices;
	int *visited;
	int *parent;
	node **vertexPointer;
}graph;

void main()
{
	int source,i;

	scanf("%d",&n);
	scanf("%d",&num_of_Edges);
	
	graph *G = (graph*)malloc(sizeof(graph));

	G->num_of_Vertices=n;
	G->visited=(int *)malloc(n*sizeof(int));
	G->parent=(int *)malloc(n*sizeof(int));

	G->vertexPointer=(node **)malloc(n*sizeof(node *));
	
	for(i = 0;i<G->num_of_Vertices;i++)
	{
		G->parent[i]=-1;
		G->visited[i]=0; //keeping all vertices as unvisited
	}

	for(k = 0;i<G->num_of_Edges;k++)
	{
		scanf("%d%d%d",&i,&j,&weight);
		addEdge(i,j,weight);
	}
	scanf("%d",&source);

	for(i = 0;i<G->num_of_Vertices;i++)
	{
		
	}
	fscanf(fptr,"%d",&source);
	fclose(fptr);
	
}

void addEdge(graph *G,int i,int j,int weight)
{
	if(G->vertexPointer[i]==NULL)
	{
		node *newnode = (node*)malloc(sizeof(node));
		newnode->data=j;
		newnode->next=NULL;
		newnode->weight=weight;
		G->vertexPointer[i]=newnode;
	}
	else
	{
		node *newnode = (node*)malloc(sizeof(node));
		newnode->data=j;
		newnode->next=G->vertexPointer[i];
		newnode->weight=weight;
		G->vertexPointer[i]=newnode;
	}
	if(G->vertexPointer[j]==NULL)
	{
		node *newnode = (node*)malloc(sizeof(node));
		newnode->data=i;
		newnode->next=NULL;
		newnode->weight=weight;
		G->vertexPointer[j]=newnode;
	}
	else
	{
		node *newnode = (node*)malloc(sizeof(node));
		newnode->data=i;
		newnode->next=G->vertexPointer[j];
		newnode->weight=weight;
		G->vertexPointer[j]=newnode;
	}
}