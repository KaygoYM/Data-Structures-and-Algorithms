// Hashsepchain.h
// author：KAI
#ifndef _HashSep_H  

typedef int ElementType;
typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

Index Hash(const int Key, int TableSize);

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);
/* Routines such as Delete and MakeEmpty are omitted */

typedef Position List;

Index Hash(const int Key, int TableSize)//hash function
{
	return Key % TableSize;
}

struct ListNode
{
	ElementType Element;
	Position Next;
};

/* List *TheList will be an array of lists,allocated later */
/* The lists use headers (for simplicity), */
/* though this wastes space */
struct HashTbl
{
	int TableSize;
	List *TheLists;
};
#endif /* _HashSep_H */  
