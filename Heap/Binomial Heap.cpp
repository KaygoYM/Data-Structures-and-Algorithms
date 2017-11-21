// Binomial Heap.cpp :
// �����
#include"stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Binomial_Heap.h"

#define swap(a,b) (a^=b,b^=a,a^=b)

/*
* ���ң��ڶ�����в��Ҽ�ֵΪkey�Ľڵ�
*/
BinomialNode* binomial_search(BinomialHeap heap, Type key)
{
	BinomialNode *child;
	BinomialNode *parent = heap;

	parent = heap;
	while (parent != NULL)
	{
		if (parent->key == key)
			return parent;
		else
		{
			if ((child = binomial_search(parent->child, key)) != NULL)
				return child;
			parent = parent->next;
		}
	}

	return NULL;
}

/*
* ��ȡ������е���С���ڵ�(*y)
*
* ����˵����
*     heap    -- �����
*     prev_y  -- [�������]��С���ڵ�y��ǰһ�����ڵ�
*     y       -- [�������]��С���ڵ�
*/
static void _binomial_minimum(BinomialHeap heap,
	BinomialNode **prev_y, BinomialNode **y)
{
	BinomialNode *x, *prev_x;    // x�����������ĵ�ǰ�ڵ�

	if (heap == NULL)
		return;

	prev_x = heap;
	x = heap->next;
	*prev_y = NULL;
	*y = heap;
	// �ҵ���С�ڵ�
	while (x != NULL) {
		if (x->key < (*y)->key) {
			*y = x;
			*prev_y = prev_x;
		}
		prev_x = x;
		x = x->next;
	}
}

BinomialNode* binomial_minimum(BinomialHeap heap)
{
	BinomialNode *prev_y, *y;

	_binomial_minimum(heap, &prev_y, &y);

	return y;
}

/*
* �ϲ���������ѣ���child�ϲ���heap��
*/
static void binomial_link(BinomialHeap child, BinomialHeap heap)
{
	child->parent = heap;
	child->next = heap->child;
	heap->child = child;
	heap->degree++;
}

/*
* ��h1, h2�еĸ���ϲ���һ���������������������غϲ���ĸ��ڵ�
*/
static BinomialNode* binomial_merge(BinomialHeap h1, BinomialHeap h2)
{
	BinomialNode* head = NULL; //heapΪָ���¶Ѹ����
	BinomialNode** pos = &head;

	while (h1 && h2)
	{
		if (h1->degree < h2->degree)
		{
			*pos = h1;
			h1 = h1->next;
		}
		else
		{
			*pos = h2;
			h2 = h2->next;
		}
		pos = &(*pos)->next;
	}
	if (h1)
		*pos = h1;
	else
		*pos = h2;

	return head;
}

/*
* �ϲ�����ѣ���h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
*/
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2)
{
	BinomialNode *heap;
	BinomialNode *prev_x, *x, *next_x;

	// ��h1, h2�еĸ���ϲ���һ������������������heap
	heap = binomial_merge(h1, h2);
	if (heap == NULL)
		return NULL;

	prev_x = NULL;
	x = heap;
	next_x = x->next;

	while (next_x != NULL)
	{
		if ((x->degree != next_x->degree)
			|| ((next_x->next != NULL) && (next_x->degree == next_x->next->degree)))
		{
			// Case 1: x->degree != next_x->degree
			// Case 2: x->degree == next_x->degree == next_x->next->degree
			prev_x = x;
			x = next_x;
		}
		else if (x->key <= next_x->key)
		{
			// Case 3: x->degree == next_x->degree != next_x->next->degree
			//      && x->key    <= next_x->key
			x->next = next_x->next;
			binomial_link(next_x, x);
		}
		else
		{
			// Case 4: x->degree == next_x->degree != next_x->next->degree
			//      && x->key    >  next_x->key
			if (prev_x == NULL)
			{
				heap = next_x;
			}
			else
			{
				prev_x->next = next_x;
			}
			binomial_link(x, next_x);
			x = next_x;
		}
		next_x = x->next;
	}

	return heap;
}

