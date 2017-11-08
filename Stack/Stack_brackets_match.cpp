// Stack_brackets_match.cpp : 
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h>
#include "string.h"

typedef char Elementtype;
typedef struct Node
{
	Elementtype Element;//������  
	struct Node *Next;//����  
}*Stack, *SNode;

Elementtype Pop(Stack S)
{
	SNode Firstcell;
	if (S->Next == NULL) return NULL;//if stack is empty
		Firstcell = S->Next;
		S->Next = Firstcell->Next;
		Elementtype x = Firstcell->Element;
		//printf("The element of the poped is %d\n", Firstcell->Element);
		free(Firstcell);
		return x;
}
void Push(Elementtype x, Stack S)
{
	SNode Tmpcell;
	Tmpcell = (SNode)malloc(sizeof(Node));
	if (Tmpcell == NULL) printf("Out of Space!");
	Tmpcell->Element = x;
	Tmpcell->Next = S->Next;
	S->Next = Tmpcell;
	//ͷ��
}
Stack CreateStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(Node));//������ͷ
	if (S == NULL) printf("Out of Space!");
	S->Next = NULL;
	return S;
}
int Check(char str[])
{
	Stack charstack = CreateStack();
	for (int i = 0; i < strlen(str); i++)//index begins with 0
	{
		switch (str[i])
		{
		case '(':
		case '[':
		case '{':
		case '<':
			Push(str[i], charstack);
			break;
		case ')':
			if (Pop(charstack) != '(') return 0;
			else break;
		case ']':
			if (Pop(charstack) != '[') return 0;
			else break;
		case '}':
			if (Pop(charstack) != '{') return 0;
			else break;
		case '>':
			if (Pop(charstack) != '<') return 0;
			else break;
		default:continue;
		}
	}
	return 1;//ʲô���Ŷ�û�б��ʽҲ�ǶԵ�

}
void main()
{	char ch[200];
	printf("please input your string!\n");
	scanf_s("%s", &ch,200);
	if (Check(ch)) printf("yes,correct!\n");
	else printf("no,wrong!\n");
	system("pause");
}