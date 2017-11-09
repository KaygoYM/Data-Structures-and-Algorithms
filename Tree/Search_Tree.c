// Search_Tree.cpp : 
// author:KAI
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 



typedef int Elementtype;
typedef struct Node
{
	Elementtype key;//data
	struct Node *Left;//left child
	struct Node *Right;//right child
	//struct Node *Parent;//父结点
}*STree, *Position;

STree MakeEmpty(STree T)//make tree empty
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(Elementtype x, STree T)//find the particular key
{
	if (T == NULL) return NULL;
	if (x < T->key)
		return Find(x, T->Left);
	else if (x>T->key)
		return Find(x, T->Right);
	else
	{
		printf("the detected position is %0x\n", T);
		printf("the detected key is %d\n", T->key);
		return T;
	}
}

Position Findmin(STree T)
{
	if (T == NULL)	return NULL;
	else if (T->Left == NULL) return T;
	else return(Findmin(T->Left));
}

Position Findmax(STree T)
{
	if (T != NULL){
		while (T->Right != NULL)
			T = T->Right;
	}
	return T;
}

void Preorder_bstree(STree tree)
{                     
	if (tree != NULL)
	{
		printf("%d ", tree->key);
		Preorder_bstree(tree->Left);
		Preorder_bstree(tree->Right);
	}
}

void Inorder_bstree(STree tree)
{
	if (tree != NULL)
	{
		Inorder_bstree(tree->Left);
		printf("%d ", tree->key);
		Inorder_bstree(tree->Right);
	}
}

void Postorder_bstree(STree tree)
{
	if (tree != NULL)
	{
		Postorder_bstree(tree->Left);
		Postorder_bstree(tree->Right);
		printf("%d ", tree->key);
	}
}

STree Insert(Elementtype x, STree T)
{
	if (T == NULL)
	{
		T = (STree)malloc(sizeof(Node));
		if (T == NULL)
			printf("Out of Space!");
		else
		{
			T->key = x;
			T->Left = T->Right = NULL;
		}
	}
	else if (x < T->key)
		T->Left = Insert(x, T->Left);
	else if (x>T->key)
		T->Right = Insert(x, T->Right);
	return T;


}

STree Delete(Elementtype x, STree T)
{
	Position P;
	if (T == NULL) return NULL;
	else if (x < T->key)
		T->Left = Delete(x, T->Left);
	else if (x > T->key)
		T->Right = Delete(x, T->Right);
	//found the key to be deleted
	else if (T->Left && T->Right)//two children
	{
		P = Findmin(T->Right);//the min key that bigger than x
		T->key = P->key;
		T->Right = Delete(T->key, T->Right);
	}
	else //one or no child
	{
		P = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(P);
	}
	return T;
}

void main()
{
	STree T=NULL;
	T = MakeEmpty(T);
	int a[7];//7个0-9的数随机序列
	for (int i = 0; i <= 6; i++)
	{
		a[i] = rand() % 10;
		T = Insert(a[i], T);
	}
	printf("Post: "); Postorder_bstree(T); printf("\n");
	printf("Pre: "); Preorder_bstree(T); printf("\n");
	printf("In: ");	Inorder_bstree(T); printf("\n");
	int x = a[rand() % 6];
	Position X = Find(x, T);
	T = Delete(x, T);
	printf("After delete(post): "); Postorder_bstree(T);
	system("pause");
}
