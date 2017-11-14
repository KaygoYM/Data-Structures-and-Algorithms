// AVL_Tree.cpp : 
// author:KAI
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 



typedef int Elementtype;
typedef struct Node
{
	Elementtype key;//data
	int height;//height
	struct Node *Left;//left child
	struct Node *Right;//right child
}*AVLTree, *Position;

static int Height(Position P)
{
	if (P == NULL) return -1;
	else return P->height;
}

#define MAX(a, b)    ((a) > (b) ? (a) : (b))


static Position Left_Left_rotation(AVLTree k2)
{
	AVLTree k1;

	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;

	k2->height = MAX(Height(k2->Left), Height(k2->Right)) + 1;
	k1->height = MAX(Height(k1->Left), k2->height) + 1;

	return k1;
}

static Position Right_Right_rotation(AVLTree k1)
{
	AVLTree k2;

	k2 = k1->Right;
	k1->Right = k2->Left;
	k2->Left = k1;

	k1->height = MAX(Height(k1->Left), Height(k1->Right)) + 1;
	k2->height = MAX(Height(k2->Right), k1->height) + 1;

	return k2;
}

static Position Left_Right_rotation(AVLTree k3)
{
	k3->Left = Right_Right_rotation(k3->Left);

	return Left_Left_rotation(k3);
}

static Position Right_Left_rotation(AVLTree k1)
{
	k1->Right = Left_Left_rotation(k1->Right);

	return Right_Right_rotation(k1);
}

AVLTree Insert(Elementtype x, AVLTree T)
{
	if (T == NULL)
	{//create and return a one-node tree
		T = (AVLTree)malloc(sizeof(Node));
		if (T == NULL)
			printf("Out of space!");
		else
		{
			T->key = x; T->height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (x < T->key)// Ӧ�ý�x���뵽"tree��������"�����
	{
		T->Left = Insert(x, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
		if (x < T->Left->key)
			T = Left_Left_rotation(T);
		else
			T = Left_Right_rotation(T);
	}
	else if (x>T->key)// Ӧ�ý�key���뵽"tree��������"�����
	{
		T->Right = Insert(x, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
		if (x > T->Right->key)
			T = Right_Right_rotation(T);
		else
			T = Right_Left_rotation(T);
	}
//else x is in the tree already, we will do nothing
	T->height = MAX(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

void Preorder(AVLTree tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->key);
		Preorder(tree->Left);
		Preorder(tree->Right);
	}
}

void Inorder(AVLTree tree)
{
	if (tree != NULL)
	{
		Inorder(tree->Left);
		printf("%d ", tree->key);
		Inorder(tree->Right);
	}
}

void Postorder(AVLTree tree)
{
	if (tree != NULL)
	{
		Postorder(tree->Left);
		Postorder(tree->Right);
		printf("%d ", tree->key);
	}
}

/*
* ��ӡ"AVL��"
*
* tree       -- AVL���Ľڵ�
* key        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
void print_avltree(AVLTree tree, Elementtype key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�  
			printf("%2d is root\n", tree->key, key);
		else                // tree�Ƿ�֧�ڵ�  
			printf("%2d is %2d's %6s child\n", tree->key, key, direction == 1 ? "right" : "left");

		print_avltree(tree->Left, tree->key, -1);
		print_avltree(tree->Right, tree->key, 1);
	}
}

static int arr[] = { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )  

void main()
{
	int i, ilen;
	AVLTree root = NULL;

	printf("== �߶�: %d\n", Height(root));
	printf("== �������: ");
	ilen = TBL_SIZE(arr);
	for (i = 0; i < ilen; i++)
	{
		printf("%d ", arr[i]);
		root = Insert(arr[i], root);
	}

	printf("\n== ǰ�����: ");
	Preorder(root);

	printf("\n== �������: ");
	Inorder(root);

	printf("\n== �������: ");
	Postorder(root);
	printf("\n");

	printf("== �߶�: %d\n", Height(root));
	printf("== ������ϸ��Ϣ: \n");
	print_avltree(root, root->key, 0);
	system("pause");
}