/*
* �½�����ѽڵ�
*/
static BinomialNode* make_binomial_node(Type key)
{
	BinomialNode* node;

	node = (BinomialNode*)malloc(sizeof(BinomialNode));
	if (node == NULL)
	{
		printf("malloc BinomialNode failed!\n");
		return NULL;
	}

	node->key = key;
	node->degree = 0;
	node->parent = NULL;
	node->child = NULL;
	node->next = NULL;

	return node;
}

/*
* �½�key��Ӧ�Ľڵ㣬��������뵽������С�
*
* ����˵����
*     heap -- ԭʼ�Ķ�������
*     key -- ��ֵ
* ����ֵ��
*     ����key֮��Ķ�����
*/
BinomialNode* binomial_insert(BinomialHeap heap, Type key)
{
	BinomialNode* node;

	if (binomial_search(heap, key) != NULL)
	{
		printf("insert failed: the key(%d) is existed already!\n", key);
		return heap;
	}

	node = make_binomial_node(key);
	if (node == NULL)
		return heap;

	return binomial_union(heap, node);
}

/*
* ��ת�����heap
*/
static BinomialNode* binomial_reverse(BinomialNode* heap)
{
	BinomialNode* next;
	BinomialNode* tail = NULL;

	if (!heap)
		return heap;

	heap->parent = NULL;
	while (heap->next)
	{
		next = heap->next;
		heap->next = tail;
		tail = heap;
		heap = next;
		heap->parent = NULL;
	}
	heap->next = tail;

	return heap;
}

/*
* �Ƴ���С�ڵ㣬�������Ƴ��ڵ��Ķ����
*/
BinomialNode* binomial_extract_minimum(BinomialHeap heap)
{
	BinomialNode *y, *prev_y;    // y����С�ڵ�

	if (heap == NULL)
		return heap;

	// �ҵ�"��С�ڵ��y"��"����ǰһ�����ڵ�prev_y"
	_binomial_minimum(heap, &prev_y, &y);

	if (prev_y == NULL)    // heap�ĸ��ڵ������С���ڵ�
		heap = heap->next;
	else                // heap�ĸ��ڵ㲻����С���ڵ�
		prev_y->next = y->next;

	// ��ת��С�ڵ�����ӣ��õ���С��child��
	// ��������ʹ����С�ڵ����ڶ������ĺ����Ƕ����������Ϊһ�ö����Ķ�����(��������С�ڵ�)
	BinomialNode* child = binomial_reverse(y->child);
	// ��"ɾ����С�ڵ�Ķ����child"��"heap"���кϲ���
	heap = binomial_union(heap, child);

	// ɾ����С�ڵ�
	free(y);

	return heap;
}

/*
* ���ٹؼ��ֵ�ֵ���������heap�еĽڵ�node�ļ�ֵ��СΪkey��
*/
static void binomial_decrease_key(BinomialHeap heap, BinomialNode *node, Type key)
{
	if ((key >= node->key) || (binomial_search(heap, key) != NULL))
	{
		printf("decrease failed: the new key(%d) is existed already, \
			                   or is no smaller than current key(%d)\n", key, node->key);
		return;
	}
	node->key = key;

	BinomialNode *child, *parent;
	child = node;
	parent = node->parent;
	while (parent != NULL && child->key < parent->key)
	{
		swap(parent->key, child->key);
		child = parent;
		parent = child->parent;
	}
}

/*
* ���ӹؼ��ֵ�ֵ���������heap�еĽڵ�node�ļ�ֵ����Ϊkey��
*/
static void binomial_increase_key(BinomialHeap heap, BinomialNode *node, Type key)
{
	if ((key <= node->key) || (binomial_search(heap, key) != NULL))
	{
		printf("increase failed: the new key(%d) is existed already, \
			                   or is no greater than current key(%d)\n", key, node->key);
		return;
	}
	node->key = key;

	BinomialNode *cur, *child, *least;
	cur = node;
	child = cur->child;
	while (child != NULL)
	{
		if (cur->key > child->key)
		{
			// ���"��ǰ�ڵ�" < "��������"��
			// ����"���ĺ�����(���� �� ���ӵ��ֵ�)"�У��ҳ���С�Ľڵ㣻
			// Ȼ��"��С�ڵ��ֵ" �� "��ǰ�ڵ��ֵ"���л���
			least = child;
			while (child->next != NULL)
			{
				if (least->key > child->next->key)
				{
					least = child->next;
				}
				child = child->next;
			}
			// ������С�ڵ�͵�ǰ�ڵ��ֵ
			swap(least->key, cur->key);

			// ��������֮���ٶ�"ԭ��С�ڵ�"���е�����ʹ��������С�ѵ����ʣ����ڵ� <= �ӽڵ�
			cur = least;
			child = cur->child;
		}
		else
		{
			child = child->next;
		}
	}
}

