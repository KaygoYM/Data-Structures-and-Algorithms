// Stack_basic.cpp : 定义控制台应用程序的入口点。
// author: KAI

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 



typedef int Elementtype;
typedef struct Node
{
	Elementtype Element;//数据域  
	struct Node *Next;//链域  
}*Stack,*SNode;

int IsEmpty(Stack S){ return S->Next == NULL; }
void Pop(Stack S)
{
	SNode Firstcell;
	if (IsEmpty(S)) printf("The stack is empty!");

	else
	{
		Firstcell = S->Next;
		S->Next = Firstcell->Next;
		printf("The element of the poped is %d\n", Firstcell->Element);
		free(Firstcell);
	}
}
void Push(Elementtype x, Stack S)
{
	SNode Tmpcell;
	Tmpcell = (SNode)malloc(sizeof(Node));
	if (Tmpcell == NULL) printf("Out of Space!");
	Tmpcell->Element = x;
	Tmpcell->Next = S->Next;
	S->Next = Tmpcell;
	//头插
}
void MakeEmpty(Stack S)
{
	if (S == NULL) printf("Must Use CreateStack first!");
	while (!IsEmpty(S)) Pop(S);
}
Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(Node));//出个表头
	if (S == NULL) printf("Out of Space!");
	S->Next = NULL;
	MakeEmpty(S);//清空stack
	return S;
}

Elementtype Top(Stack S)
{
	if (!IsEmpty(S))
		return S->Next->Element;
	else
	{
		printf("Stack is empty"); return 0;
	}
}
void Print(Stack L){
	SNode P = L->Next;
	if (IsEmpty(L))   //链表为空
		printf("PrintList is excuted，but it is empty.\n");
	else
	{
		while (P != NULL)
		{
			printf("%d ", P->Element);
			P = P->Next;
		}
		printf("\n");
	}
}
int Getlength(Stack L)
{
	if (IsEmpty(L)) return 0;
	SNode P = L;
	int counter = 0;
	do{
		counter++;
		P = P->Next;
	} while (P != NULL);
	return counter-1;
}

void main()
{
	int length = 6;
	Stack S=CreateStack();
	for (int i = 1; i <= length; i++)
		Push(i, S);
	Print(S);
	printf("Now the top of S is %d\n",Top(S));
	Pop(S); Pop(S);
	printf("Now the top of S is %d\n", Top(S));
	int now_length = Getlength(S);
	for (int i = 1; i <= now_length; i++)
		Pop(S);
	Top(S); Print(S);
	system("pause");
}
