/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : btree.c
	DATE : 2/3/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


typedef struct node
{
	int t;
	int size;
	int leaf;
	int *keys;
	struct node **child;
}node;


void insert(node **root,int item);
void insertNonFull(node **x,int item);
void splitChild(node **x,int i);
void printTree(node *root);
node* createNewNode();

void main()
{
	int n,i,key;
	scanf("%d",&n);

	node *root=NULL;
	for (i = 0; i < n; i++)
	{
		scanf("%d",&key);
		insert(&root,key);
		printTree(root);
	}

	while(1)
	{
		scanf("%d",&key);
		if(key==-1)
		{
			break;
		}
		//search((*root),key);
		//printRoute((*root));
	}
}
void printTree(node *root)
{
	if (root==NULL)
	{
		return;
	}
	int i=0;
	printTree(root->child[0]);
	
	while(i < (root->size))
	{
		printf("%d\n",root->keys[i]);
		printTree(root->child[i+1]);
	}
}
node* search(node *root,int item)
{
    int i = 0;
    while (i < root->size && root->keys[i] < item)
    {
        i++;
    }
 
    if(root->keys[i] == item && i<=(root->size))
    {
    	//printRoute(root,i);
        return root;
    }
 
    if (root->leaf == 1)
    {
    	return NULL;
    }   
    else
	{
  		return search(root->child[i],item); 	
  	}
}
void insert(node **root,int item)
{
	if ((*root)==NULL)
	{
		(*root)=createNewNode();
		(*root)->leaf=1;
		(*root)->keys[0]=item;
		(*root)->size=1;
		return;
	}

	if((*root)->size == (2*((*root)->t)-1))
	{
		node *newnode=createNewNode();
		newnode->leaf=0;

		newnode->child[0]=*root;
		(*root) = newnode;
		splitChild(root,0);

	}

	insertNonFull(root,item);
}
void insertNonFull(node **x,int item)
{
	int i;
	if ((*x)->leaf==1)
	{
		i=(*x)->size;
		while (i >= 0 && (*x)->keys[i] > item)
        {
            (*x)->keys[i+1] = (*x)->keys[i];
            i--;
        }
        (*x)->keys[i+1] = item;
        (*x)->size = (*x)->size +1;
	}
	else
	{
		i=(*x)->size;
		while (i >= 0 && (*x)->keys[i] > item)
		{
            i--;
		}
 
        if (((*x)->child[i+1])->size == 2*((*x)->t)-1)
        {
            splitChild(&((*x)->child[i+1]),i+1);

            if ((*x)->keys[i+1] < item)
            {
                i++;
            }
        }
        insertNonFull(&(*x)->child[i+1],item);
	}
}


void splitChild(node **x,int i)
{
	int j;
	node *y;
	y=(*x)->child[i];
	node *z=createNewNode();
	z->size=(z->t)-1;

	for (j = 0; j < (y->t)-1; j++)//copying last t-1 keys of y to z
	{
		z->keys[j]=y->keys[j+(y->t)];
	}

	if(y->leaf==0)
	{
		for (j = 0; j < (y->t); j++)//copying last t children of y to z
		{
			z->child[j]=y->child[j+(y->t)];
		}
	}

	y->size=(y->t)-1;


	for(j = ((*x)->size)-1; j >= i; j--)
	{
        (*x)->keys[j+1] = (*x)->keys[j];
	}

    (*x)->keys[i] = y->keys[(y->t)-1];

    for (j = (*x)->size; j >= i+1; j--)
    {
        z->child[j+1] = y->child[j];
    }
 
    (*x)->child[i+1] = z;
 
    (*x)->size = (*x)->size + 1;

}
node* createNewNode()
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->t=3;
	newnode->child=(node**)malloc((2*(newnode->t))*sizeof(node *));
	newnode->keys=(int*)malloc((2*(newnode->t)-1)*sizeof(int));
	newnode->size=0;
	newnode->leaf=0;
	return newnode;
}
