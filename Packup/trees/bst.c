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


void deleteNode(node **root,int key);
node* search(node* root,int key);
void inorder(node* root);
node* insert(node **root,int key);
void postorder(node* root);
node* findInorderPrecedor(node* root,int key);
node* findMinKey(node* root);
void printTree(node* root,int tab);
void print_spaces(int spaces);

void main()
{
	int  item,option;
	node *root=NULL,*temp=NULL;
	// insert(&root, 100);
	// insert(&root, 120);
	// insert(&root, 75);
	// insert(&root, 50);
	// insert(&root, 60);
	// insert(&root, 55);
	// insert(&root, 53);
	// insert(&root, 70);
	// insert(&root, 65);
	// insert(&root, 80);
	// insert(&root, 78);
	// insert(&root, 90);
	// insert(&root, 98);	
	// insert(&root, 110);
	// insert(&root, 150);
	insert(&root,3);
	insert(&root,2);
	insert(&root,1);
	insert(&root,4);
	insert(&root,5);
	insert(&root,6);
	
	
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
				insert(&root,item);
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
				deleteNode(&root,item);
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
node* insert(node **root,int key)
{
	node *current=*root,*parent=NULL;
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


	if(*root == NULL)
	{
		*root=newnode;
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

void deleteNode(node **root,int key)
{
	node *temp;
	if(*root==NULL)
	{
		return ;
	}
	if (key == (*root)->key)
	{
		if((*root)->leftptr==NULL || (*root)->rightptr==NULL)//one child or no child
		{
			if((*root)->parentptr == NULL)
			{
				node *temp1=*root;
				if((*root)->leftptr==NULL)
				{
					*root=(*root)->rightptr;	
				}
				else if((*root)->rightptr==NULL)
				{
					*root=(*root)->leftptr;
				}				
				(*root)->parentptr=NULL;
				free(temp1);
				return ;
			}

			temp=(*root);
			if(key < (*root)->parentptr->key)
			{
				if((*root)->leftptr==NULL )
				{
					(*root)->parentptr->leftptr=(*root)->rightptr;
				}
				else if((*root)->rightptr==NULL)
				{
					(*root)->parentptr->leftptr=(*root)->leftptr;
				}				
			}
			else
			{
				if((*root)->leftptr==NULL )
				{
					(*root)->parentptr->rightptr=(*root)->rightptr;
				}
				else if ((*root)->rightptr==NULL)
				{
					(*root)->parentptr->rightptr=(*root)->leftptr;
				}
			}
			
			free(temp);
			return ;
		}
		if((*root)->leftptr!=NULL && (*root)->rightptr!=NULL)//2 children
		{
			temp=findInorderPrecedor(*root,(*root)->key);
			int y=temp->key;
			deleteNode(&((*root)->leftptr),y);	
			(*root)->key=y;
		}

	}
	if(key < (*root)->key)
	{
		deleteNode(&((*root)->leftptr),key);
		return ;
		
	}
	else if (key > (*root)->key)
	{
		deleteNode(&((*root)->rightptr),key);
		return;
	}
}

void printTree(node *root,int tab)
{
	
	if (root==NULL)
	{
		return;
	}
	int x=tab;
	tab=tab+1;
	printTree(root->rightptr,tab);
	print_spaces(x*10);
	printf("%d\n\n",root->key);
	printTree(root->leftptr,tab);
	
}

void print_spaces(int spaces)
{
    while(spaces>0)
    {
        printf(" ");
        spaces--;
    }
}


// if(search(root,1)!=NULL)
	// {
	// 	printf("Found in the tree\n");
	// }
	// else
	// {
	// 	printf("Not found in the tree\n");
	// }
	// deleteNode(&root,2);
	// insert(&root,7);
	// if(search(root,2)!=NULL)
	// {
	// 	printf("Found in the tree\n");
	// }
	// else
	// {
	// 	printf("Not found in the tree\n");
	// }
	// insert(&root,4);
	// insert(&root,13);
	// insert(&root,2);
	// if(search(root,3)!=NULL)
	// {
	// 	printf("Found in the tree\n");
	// }
	// else
	// {
	// 	printf("Not found in the tree\n");
	// }
	// // printf("Enter the key value to findPreceedingKey : \n");
	// // scanf("%d",& );
	// if(search(root,13)==NULL)
	// {
	// 	printf("Entered key value is not there in the tree\n");
	// }
	// else if(findInorderPrecedor(root,13)!=NULL)
	// {
	// 	printf("PreceedingKey of %d is %d\n", ,findInorderPrecedor(root,13)->key); 
	// }
	// //printTree(root);
	// deleteNode(&root,7);
	// if(search(root,1)!=NULL)
	// {
	// 	printf("Found in the tree\n");
	// }
	// else
	// {
	// 	printf("Not found in the tree\n");
	// }
	// if(search(root,2)!=NULL)
	// {
	// 	printf("Found in the tree\n");
	// }
	// else
	// {
	// 	printf("Not found in the tree\n");
	// }
	// inorder(root);
	//postorder(root);