/*
* ���¶����heap�Ľڵ�node�ļ�ֵΪkey
*/
static void binomial_update_key(BinomialHeap heap, BinomialNode* node, Type key)
{
	if (node == NULL)
		return;

	if (key < node->key)
		binomial_decrease_key(heap, node, key);
	else if (key > node->key)
		binomial_increase_key(heap, node, key);
	else
		printf("No need to update!!!\n");
}

/*
* �������heap�ļ�ֵoldkey����Ϊnewkey
*/
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey)
{
	BinomialNode *node;

	node = binomial_search(heap, oldkey);
	if (node != NULL)
		binomial_update_key(heap, node, newkey);
}

/*
* ɾ���ڵ㣺ɾ����ֵΪkey�Ľڵ㣬������ɾ���ڵ��Ķ�����
*/
BinomialNode* binomial_delete(BinomialHeap heap, Type key)
{
	BinomialNode *node;
	BinomialNode *parent, *prev, *pos;

	if (heap == NULL)
		return heap;

	// ���Ҽ�ֵΪkey�Ľڵ�
	if ((node = binomial_search(heap, key)) == NULL)
		return heap;

	// ����ɾ���Ľڵ�������������Ƶ������ڵĶ������ĸ��ڵ�
	parent = node->parent;
	while (parent != NULL)
	{
		// ��������
		swap(node->key, parent->key);
		// ��һ�����ڵ�
		node = parent;
		parent = node->parent;
	}

	// �ҵ�node��ǰһ�����ڵ�(prev)
	prev = NULL;
	pos = heap;
	while (pos != node)
	{
		prev = pos;
		pos = pos->next;
	}
	// �Ƴ�node�ڵ�
	if (prev)
		prev->next = node->next;
	else
		heap = node->next;

	heap = binomial_union(heap, binomial_reverse(node->child));

	free(node);

	return heap;
}

/*
* ��ӡ"�����"
*
* ����˵����
*     node       -- ��ǰ�ڵ�
*     prev       -- ��ǰ�ڵ��ǰһ���ڵ�(���ڵ�or�ֵܽڵ�)
*     direction  --  1����ʾ��ǰ�ڵ���һ������;
*                    2����ʾ��ǰ�ڵ���һ���ֵܽڵ㡣
*/
static void _binomial_print(BinomialNode *node, BinomialNode *prev, int direction)
{
	while (node != NULL)
	{
		//printf("%2d \n", node->key);
		if (direction == 1)
			printf("\t%2d(%d) is %2d's child\n", node->key, node->degree, prev->key);
		else
			printf("\t%2d(%d) is %2d's next\n", node->key, node->degree, prev->key);

		if (node->child != NULL)
			_binomial_print(node->child, node, 1);

		// �ֵܽڵ�
		prev = node;
		node = node->next;
		direction = 2;
	}
}

void binomial_print(BinomialHeap heap)
{
	if (heap == NULL)
		return;

	BinomialNode *p = heap;
	printf("== �����( ");
	while (p != NULL)
	{
		printf("B%d ", p->degree);
		p = p->next;
	}
	printf(")����ϸ��Ϣ��\n");

	int i = 0;
	while (heap != NULL)
	{
		i++;
		printf("%d. ������B%d: \n", i, heap->degree);
		printf("\t%2d(%d) is root\n", heap->key, heap->degree);

		_binomial_print(heap->child, heap, 1);
		heap = heap->next;
	}
	printf("\n");
}