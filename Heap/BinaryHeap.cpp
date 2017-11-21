// BinaryHeap.cpp :
// The basic realization of BinaryHeap 二叉堆
// author:KAI
#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
//#include<>直接从编译器自带的函数库中寻找文件
//#include""是先从自定义的文件中找 ，如果找不到在从函数库中寻找文件
//如果是自己写的头文件 建议使用#include“”
typedef int ElemType;
struct HeapSq 
{
	ElemType* heap; //array
	int len; //length，begin with 0
	int MaxSize;    
};

//1、Initialization
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
		printf("Out of space！\n");
		exit(1);
	}
	HBT->MaxSize = MS;
	HBT->len = 0;
}

//2、Clear all
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

//3、Empty?
int EmptyHeap(struct HeapSq* HBT)
{
	if (HBT->len == 0)
		return 1;
	else
		return 0;
}

//4、Insert into Heap
void InsertHeap(struct HeapSq* HBT, ElemType x)
{
	int i;
	if (HBT->len == HBT->MaxSize) //if it is full, expand it to double times
	{
		ElemType *p;
		p = (ElemType*)realloc(HBT->heap, 2 * HBT->MaxSize*sizeof(ElemType));
		if (!p)
		{
			printf("Out of Space！\n");
			exit(1);
		}
		printf("Expand to 2 times already！\n");
		HBT->heap = p;
		HBT->MaxSize = 2 * HBT->MaxSize;
	}
	HBT->heap[HBT->len] = x; //insert x to tail
	HBT->len++; //length+1
	i = HBT->len - 1; //i指向待调整元素的位置，即其数组下标，初始指向新元素所在的堆尾位置
	while (i != 0)
	{
		int j = (i - 1) / 2; //j指向下标为i的元素的双亲
		if (x >= HBT->heap[j]) //若新元素大于待调整元素的双亲，则比较调整结束，退出循环
			break;
		HBT->heap[i] = HBT->heap[j]; //将双亲元素下移到待调整元素的位置
		i = j; //使待调整位置变为其双亲位置，进行下一次循环
	}
	HBT->heap[i] = x;//把新元素调整到最终位置
}

//5、Delete the top
ElemType DeleteHeap(struct HeapSq* HBT)
{
	ElemType temp, x;
	int i, j;
	if (HBT->len == 0)
	{
		printf("The heap is empty！\n");
		exit(1);
	}
	temp = HBT->heap[0]; //暂存堆顶元素
	HBT->len--;
	if (HBT->len == 0) //若删除操作后堆为空则返回
		return temp;
	x = HBT->heap[HBT->len]; //将待调整的原堆尾元素暂存x中，以便放入最终位置
	i = 0; //用i指向待调整元素的位置，初始指向堆顶位置
	j = 2 * i + 1;//用j指向i的左孩子位置，初始指向下标为1的位置
	while (j <= HBT->len - 1)//寻找待调整元素的最终位置，每次使孩子元素上移一层，调整到孩子为空时止
	{
		if (j < HBT->len - 1 && HBT->heap[j] > HBT->heap[j + 1])//若存在右孩子且较小，使j指向右孩子
			j++;
		if (x <= HBT->heap[j]) //若x比其较小的孩子还小，则调整结束，退出循环
			break;
		HBT->heap[i] = HBT->heap[j];//否则，将孩子元素移到双亲位置
		i = j; //将待调整位置变为其较小的孩子位置
		j = 2 * i + 1;//将j变为新的待调整位置的左孩子位置，继续下一次循环
	}
	HBT->heap[i] = x; //把x放到最终位置
	return temp; //返回原堆顶元素
}

//主函数
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
	while (!EmptyHeap(&b)) //依次删除堆顶元素并显示出来，直到堆空为止
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
