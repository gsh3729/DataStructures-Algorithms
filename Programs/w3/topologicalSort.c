/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : topologicalSort.c
	DATE : 17/1/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node //nodes of linked list
{
	int data;
	struct node *next;
}node;

typedef struct stack
{
	int data;
	struct stack *next;
}stack;

typedef struct graph //graph information
{
	int num_of_Vertices;
}graph;

typedef struct vertex
{
	int visited;
	int pre;
	int post;
	int parent;
}vertex;

typedef struct Adjlist
{
	node *head;
}Adjlist;

void TopologicalSort(vertex *V,int start,Adjlist *AdjlistArray,stack **top);
int checkDAG(vertex *V);
void printStack(stack **top);
void push(stack **top,int newValue);
int pop(stack **top);
int isEmpty(stack **top);

int u=-1,v=-1,timing;
void main()
{
	int valueScanned,i,newline=0;
	
	graph *G = (graph*)malloc(sizeof(graph));
	scanf("%d",&G->num_of_Vertices);

	vertex *V = (vertex*)malloc(G->num_of_Vertices * sizeof(vertex));

	Adjlist *AdjlistArray = (Adjlist*)malloc(G->num_of_Vertices*sizeof(Adjlist));

	for(i = 0;i<G->num_of_Vertices;i++)
	{
		V[i].parent=-1;
		V[i].visited=0; //keeping all vertices as unvisited
		V[i].pre=-1; 
		V[i].post=-1;
	}

	node *newnode,*tail;
	for(i = 0;i<G->num_of_Vertices;i++)//maintaining linked list for all vertices
	{
		while(1)
		{
			scanf("%d",&valueScanned);
			if(valueScanned==-1 &&newline==0) //when the vertex does not have any adjacent vertex
			{
				AdjlistArray[i].head=NULL;
			}
			if(valueScanned!=-1)
			{
				if(newline==0) //assigning head of linked list to vertexHeadPointer
				{
					AdjlistArray[i].head=(node*)malloc(sizeof(node));
					AdjlistArray[i].head->data=valueScanned;
					AdjlistArray[i].head->next=NULL;
					tail=AdjlistArray[i].head;
					newline++;
				}
				else //pushing the linked list
				{
					newnode=(node*)malloc(sizeof(node));
					newnode->data=valueScanned;
					newnode->next=NULL;
					tail->next=newnode;
					tail=newnode;
				}
			}
			else
			{
				newline=0;
				break;
			}
		}
	}
	
	stack *top=NULL;
	timing=1;
	for(i = 0;i<G->num_of_Vertices;i++)
	{
		if(V[i].visited!=1) 
//if any vertex doesn't get visited we again start dfs from that vertex such that all vertices are visited 
		{
			TopologicalSort(V,i,AdjlistArray,&top);
		}
	}
	if(checkDAG(V)==0)
	{
		printf("TopologicalSort is ");
		printStack(&top);
	}	
}
int checkDAG(vertex *V)
{
	int x=u;
	if (u==-1 && v==-1)
	{
		return 0;
	}
	else
	{
		printf("A directed cycle is detected\n");
		printf("Cycle is ");
		stack *top1;
		while(x!=v)
		{
			push(&top1,x);
			x=V[x].parent;
		}
		printf("%d->",v);
		while(isEmpty(&top1))
		{
			printf("%d->",pop(&top1));
		}
		printf("%d\n",v);
		return 1;
	}
}
void TopologicalSort(vertex *V,int start,Adjlist *AdjlistArray,stack **top)
{
	node *temp;
	V[start].visited=1;
	V[start].pre=timing;
	timing++;

	temp=AdjlistArray[start].head;
	while(temp!=NULL)                                                                                                                                                                                                                    
	{
		if(V[temp->data].visited==0)
		{
			V[temp->data].parent=start;
			TopologicalSort(V,temp->data,AdjlistArray,top);
		}
		else if(V[temp->data].post==-1) //detecting back edge
		{
			u=start;
			v=temp->data;
		}
		temp=temp->next;
	}
	push(top,start);
	V[start].post=timing;
	timing++;
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
