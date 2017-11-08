// Linkedlist.cpp : 定义控制台应用程序的入口点。
// author:KAI

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include <malloc.h> 

typedef int Elementtype;
//typedef struct Node *PtrToNode;//定义节点指针 
typedef struct Node
{
	Elementtype Element;//数据域  
	struct Node *Next;//链域  
}*List,*Position;

//节点的定义  
//typedef PtrToNode Position;//节点
//typedef PtrToNode List;//表头

List CreateList(int size)
{
	Position p,e = NULL;
	int i;
	List L= (List)malloc(sizeof(Node));//申请表头(=表)的空间
	if (L == NULL){
		printf("Fail to create header.\n");
		return NULL;
	}
	L->Next = NULL;
	for (i = 1; i <= size; i++)
	{
		p = (Position)malloc(sizeof(Node));
		if (p == NULL){
			printf("Fail to create Node p.\n");
			return NULL;
		}
		printf("Please input the element(int) in the list!\n");
		scanf_s("%d", &(p->Element), 5);
		//头插
		//p->Next = L->Next;
		//L->Next = p;
		//尾插
		if (i == 1)
			L->Next = p;
		else
			e->Next = p; //e始终指向末尾
		e = p;
		e->Next = NULL;
	}
	printf("Create List successfully!\n");
	return L;
}

int DeleteList(List L)//make empty
{
	Position P,Q;
	P = L->Next;
	L->Next = NULL;//留下表头

	while (P != NULL)
	{
		Q = P->Next;
		free(P);
		P = Q;
	}
	printf("Delete List successfully!\n");
	return 1;
}

void PrintList(List L){
	Position P = L->Next;
	if (P==NULL)   //链表为空
		printf("PrintList is excuted，but it is empty.\n");
	else
	{	
		while (P!=NULL)
			{
				printf("%d ", P->Element);
				P = P->Next;
			}
			printf("\n");
	}
}

int IsEmpty(List header)
{
	if (header->Next == NULL){
		printf("The list is empty.\n");
		return 1;
	}
	else
	{
		printf("The list is not empty.\n");
		return -1;
	}
}

int IsLast(List header, Position P)
{
	if (P->Next == NULL){
		printf("Position %d is last.\n",P->Element);
		return 1;
	}
	else
	{
		printf("Position %d is not last.\n",P->Element);
		return 0;
	}
}

Position Find(Elementtype x, List header){
	Position P;

	P = header->Next;
	while (P != NULL && P->Element != x)
		P = P->Next;
	printf("the %d address is 0x%x\n", x, &(P->Element));
	return P;

}

Position FindPrevious(Elementtype x, List header){
	Position P;

	P = header;
	while (P->Next != NULL && P->Next->Element != x)
		P = P->Next;
	return P;
}

void Insert(Elementtype x, List L, Position P)
{
	Position Tmpcell;
	Tmpcell =(Position)malloc(sizeof(Node));
	if (Tmpcell == NULL)
		printf("Out of Space");
	Tmpcell->Element = x;
	Tmpcell->Next = P->Next;
	P->Next = Tmpcell;
}

void Delete(Elementtype x, List L)
{
	Position P = FindPrevious(x, L);
	Position Tmp=P->Next;

	if (!IsLast(Tmp, L))
		P->Next = Tmp->Next;
	else P->Next == NULL;
	free(Tmp);
	
}


void main(){

	List Test_List = NULL;//表头
	int size = 5;
	bool flag = true;
	Elementtype num,num2;
	char s;
	Test_List=CreateList(size);       //链表初始化
	PrintList(Test_List);
	while (flag){
		printf("choose function:\n");
		printf("0.Print \t 1.Find \t 2.Insert\t 3.Delete \t 4.Delete whole \n");
		printf("print # to quit\n");
		scanf_s("%c", &s,20);
		switch (s){
		case '0':{
					 IsEmpty(Test_List);
					 PrintList(Test_List);
					 break; }
		case '1':{
					 printf("what number will you want to find the position?\n");
					 scanf_s("%d", &num);
					 Position Pos = Find(num, Test_List);
					 IsLast(Test_List, Pos);
					 break; }
		case '2':{
					 printf("what number will you insert and after which number?\n");
					 scanf_s("%d %d", &num,&num2);
					 Insert(num, Test_List, Find(num2, Test_List));
					 PrintList(Test_List);
					 break; }
		case '3':{
					 printf("what number will you delete?\n");
					 scanf_s("%d", &num);
					 Delete(num, Test_List);
					 PrintList(Test_List);
					 break; }
		case '4':{
					 DeleteList(Test_List);
					 IsEmpty(Test_List);
					 break; }
		case '#':{
					 flag = false;
					 break; }
		}

	}
	system("pause");
}
