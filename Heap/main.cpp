/**
* C����ʵ�ֵĶ����
*/
#include"stdafx.h"
#include<stdlib.h>
#include <stdio.h>
#include "Binomial_Heap.h"

#define DEBUG 1

#if DEBUG
#define log(x, ...)   printf(x, __VA_ARGS__)
#else
#define log(x, ...)   
#endif

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

// ��7�� = 1+2+4
int a[] = { 12, 7, 25, 15, 28,
33, 41 };
// ��13�� = 1+4+8
int b[] = { 18, 35, 20, 42, 9,
31, 23, 6, 48, 11,
24, 52, 13 };
// ��֤"����ѵĲ������"
void test_insert()
{
	int i;
	int alen = LENGTH(a);
	BinomialHeap ha = NULL;

	// �����ha
	printf("== �����(ha)���������: ");
	for (i = 0; i<alen; i++)
	{
		printf("%d ", a[i]);
		ha = binomial_insert(ha, a[i]);
	}
	printf("\n");
	// ��ӡ�����ha
	printf("== �����(ha)����ϸ��Ϣ: \n");
	binomial_print(ha);
}

// ��֤"����ѵĺϲ�����"
void test_union()
{
	int i;
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	BinomialHeap ha, hb;

	ha = hb = NULL;

	// �����ha
	printf("== �����(ha)���������: ");
	for (i = 0; i<alen; i++)
	{
		printf("%d ", a[i]);
		ha = binomial_insert(ha, a[i]);
	}
	printf("\n");
	printf("== �����(ha)����ϸ��Ϣ: \n");
	binomial_print(ha); // ��ӡ�����ha

	// �����hb
	printf("== �����(hb)���������: ");
	for (i = 0; i<blen; i++)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb, b[i]);
	}
	printf("\n");
	printf("== �����(hb)����ϸ��Ϣ: \n");
	binomial_print(hb); // ��ӡ�����hb

	// ��"�����hb"�ϲ���"�����ha"�С�
	ha = binomial_union(ha, hb);
	printf("== �ϲ�ha��hb�����ϸ��Ϣ:\n");
	binomial_print(ha); // ��ӡ�����ha����ϸ��Ϣ
}

// ��֤"����ѵ�ɾ������"
void test_delete()
{
	int i;
	int blen = LENGTH(b);
	BinomialHeap hb = NULL;

	// �����hb
	printf("== �����(hb)���������: ");
	for (i = 0; i<blen; i++)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb, b[i]);
	}
	printf("\n");
	printf("== �����(hb)����ϸ��Ϣ: \n");
	binomial_print(hb); // ��ӡ�����hb

	// ɾ�������hb�еĽڵ�
	i = 20;
	hb = binomial_delete(hb, i);
	printf("== ɾ���ڵ�%d�����ϸ��Ϣ: \n", i);
	binomial_print(hb); // ��ӡ�����hb
}

// ��֤"����ѵĸ���(����)����"
void test_decrease()
{
	int i;
	int blen = LENGTH(b);
	BinomialHeap hb = NULL;

	// �����hb
	printf("== �����(hb)���������: ");
	for (i = 0; i<blen; i++)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb, b[i]);
	}
	printf("\n");
	printf("== �����(hb)����ϸ��Ϣ: \n");
	binomial_print(hb); // ��ӡ�����hb

	// ���ڵ�20����Ϊ2
	binomial_update(hb, 20, 2);
	printf("== ���½ڵ�20->2�����ϸ��Ϣ: \n");
	binomial_print(hb); // ��ӡ�����hb
}

// ��֤"����ѵĸ���(����)����"
void test_increase()
{
	int i;
	int blen = LENGTH(b);
	BinomialHeap hb = NULL;

	// �����hb
	printf("== �����(hb)���������: ");
	for (i = 0; i<blen; i++)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb, b[i]);
	}
	printf("\n");
	printf("== �����(hb)����ϸ��Ϣ: \n");
	binomial_print(hb); // ��ӡ�����hb

	// ���ڵ�6����Ϊ20
	binomial_update(hb, 6, 60);
	printf("== ���½ڵ�6->60�����ϸ��Ϣ: \n");
	binomial_print(hb); // ��ӡ�����hb
}


void main()
{
	// 1. ��֤"����ѵĲ������"
	test_insert();
	// 2. ��֤"����ѵĺϲ�����"
	test_union();
	// 3. ��֤"����ѵ�ɾ������"
	test_delete();
	// 4. ��֤"����ѵĸ���(����)����"
	test_decrease();
	// 5. ��֤"����ѵĸ���(����)����"
	test_increase();
	system("pause");
}