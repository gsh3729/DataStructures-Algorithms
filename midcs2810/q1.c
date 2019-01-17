/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : q1.c
	DATE : 27/2/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct node //nodes of linked list
{
	int data;
	struct node *next;
}node;

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

void printll(graph *G,vertex *V,Adjlist *AdjlistArray); 
void EdgeTypes(graph *G,vertex *V,Adjlist *AdjlistArray);
void printTimings(graph *G,vertex *V);
void DepthFirstSearch(vertex *V,int start,Adjlist *AdjlistArray);
int checkEdge(graph *G,int i,int j);

int timing;

void main()
{
	int valueScanned,i,newline=0;

	graph *G = (graph*)malloc(sizeof(graph));
	scanf("%d",&G->num_of_Vertices);

	vertex *V = (vertex*)malloc(G->num_of_Vertices * sizeof(vertex));

	Adjlist *AdjlistArray = (Adjlist*)malloc(G->num_of_Vertices*sizeof(Adjlist));

	node *newnode,*tail;
	
	for(i = 0;i<G->num_of_Vertices;i++)
	{
		V[i].parent=-1;
		V[i].visited=0; //keeping all vertices as unvisited
		V[i].pre=-1; 
		V[i].post=-1;
	}
	
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
	printll(G,V,AdjlistArray); //to print entire scanned file input
	timing=1;
	for(i = 0;i<G->num_of_Vertices;i++)
	{
		if(V[i].visited!=1) 
//if any vertex doesn't get visited we again start dfs from that vertex such that all vertices are visited 
		{
			DepthFirstSearch(V,i,AdjlistArray);
		}
	}
	printTimings(G,V);
	EdgeTypes(G,V,AdjlistArray);
	printf("\n");
	
}

void DepthFirstSearch(vertex *V,int start,Adjlist* AdjlistArray)
{
	node *temp;
	V[start].visited=1;
	V[start].pre=timing;
	timing++;

	temp=AdjlistArray[start].head;
	while(temp !=     NULL)                                                                                                                                                                                                                      
	{
		if(V[temp->data].visited==0)
		{
			V[temp->data].parent=start;
			DepthFirstSearch(V,temp->data,AdjlistArray);
		}
		temp=temp->next;
	}
	V[start].post=timing;
	timing++;
}

void printTimings(graph *G,vertex *V)//to print pre and post timings of vertices
{
	int i;
	for(i=0;i<G->num_of_Vertices;i++)
	{
		printf("\nStart and finish time of vertex %d are (%d,%d)",i,V[i].pre,V[i].post);	
	}
}

void EdgeTypes(graph *G,vertex *V,Adjlist *AdjlistArray)
{
	int i,u,v;
	node *temp;
	for(i=0;i<G->num_of_Vertices;i++)                                                                                                                                                                                                                    
	{
		temp=AdjlistArray[i].head;	
		while(temp!=NULL)
		{
			u=i;
			v=temp->data;
			temp=temp->next;
			
			if( V[u].pre < V[v].pre ) //condition for tree edge and forward edge
			{
				if(V[v].parent==u) //condition for tree edge
				{
					printf("\n%d-%d is tree edge",u,v);
				}
				else
				{
					printf("\n%d-%d is forward edge",u,v);
				}	
			}
			if( V[v].pre<V[u].pre && V[u].post<V[v].post) //condition for back edge
			{
				printf("\n%d-%d is back edge",u,v);
			}
			if( V[v].pre<V[v].post && V[u].pre>V[v].post) //condition for cross edge
			{
				printf("\n%d-%d is cross edge",u,v);
			}
		}
	}
}

void printll(graph *G,vertex *V,Adjlist *AdjlistArray)//to print the linked list nodes
{
	int i;
	node *temp;
	// for(i = 0;i<G->num_of_Vertices ;i++) //to print only head nodes all  vertices
	// {
	// 	printf("%d%d\n",i,AdjlistArray[i].head->data );
	// }
	printf("\nScanned input file\n");
	for(i = 0;i<G->num_of_Vertices;i++) //to print entire linked lists of all vertices
	{
		temp=AdjlistArray[i].head;
		while(temp!=NULL)
		{
			printf("%d->",temp->data);
			temp=temp->next;
		}
		printf("NULL\n");
	}
}

// int checkEdge(graph *G,int vertex1,int vertex2)//to check if there is edge between any two vertices
// {
// 	int flag=1;
// 	node *temp;
// 	temp=G.head[vertex1];
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


