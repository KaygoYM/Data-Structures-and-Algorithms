// Hashsepchain.cpp :
// author:KAI
#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <malloc.h> 
#include "Hashsepchain.h"
#define MinTableSize (5) 

static int NextPrime(int N)//±ä³ÉËØÊý
{
	int i;

	if (N % 2 == 0)
		N++;
	for (;; N += 2)
	{
		for (i = 3; i * i <= N; i += 2)
		if (N % i == 0)
			goto ContOuter;  /* Sorry about this! */
		return N;
	ContOuter:;
	}
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if (TableSize < MinTableSize)
	{
		printf("Table size too small");
		return NULL;
	}

	/* Allocate table */
	H =(HashTable) malloc(sizeof(struct HashTbl));
	if (H == NULL)
		printf("Out of space!!!");

	H->TableSize = NextPrime(TableSize);

	/* Allocate array of lists */
	H->TheLists =(List*)malloc(sizeof(List)* H->TableSize);
	if (H->TheLists == NULL)
		printf("Out of space!!!");

	/* Allocate list headers */
	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		if (H->TheLists[i] == NULL)
			printf("Out of space!!!");
		else
			H->TheLists[i]->Next = NULL;
	}

	return H;
}

Position Find(ElementType Key, HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(Key, H->TableSize)];
	P = L->Next;

	while (P != NULL && P->Element != Key)
		/* Probably need strcmp!! */
		P = P->Next;

	return P;
}

void Insert(ElementType Key, HashTable H)
{
	Position Pos, NewCell;
	List L;

	Pos = Find(Key, H);
	if (Pos == NULL) /* Key is not found */
	{
		NewCell = (List)malloc(sizeof(struct ListNode));
		if (NewCell == NULL)
			printf("Out of space!!!");
		else
		{
			L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->Element = Key; /* Probably need strcpy!! */
			L->Next = NewCell;
		}
	}
}
void DestroyTable(HashTable H)
{
	int i;

	for (i = 0; i < H->TableSize; i++)
	{
		Position P = H->TheLists[i];
		Position Tmp;

		while (P != NULL)
		{
			Tmp = P->Next;
			free(P);
			P = Tmp;
		}
	}

	free(H->TheLists);
	free(H);
	printf("Destroy the Hash table successfully.\n");
}
ElementType Retrieve(Position P)
{
	return P->Element;
}


void main()
{
	HashTable H = InitializeTable(10);
	int i;
	printf("HashTable:\n");
	for (i = 0; i < 10; i++)
	{
		Insert(i * i, H);
		printf("%d:%d\n", i*i, Hash(i * i, 10));
	}
	int x = 81;
	printf("The position of %d is %0x\n",x,Find(x, H));
	DestroyTable(H);
	system("pause");
	
}
