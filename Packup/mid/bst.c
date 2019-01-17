/*
   Name: Vishnu Teja
   Roll.NO: 111601028
   program: BST
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node{
	int key;
	struct node* rchild;
	struct node* lchild;
	struct node* parent;
}node;

void postorder(node *root);
struct node * search(node *root,int item);
struct node * insert(node *T,int item);
struct node * newnode(int item);
void inorder(node *root);
struct node * findmin(node *T);
void delete(node *root,int item);
struct node * predecessor(node *root,int item);
struct node * findmax(node *T);
void printtree(node *root,int level);

void main()
{
	int i,op,item,flag=0;
	node *root;
	root=NULL;
	// root=insert(root,100);
	
	// 					root=insert(root,120);
	// 					root=insert(root,110);
	// 					root=insert(root,150);
	// 					root=insert(root,75);
	// 					root=insert(root,50);
	// 					root=insert(root,60);
	// 					root=insert(root,55);
	// 					root=insert(root,53);
	// 					root=insert(root,70);
	// 					root=insert(root,65);
	// 					root=insert(root,80);
	// 					root=insert(root,78);
	// 					root=insert(root,90);
	// 					root=insert(root,98);
   while(flag==0)
   {
   	printf("________\n");
	printf("1.Search a key\n2.Insert\n3.Findmin\n4.Inorder\n5.postorder\n6.Predecessor\n7.Delete key \n8.Print tree\n9.Exit\n");
	printf("________\n");
	printf("\nEnter your option\n");
	scanf("%d",&op);

	printf("________\n");
		switch(op)
		{
			case 1: if(root==NULL)
					{
						printf("Tree is empty to be searched\n");
						break;
					}
					printf("Enter item to be searched\n");
					scanf("%d",&item);
					
						if(search(root,item)==NULL)
						{
							printf("Not Found\n");
							break;
						}
						else
						{
							printf("Found\n");
							break;
						}

			case 2: printf("Enter the value to be inserted:\n");
					scanf("%d",&item);
					root=insert(root,item);
					break;
					
			case 3: if(root==NULL)
					{
						printf("Tree is empty\n");
						break;
					}
					
					printf("The Minimum is %d\n",(findmin(root))->key);
					break;

			case 4: if(root==NULL)
					{
						printf("Tree is empty\n");
						break;
					}
					else
					{
						inorder(root);
						break;
					}
			case 5: if(root==NULL)
					{
						printf("Tree is empty\n");
						break;
					}
					else
					{
						postorder(root);
						break;
					}

			case 6: if(root==NULL)
					{
						printf("Tree is empty\n");
						break;
					}
					printf("Enter the key for which predecessor is to be found :\n");
					scanf("%d",&item);
					
					printf("The predecessor of %d is %d\n",item,(predecessor(root,item))->key);
					break;

			case 7: if(root==NULL)
					{
						printf("Tree is empty nothing to delete\n");
						break;
					}
					else
					{
						printf("Enter the value to be deleted:\n");
						scanf("%d",&item);
						delete(root,item);
						break;
					}
			case 8: printtree(root,0);
					break;
			case 9: flag=1;
					break;
			
			default: printf("Invalid Choice\n");
					 break;
		}
   }
}

struct node *search(node *root,int item)
{
	while(root!=NULL)
	{
		if(root->key==item)
			return root;
		else if(root->key>item)
			root=root->lchild;
		else
			root=root->rchild;
	}
	return root;
}


struct node * insert(node *T,int item)
{
	
	if(T==NULL)
		return newnode(item);
	else if(search(T,item)==NULL)
	{
		node *temp;
		if(item<=T->key)
		{
			temp=insert(T->lchild,item);
			T->lchild=temp;
			temp->parent=T;
		}
		else
		{	
			temp=insert(T->rchild,item);
			T->rchild=temp;
			temp->parent=T;
		}
	}
	else
	{
		printf("A duplicate is found\n");
	}	
	return T;
}


struct node * newnode(int item)
{
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->key=item;
	temp->lchild=NULL;
	temp->rchild=NULL;
	temp->parent=NULL;
	return temp;
}	

void inorder(node *root)
{

	if(root!=NULL)
	{
		
		inorder(root->lchild);
		printf("%d\n",root->key);
		inorder(root->rchild);
	}
}

struct node * findmin(node *T)
{
	while(T->lchild!=NULL)
	{
		T=T->lchild;
	}
	
	return T;
}

struct node * findmax(node *T)
{
	while(T->rchild!=NULL)
	{
		T=T->rchild;
	}
	
	return T;
}



void postorder(node *root)
{
	if(root!=NULL)
	{
		postorder(root->lchild);
		postorder(root->rchild);
		printf("%d\n",root->key);
	}
}

// struct node * delete(node *root,int item)
// {
// 	if(root==NULL)
// 		return root;
// 	if(item<root->key)
// 		root->lchild=delete(root->lchild,item);
// 	else if(item>root->key)
// 		root->rchild=delete(root->rchild,item);
	
// else
// {
// 	if(root->lchild==NULL)
// 	{
// 		struct node *temp=root->rchild;
// 		//temp->parent=root->parent;
// 		free(root);
// 		return temp;
// 	}
// 	else if(root->rchild==NULL)
// 	{
// 		struct node *temp=root->lchild;
// 		//temp->parent=root->parent;
// 		free(root);
// 		return temp;
// 	}
	
// 	struct node* temp=findmin(root->rchild);
// 	root->key=temp->key;
// 	root->rchild=delete(root->rchild,temp->key);
//  }
// 	return root;
// }


void printtree(node *root,int level)
{
    int i;
    if(root == NULL )/*Base Case*/
        return;
    else
    {
        printtree(root->rchild, level+1);
        printf("\n");
        for (i=0; i<level; i++)
            printf("    ");
        printf("%d", root->key);
        printtree(root->lchild, level+1);
    }

       printf("\n");

}




