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
	int noOfVertices;
	int *visited;
	int *pre;
	int *post;
	int *parent;
	node **vertexPointer;
	int timing;
}graph;


void TopologicalSort(graph *G,int start,stack **top);
int checkDAG(graph *G);

void printStack(stack **top);
void push(stack **top,int newValue);
int pop(stack **top);
int isEmpty(stack **top);

int u=-1,v=-1;
void main()
{
	int n,start,valueScanned,i,newline;

	char filename[30];

	printf("\n..Enter the input graph filename:");
	scanf("%s",filename);

	FILE *fptr;
	fptr=fopen(filename,"r");

	if(fptr==0)
	{
		printf("\n..Error in opening the file\n");
		exit(0);
	}

	fscanf(fptr,"%d",&n);
	
	graph *G = (graph*)malloc(sizeof(graph));

	G->noOfVertices=n;
	G->visited=(int *)malloc(n*sizeof(int));
	G->pre=(int *)malloc(n*sizeof(int));
	G->post=(int *)malloc(n*sizeof(int));
	G->parent=(int *)malloc(n*sizeof(int));

	G->vertexPointer=(node **)malloc(n*sizeof(node *));
	node *newnode,*tail;
	
	for(i = 0;i<G->noOfVertices;i++)
	{
		G->parent[i]=-1;
		G->visited[i]=0; //keeping all vertices as unvisited
		G->pre[i]=-1; 
		G->post[i]=-1;
	}
	//G->parent[start]=-1; //parent of start vertex is assigned -1
	G->timing=1;
	for(i = 0;i<G->noOfVertices;i++)//maintaining linked list for all vertices
	{
		while(1)
		{
			fscanf(fptr,"%d",&valueScanned);
			if(valueScanned==-1 &&newline==0) //when the vertex does not have any adjacent vertex
			{
				//vertexPointer[i]=(node*)malloc(sizeof(node));
				//vertexPointer[i]->data=-1;
				G->vertexPointer[i]=NULL;
			}
			if(valueScanned!=-1)
			{
				if(newline==0) //assigning head of linked list to vertexpointer
				{
					G->vertexPointer[i]=(node*)malloc(sizeof(node));
					G->vertexPointer[i]->data=valueScanned;
					G->vertexPointer[i]->next=NULL;
					tail=G->vertexPointer[i];
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
	fclose(fptr);
	
	stack *top=NULL;
	for(i = 0;i<G->noOfVertices;i++)
	{
		if(G->visited[i]!=1) 
//if any vertex doesn't get visited we again start dfs from that vertex such that all vertices are visited 
		{
			TopologicalSort(G,i,&top);
		}
	}
	if(checkDAG(G)==0)
	{
		printf("TopologicalSort is ");
		printStack(&top);
	}	
}
int checkDAG(graph *G)
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
		while(x!=v)
		{
			printf("%d->",x);
			x=G->parent[x];
		}
		printf("%d->%d\n",v,u);
		return 1;
	}
}
void TopologicalSort(graph *G,int start,stack **top)
{
	node *temp;
	G->visited[start]=1;
	G->pre[start]=G->timing;
	G->timing++;

	temp=G->vertexPointer[start];
	while(temp!=NULL)                                                                                                                                                                                                                   
	{
		if(G->visited[temp->data]==0)
		{
			G->parent[temp->data]=start;
			TopologicalSort(G,temp->data,top);
		}
		else if(G->post[temp->data]==-1) //detecting back edge
		{
			u=start;
			v=temp->data;
		}
		temp=temp->next;
	}
	push(top,start);
	G->post[start]=G->timing;
	G->timing++;
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
// void printTimings(graph *G)//to print pre and post timings of vertices
// {
// 	int i;
// 	for(i=0;i<G->noOfVertices;i++)
// 	{
// 		printf("\nStart and finish time of vertex %d are (%d,%d)",i,G->pre[i],G->post[i] );	
// 	}
// }

// void EdgeTypes(graph *G)
// {
// 	int i,u,v;
// 	node *temp;
// 	for(i=0;i<G->noOfVertices;i++)                                                                                                                                                                                                                    
// 	{
// 		temp=G->vertexPointer[i];	
// 		while(temp!=NULL)
// 		{
// 			u=i;
// 			v=temp->data;
// 			temp=temp->next;
			
// 			if( G->pre[u] < G->pre[v] ) //condition for tree edge and forward edge
// 			{
// 				if(G->parent[v]==u) //condition for tree edge
// 				{
// 					printf("\n%d-%d is tree edge",u,v);
// 				}
// 				else
// 				{
// 					printf("\n%d-%d is forward edge",u,v);
// 				}	
// 			}
// 			if( G->pre[v]<G->pre[u] && G->post[u]<G->post[v]) //condition for back edge
// 			{
// 				printf("\n%d-%d is back edge",u,v);
// 			}
// 			if( G->pre[v]<G->post[v] && G->pre[u]>G->post[v]) //condition for cross edge
// 			{
// 				printf("\n%d-%d is cross edge",u,v);
// 			}
// 		}
// 	}
// }

// void printll(graph *G)//to print the linked list nodes
// {
// 	int i;
// 	node *temp;
// 	// for(i = 0;i<n;i++) //to print only head nodes all  vertices
// 	// {
// 	// 	printf("%d%d\n",i,vertexPointer[i]->data );
// 	// }
// 	printf("\nScanned input file\n");
// 	for(i = 0;i<G->noOfVertices;i++) //to print entire linked lists of all vertices
// 	{
// 		temp=G->vertexPointer[i];
// 		while(temp!=NULL)
// 		{
// 			printf("%d->",temp->data);
// 			temp=temp->next;
// 		}
// 		printf("NULL\n");
// 	}
// }

// int checkEdge(graph *G,int vertex1,int vertex2)//to check if there is edge between any two vertices
// {
// 	int flag=1;
// 	node *temp;
// 	temp=G->vertexPointer[vertex1];
// 	while(temp!=NULL)
// 	{
// 		if((temp->data)==vertex2)
// 		{
// 			flag=2;
// 			return 1;
// 		}
// 		else
// 		{
// 			temp=temp->next;
// 		}
// 	}
// 	if(flag==1)
// 	{
// 		return 0;
// 	}
// }


//node *temp;
	// for(i=0;i<G->noOfVertices;i++)                                                                                                                                                                                                                    
	// {
	// 	temp=G->vertexPointer[i];	
	// 	while(temp!=NULL)
	// 	{
	// 		u=i;
	// 		v=temp->data;
	// 		temp=temp->next;
			
	// 		if( G->pre[v]<G->pre[u] && G->post[u]<G->post[v]) //condition for back edge
	// 		{
	// 			printf("A directed cycle is detected\n");
	// 			while(u!=v)
	// 			{
	// 				printf("bye\n");
	// 				for(k=0;k<G->noOfVertices;k++)
	// 				{
	// 					printf("ensms\n");
	// 					if(G->parent[k]==u && u!=k)
	// 					{
	// 						printf("hiii\n");
	// 						printf("%d ",k);
	// 					//	u=k;
	// 						break;
	// 					}
	// 				}
	// 				u=k;
	// 			}
	// 			printf("%d \n",v);
	// 			//exit(0);
	// 		}
	// 	}
	// }