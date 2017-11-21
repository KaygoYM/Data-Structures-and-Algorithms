#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_

typedef int Type;

typedef struct _BinomialNode{
	Type   key;                     // �ؼ���(��ֵ)
	int degree;                     // ����
	struct _BinomialNode *child;    // ����
	struct _BinomialNode *parent;   // ���ڵ�
	struct _BinomialNode *next;     // �ֵ�
}BinomialNode, *BinomialHeap;

// �½�key��Ӧ�Ľڵ㣬��������뵽������С�
BinomialNode* binomial_insert(BinomialHeap heap, Type key);
// ɾ���ڵ㣺ɾ����ֵΪkey�Ľڵ㣬������ɾ���ڵ��Ķ�����
BinomialNode* binomial_delete(BinomialHeap heap, Type key);
// �������heap�ļ�ֵoldkey����Ϊnewkey
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey);

// �ϲ�����ѣ���h1, h2�ϲ���һ���ѣ������غϲ���Ķ�
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2);

// ���ң��ڶ�����в��Ҽ�ֵΪkey�Ľڵ�
BinomialNode* binomial_search(BinomialHeap heap, Type key);
// ��ȡ������е���С�ڵ�
BinomialNode* binomial_minimum(BinomialHeap heap);
// �Ƴ���С�ڵ㣬�������Ƴ��ڵ��Ķ����
BinomialNode* binomial_extract_minimum(BinomialHeap heap);

// ��ӡ"�����"
void binomial_print(BinomialHeap heap);

#endif