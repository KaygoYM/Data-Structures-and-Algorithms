// Sorting.cpp
// author:KAI

#include "stdafx.h"
#include <stdio.h>
#include "All_sorting.h"
#include<malloc.h>

void Bubble_sort(Elementtype A[], int N)//ð������
{
	int i, j;
	int flag;                 // ���
	for (i = 0; i<N-1; i++)
	{
		flag = 0;            // ��ʼ�����Ϊ0
		 // ��a[0...i]���������ݷ���ĩβ
		for (j = 0; j<N-1-i; j++)
		{
			if (A[j] > A[j + 1])
			{
				Elementtype Tmp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = Tmp;
				flag = 1;    // ������������������Ϊ1
			}
		}
		if (flag == 0)
			break;            // ��û������������˵������������
	}
	//���÷��أ�����Ҳ��������������������
}

void Insert_sort(Elementtype A[], int N)
{
	int j, p;
	Elementtype Tmp;
	for (p = 1; p < N; p++)
	{
		Tmp = A[p];
		for (j = p; j>0 && A[j - 1] > Tmp; j--)
			A[j] = A[j - 1];
		A[j] = Tmp;//jֹͣ�ĵط����ǵ�ǰ����λ��
	}
}

void Shell_sort(Elementtype A[], int N){
	int i, j, Increment;
	Elementtype x;
	for (Increment = N / 2; Increment > 0;Increment/=2)
	for (i = Increment; i < N; i++)
	{
		x = A[i];
		for (j = i; j >= Increment;j-=Increment)
		if (x < A[j - Increment])
			A[j] = A[j - Increment];
		else
			break;
		A[j] = x;
	}
}

#define LeftChild(i)(2*i+1)
void PerDown(Elementtype A[], int i ,int N)//���˷�
{
	int Child;
	Elementtype Tmp;
	for (Tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1]>A[Child])
			Child++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;//�Ѷ�max
}
void Heap_sort(Elementtype A[], int N){
	for (int i = N / 2; i >= 0; i--)//build heap
		PerDown(A, i, N);
		for (int i = N - 1; i > 0; i--)//delete max
		{
			Elementtype x = A[0];
			A[0] = A[i]; 
			A[i] = x;
			PerDown(A, 0, i);
		}
}

void Merge(Elementtype A[], Elementtype xa[], int Lpos, int Rpos, int RightEnd);
void Msort(Elementtype A[], Elementtype xa[], int Left, int Right)
{
	int Center;
	if (Left < Right){ Center = (Left + Right)/ 2;
	Msort(A, xa, Left, Center);
	Msort(A, xa, Center + 1, Right);
	Merge(A, xa, Left, Center + 1, Right);
	}
}
void Merge(Elementtype A[], Elementtype xa[], int Lpos, int Rpos, int RightEnd)
{
	int i, Leftend, num, pos;
	Leftend = Rpos - 1; pos = Lpos; num = RightEnd - Lpos + 1;
	while (Lpos <= Leftend && Rpos <= RightEnd){
		if (A[Lpos] <= A[Rpos])
			xa[pos++] = A[Lpos++];
		else
			xa[pos++] = A[Rpos++];
	}
	while (Lpos<=Leftend)//copy the rest of first half
		xa[pos++] = A[Lpos++];
	while (Rpos <= RightEnd)//copy the rest of first half
		xa[pos++] = A[Rpos++];
	for (i = 0; i < num; i++, RightEnd--)
		A[RightEnd] = xa[RightEnd];
}
void Merge_sort(Elementtype A[], int N)
{
	Elementtype *tmp;
	tmp = (Elementtype*)malloc(N * sizeof(Elementtype));
	if (tmp != NULL){ Msort(A, tmp, 0, N - 1); free(tmp); }
	else printf("No space!");
}


Elementtype Median3(Elementtype A[], int left, int right)
{
	int center = (left + right) / 2;
	int t;
	if (A[left] > A[center]) { t = A[left], A[left] = A[center]; A[center] = t;}
	if (A[left] > A[right]) { t = A[left], A[left] = A[right]; A[right] = t; }
	if (A[center] > A[right]) { t = A[center], A[center] = A[right]; A[right] = t; }
	t=A[center];
	A[center] = A[right];
	A[right] = t;
	return A[right];
}
void Quick_sort(Elementtype A[], int left, int right)
{
	if (left < right)
		{
			int i, j, x;
			x = Median3(A,left,right);
			i = left-1; j = right;//��ĩΪ��ŦԪx
			for (;;)
			{
				while (A[++i] < x){}
				while (A[--j]>x){}
				if (i < j){
					int tmp = A[i];
					A[i] = A[j];
					A[j] = tmp;
				}
				else
					break;
			}	
			int tmp = A[i];
			A[i] = A[right];
			A[right] = tmp;
			Quick_sort(A, left,i-1); /* �ݹ���� */
			Quick_sort(A, i+1,right); /* �ݹ���� */
		}

}

void Bucket_sort(Elementtype A[], int N)
{
	int i, j;
	int buckets[10];//ֻ����0-9
	for (i = 0; i < 10; i++)
		buckets[i] = 0;//��ʼ��Ϊ0
	// ����
	for (i = 0; i < N; i++)
		buckets[A[i]]++;
	// ����
	for (i = 9, j = N-1; i>=0,j>=0; i--)
	{
		while ((buckets[i]--) >0)
			A[j--] = i;
	}

}
