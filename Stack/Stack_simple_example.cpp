// Stack_simple_example.cpp 
// Binary,Decimal,Hex and Octal Convert

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 

typedef int Elementtype;
typedef struct Node
{
	Elementtype Element;//数据域  
	struct Node *Next;//链域  
}*Stack, *SNode;
void Pop(Stack S)
{
	SNode Firstcell;
		Firstcell = S->Next;
		S->Next = Firstcell->Next;
		switch (Firstcell->Element){
		case 10: printf("A "); break;
		case 11: printf("B "); break;
		case 12: printf("C "); break;
		case 13: printf("D "); break;
		case 14: printf("E "); break;
		case 15: printf("F "); break;
		default :printf("%d ", Firstcell->Element);
		}
		free(Firstcell);
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
Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(Node));//出个表头
	if (S == NULL) printf("Out of Space!");
	S->Next = NULL;
	//MakeEmpty(S);//清空stack
	return S;
}

void Convert(int num, int sys)
{
	int len = 0;
	Stack S = CreateStack();
	while (num >= sys)
	{
		int reminder = num % sys;
		num = num / sys;//quotient 商(整除)
		Push(reminder, S);
		len++;
	}
	Push(num, S);//最后余数压入
	for (int i = 1; i <= len+1; i++)//len+1
		Pop(S);
}

void main()
{
	int s,sys;
	printf("please input a Decimal number.\n");
	scanf_s("%d", &s);
	printf("please choose a system: 2 or 8 or 16 is preferred.\n");
	scanf_s("%d", &sys);
	Convert(s, sys);

	system("pause");
}