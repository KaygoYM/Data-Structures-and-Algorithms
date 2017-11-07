// Josephu circle.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 

typedef struct Node
{
	int Element;//������  
	struct Node *Next;//����  
}*List, *Position;
//�б�ͷ�ĵ���ѭ������
List CreateList(int size)
{
	Position p, e = NULL;
	int i = 1;
	List L = (List)malloc(sizeof(Node));//�����һ���Ŀռ�
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
		//ͷ��
		//p->Next = L->Next;
		//L->Next = p;
		//β��
		if (i == 2)
			L->Next = p;
		else
			e->Next = p; //eʼ��ָ��ĩβ
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
	if (P == NULL)   //����Ϊ��
		printf("PrintList is excuted��but it is empty.\n");
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
		for (int i = 1; i <= len; i++) //i��¼ɾ������index
		{
			for (int k = 1; k < rule-1; k++)//����
			{
				P = P->Next;
			}
			Position Tmp = P->Next;//ɾ������rule���������
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
