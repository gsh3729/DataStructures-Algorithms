/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM DESCRIPTION : 
	PROGRAM NAME : bst.c
	DATE : 2/3/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct node
{
	int key;
	struct node *leftptr;
	struct node *rightptr;
	struct node *parentptr;
}node;

struct node *root=NULL;

void deleteNode(node *root,int key);
node* search(node* root,int key);
void inorder(node* root);
node* insert(int key);
void postorder(node* root);
node* findInorderPrecedor(node* root,int key);
node* findMinKey(node* root);
void transplant(node *u,node *v);
void printTree(node* root,int tab);
void print_spaces(int spaces);

void main()
{
	int  item,option;
	node *temp=NULL;
	
	
	insert( 100);
	insert( 120);
	insert( 75);
	insert( 50);
	insert( 60);
	insert( 55);
	insert( 53);
	insert( 70);
	insert( 65);
	insert( 80);
	insert( 78);
	insert( 90);
	insert( 98);	
	insert( 110);
	insert( 150);

	// insert(3);
	// insert(2);
	// insert(1);
	// insert(4);
	// insert(5);
	// insert(6);
	
	
	while(1)
	{
		printf(" Menu\n 1.Searching");
		printf("\n 2.Insert");
		printf("\n 3.FindMinKey");
		printf("\n 4.InorderTraversal");
		printf("\n 5.PostorderTraversal");
		printf("\n 6.FindPreceedingKey");
		printf("\n 7.DeleteKey");
		printf("\n 8.PrintTree");
		printf("\n 9.Exit\n");

		printf("Enter the option : ");
		scanf("%d",&option);
		if (option==9)
		{
			break;
		}
		switch(option)
		{
			case  1 :

				printf("Enter the key value to search : \n");
				scanf("%d",&item );
				if(search(root,item )!=NULL)
				{
					printf("Found in the tree\n");
				}
				else
				{
					printf("Not found in the tree\n");
				}
				break;

			case  2 :

				printf("Enter the key value to insert : \n");
				scanf("%d",& item);
				insert(item);
				break;

			case  3 :
				
				printf("MinimumKey in the subtree is %d\n",findMinKey(root)->key); 
				break;

			case  4 :

				inorder(root);
				break;

			case  5 :

				postorder(root);
				break;

			case  6 :

				printf("Enter the key value to findPreceedingKey : \n");
				scanf("%d",&item );
				if(search(root,item )==NULL)
				{
					printf("Entered key value is not there in the tree\n");
				}
				else
				{
					temp = findInorderPrecedor(root,item);
					if(temp!=NULL)
					{
						printf("PreceedingKey of %d is %d\n",item,temp->key);
					}
					 
				}
				break;

			case  7 :

				printf("Enter the key value to delete : \n");
				scanf("%d",&item);
				deleteNode(root,item);
				break;

			case  8 :

				printTree(root,0);
				// printf("%d\n",root->key);;
				break;
	
		}
	}
}

node* search(node* root,int key)
{
    if (root == NULL || root->key == key)
    {
       	return root;
    }
    if (root->key < key)
    {
       	return search(root->rightptr,key);
    }
 	else
 	{
    	return search(root->leftptr,key);
	}
}

node* findMinKey(node* root)
{
	node *temp=root;
	while(temp->leftptr != NULL)
	{
		temp=temp->leftptr;
	}
	return temp;
}
node* insert(int key)
{
	node *current=root,*parent=NULL;
	while(current!=NULL)
	{
		if (key == current->key)
		{
			printf("Entered key is already there in the tree\n");
			return NULL;
		}
		if(key < current->key)
		{
			parent = current;
			current = current->leftptr;
		}
		else if(key > current->key)
		{
			parent = current;
			current = current->rightptr;
		}
	}

	node *newnode = (node*)malloc(sizeof(node));

	newnode->key = key;
	newnode->leftptr = NULL;
	newnode->rightptr = NULL;
	newnode->parentptr = NULL;


	if(root == NULL)
	{
		root=newnode;
	}
	if(parent!=NULL)
	{
		if (key < parent->key)
		{
			parent->leftptr=newnode;
			newnode->parentptr=parent;
		}
		else
		{
			parent->rightptr=newnode;
			newnode->parentptr=parent;
		}
	}
	return newnode;
}

void inorder(node* root)
{
	if(root==NULL)
	{
		return;
	}
	inorder(root->leftptr);
	printf("%d ",root->key);
	inorder(root->rightptr);
}

void postorder(node* root)
{
	if(root==NULL)
	{
		return;
	}
	inorder(root->leftptr);
	inorder(root->rightptr);
	printf("%d ",root->key);
}


node* findInorderPrecedor(node* root,int key)
{
	node *current,*parent;
	if(search(root,key)==findMinKey(root))
	{
		printf("Given key is Minimum Key\n");
		return NULL;
	}
	root=search(root,key);
	if(root->leftptr!=NULL)
	{
		current=root->leftptr;
		while(current->rightptr!=NULL)
		{
			current=current->rightptr;
		}
		return current;
	}
	else
	{
		if(root->leftptr == NULL)
		{
			current = root;
			parent = root->parentptr;
			while(current==parent->leftptr && parent!=NULL)
			{
				current=parent;
				parent=parent->parentptr;
			}
			return parent;		
		}
	}
}
void transplant(node *u,node *v)
{
	node *parent;
	parent=u->parentptr;
	if(parent==NULL)
	{
		root=v;
	}
	else if(parent->leftptr==u)
	{
		parent->leftptr=v;
	}
	else parent->rightptr=v;
	if(v!=NULL)
	{
		v->parentptr=parent;
	}
}

void deleteNode(node *root_temp,int key)
{
	if(root_temp==NULL)
	{
		return ;
	}
	if(key == root_temp->key)
	{
		if(root_temp->leftptr==NULL)
		{
			transplant(root_temp,root_temp->rightptr);
		}
		else if(root_temp->rightptr==NULL)
		{
			transplant(root_temp,root_temp->leftptr);
		}
		else
		{
			node *temp = findInorderPrecedor(root_temp,root_temp->key);
			if(temp->parentptr != root_temp)
			{
				transplant(temp,temp->leftptr);
				temp->leftptr = root_temp->leftptr;
				temp->leftptr->parentptr = temp;
			}
			transplant(root_temp,temp);
			temp->rightptr=root_temp->rightptr;
			temp->rightptr->parentptr = temp;
		}
		return;
	}
	if(key < root_temp->key)
	{
		deleteNode(root_temp->leftptr,key);
		return ;
	}
	else if (key > root_temp->key)
	{
		deleteNode(root_temp->rightptr,key);
		return;
	}
	
}

void printTree(node *root_temp,int tab)
{
	
	if (root_temp==NULL)
	{
		return;
	}
	int x=tab;
	tab=tab+1;
	printTree(root_temp->rightptr,tab);
	print_spaces(x*10);
	printf("%d\n\n",root_temp->key);
	printTree(root_temp->leftptr,tab);
	
}

void print_spaces(int spaces)
{
    while(spaces>0)
    {
        printf(" ");
        spaces--;
    }
}

	// insert( 100);
	// insert( 120);
	// insert( 75);
	// insert( 50);
	// insert( 60);
	// insert( 55);
	// insert( 53);
	// insert( 70);
	// insert( 65);
	// insert( 80);
	// insert( 78);
	// insert( 90);
	// insert( 98);	
	// insert( 110);
	// insert( 150);
	// insert(4);
	// insert(3);
	// insert(2);
	// insert(1);
	// insert(5);
	// insert(6);