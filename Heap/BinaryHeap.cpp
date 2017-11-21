// BinaryHeap.cpp :
// The basic realization of BinaryHeap �����
// author:KAI
#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
//#include<>ֱ�Ӵӱ������Դ��ĺ�������Ѱ���ļ�
//#include""���ȴ��Զ�����ļ����� ������Ҳ����ڴӺ�������Ѱ���ļ�
//������Լ�д��ͷ�ļ� ����ʹ��#include����
typedef int ElemType;
struct HeapSq 
{
	ElemType* heap; //array
	int len; //length��begin with 0
	int MaxSize;    
};

//1��Initialization
void InitHeap(struct HeapSq* HBT, int MS)
{
	if (MS <= 0)
	{
		printf("the length can't be negative!\n");
		exit(1);
	}
	HBT->heap = (ElemType*)malloc(MS*sizeof(ElemType));
	if (!HBT->heap)
	{
		printf("Out of space��\n");
		exit(1);
	}
	HBT->MaxSize = MS;
	HBT->len = 0;
}

//2��Clear all
void ClearHeap(struct HeapSq* HBT)
{
	if (HBT->heap != NULL)
	{
		free(HBT->heap);
		HBT->len = 0;
		HBT->MaxSize = 0;
	}
	printf("The heap is clean!\n");
}

//3��Empty?
int EmptyHeap(struct HeapSq* HBT)
{
	if (HBT->len == 0)
		return 1;
	else
		return 0;
}

//4��Insert into Heap
void InsertHeap(struct HeapSq* HBT, ElemType x)
{
	int i;
	if (HBT->len == HBT->MaxSize) //if it is full, expand it to double times
	{
		ElemType *p;
		p = (ElemType*)realloc(HBT->heap, 2 * HBT->MaxSize*sizeof(ElemType));
		if (!p)
		{
			printf("Out of Space��\n");
			exit(1);
		}
		printf("Expand to 2 times already��\n");
		HBT->heap = p;
		HBT->MaxSize = 2 * HBT->MaxSize;
	}
	HBT->heap[HBT->len] = x; //insert x to tail
	HBT->len++; //length+1
	i = HBT->len - 1; //iָ�������Ԫ�ص�λ�ã����������±꣬��ʼָ����Ԫ�����ڵĶ�βλ��
	while (i != 0)
	{
		int j = (i - 1) / 2; //jָ���±�Ϊi��Ԫ�ص�˫��
		if (x >= HBT->heap[j]) //����Ԫ�ش��ڴ�����Ԫ�ص�˫�ף���Ƚϵ����������˳�ѭ��
			break;
		HBT->heap[i] = HBT->heap[j]; //��˫��Ԫ�����Ƶ�������Ԫ�ص�λ��
		i = j; //ʹ������λ�ñ�Ϊ��˫��λ�ã�������һ��ѭ��
	}
	HBT->heap[i] = x;//����Ԫ�ص���������λ��
}

//5��Delete the top
ElemType DeleteHeap(struct HeapSq* HBT)
{
	ElemType temp, x;
	int i, j;
	if (HBT->len == 0)
	{
		printf("The heap is empty��\n");
		exit(1);
	}
	temp = HBT->heap[0]; //�ݴ�Ѷ�Ԫ��
	HBT->len--;
	if (HBT->len == 0) //��ɾ���������Ϊ���򷵻�
		return temp;
	x = HBT->heap[HBT->len]; //����������ԭ��βԪ���ݴ�x�У��Ա��������λ��
	i = 0; //��iָ�������Ԫ�ص�λ�ã���ʼָ��Ѷ�λ��
	j = 2 * i + 1;//��jָ��i������λ�ã���ʼָ���±�Ϊ1��λ��
	while (j <= HBT->len - 1)//Ѱ�Ҵ�����Ԫ�ص�����λ�ã�ÿ��ʹ����Ԫ������һ�㣬����������Ϊ��ʱֹ
	{
		if (j < HBT->len - 1 && HBT->heap[j] > HBT->heap[j + 1])//�������Һ����ҽ�С��ʹjָ���Һ���
			j++;
		if (x <= HBT->heap[j]) //��x�����С�ĺ��ӻ�С��������������˳�ѭ��
			break;
		HBT->heap[i] = HBT->heap[j];//���򣬽�����Ԫ���Ƶ�˫��λ��
		i = j; //��������λ�ñ�Ϊ���С�ĺ���λ��
		j = 2 * i + 1;//��j��Ϊ�µĴ�����λ�õ�����λ�ã�������һ��ѭ��
	}
	HBT->heap[i] = x; //��x�ŵ�����λ��
	return temp; //����ԭ�Ѷ�Ԫ��
}

//������
void main()
{
	int i, x;
	int a[8] = { 23, 56, 40, 62, 38, 55, 10, 16 };
	struct HeapSq b;
	InitHeap(&b, 10);
	for (i = 0; i < 8; i++)
	{
		InsertHeap(&b, a[i]);
	}
	while (!EmptyHeap(&b)) //����ɾ���Ѷ�Ԫ�ز���ʾ������ֱ���ѿ�Ϊֹ
	{
		x = DeleteHeap(&b);
		printf("%d", x);
		if (!EmptyHeap(&b))
			printf(",");
	}
	printf("\n");
	ClearHeap(&b);
	system("pause");

}