void delete(node *root,int item)
{
	node *x;
	node *p;
	node *y;
	x=search(root,item);
	if(x==NULL)
	{
		printf("Entered value is not in the tree\n");
		return;
	}
	if(x->rchild==NULL && x->lchild==NULL)
	{
		p=x->parent;
		if(p==NULL)
		{
			free(x);
			return;
		}
		else
		{
			if(x==p->lchild)
			{
				p->lchild=NULL;
			}
			else if(x==p->rchild)
			{
				p->rchild=NULL;
			}
		}
		free(x);
	}

	if(x->rchild!=NULL && x->lchild==NULL)
	{
		p=x->parent;
		if(p==NULL)
		{
			x->rchild->parent=NULL;
			free(x);
			return;
		}
		else
		{
			if(x==p->lchild)
			{
				p->lchild=x->rchild;
				x->rchild->parent=p;
			}
			else if(x==p->rchild)
			{
				p->rchild=x->rchild;
				x->rchild->parent=p;
			}
		}
	}


	else if(x->lchild!=NULL && x->rchild==NULL)
	{
		p=x->parent;
		if(p==NULL)
		{
			x->lchild->parent=NULL;
			free(x);
			return;
		}
		else
		{
			if(x==p->lchild)
			{
				p->lchild=x->lchild;
				x->lchild->parent=p;
			}
			else if(x==p->rchild)
			{
				p->rchild=x->lchild;
				x->lchild->parent=p;
			}
		}
	}

	else if(x->lchild!=NULL && x->rchild!=NULL)
	{
		int k;
		y=predecessor(root,x->key);
		k=y->key;
		delete(root,k);
		x->key=k;
	}

}


struct node * predecessor(node *root,int item)
{
	 node *temp;
	 while(root!=NULL)
	{
		if(root->key==item)
			break;
		else if(root->key>item)
			root=root->lchild;
		else
			root=root->rchild;
	}
	
	if(root->lchild!=NULL)
	{
		return findmax(root->lchild);
	}
	
	temp=root->parent;
	while(temp!=NULL && root==temp->lchild)
	{
		root=temp;
		temp=temp->parent;
	}
	return temp;

}