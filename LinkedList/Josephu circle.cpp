// Josephu circle.cpp : 
//
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 

typedef struct Node
{
	int Element;//数据域  
	struct Node *Next;//链域  
}*List, *Position;
//有表头的单向循环链表
List CreateList(int size)
{
	Position p, e = NULL;
	int i = 1;
	List L = (List)malloc(sizeof(Node));//申请第一个的空间
	if (L == NULL){
		printf("Fail to create header.\n");
		return NULL;
	}
	L->Element = 1;
	L->Next = NULL;
	for (i = 2; i <= size; i++)
	{
		p = (Position)malloc(sizeof(Node));
		if (p == NULL){
			printf("Fail to create Node p.\n");
			return NULL;
		}
		p->Element=i;
		//头插
		//p->Next = L->Next;
		//L->Next = p;
		//尾插
		if (i == 2)
			L->Next = p;
		else
			e->Next = p; //e始终指向末尾
		e = p;
		e->Next = L;
	}
	return L;
}

int getlength(List L)
{
	Position P = L;
	int counter = 0;
	do{ 
		counter++; 
		P = P->Next;
	} while (P != L);
	return counter;
}

void PrintList(List L){
	Position P = L;
	if (P == NULL)   //链表为空
		printf("PrintList is excuted，but it is empty.\n");
	else
	{
		do{
			printf("%d ", P->Element);
			P = P->Next;
		} while (P != L);
	}
		printf("\n");
	
}


void Josbegin(List J, int rule)
{
	Position P = J;
	int len = getlength(J);
		for (int i = 1; i <= len; i++) //i记录删除的人index
		{
			for (int k = 1; k < rule-1; k++)//报数
			{
				P = P->Next;
			}
			Position Tmp = P->Next;//删除报到rule这个数的人
			P->Next = Tmp->Next;
			printf("%d\n", Tmp->Element);
			free(Tmp);
			P = P->Next;
		}
}


void main()
{   
	int length = 15;
	List Jos = CreateList(length);
	PrintList(Jos);
    Josbegin(Jos, 4);
	//PrintList(Jos);
	system("pause");

}
