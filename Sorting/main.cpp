#include"stdafx.h"
#include<stdio.h>
#include "stdlib.h"
#include<malloc.h>
#include"All_sorting.h"
#include<time.h>

void print_s(Elementtype A[], int N,char a[])
{
	printf("The %s sort is: ", a);
	for (int i = 0; i < N; i++)
		printf("%d ",A[i]);
}

void main()
{
	const long int N = 100000;
	int Test_array[N];
	time_t start, end;
	for (int test = 1; test <= 7; test++){
		printf("The test_array is: ");
	
		for (int i = 0; i < N; i++)
			{
				Test_array[i] = rand() % 10;
				printf("%d ", Test_array[i]);
			}
			printf("\n");

			switch (test)
			{
			case 1:
			{
					  time(&start);
					  Bubble_sort(Test_array, N);//冒泡
					  time(&end);
					  print_s(Test_array, N, "Bubble");
					  printf("Bubble time= %lf s\n", difftime(end, start));
					  break;
			}
			case 2:
			{
					  time(&start);
					  Insert_sort(Test_array, N);//插入
					  time(&end);
					  print_s(Test_array, N, "Insert");
					  printf("Insert time= %lf s\n", difftime(end, start));
					  break;
			}
			case 3:
			{
					  time(&start);
					  Shell_sort(Test_array, N);//希尔
					  time(&end);
					  print_s(Test_array, N, "Shell");
					  printf("Shell time= %lf s\n", difftime(end, start));
					  break;
			}
			case 4:
			{
					  time(&start);
					  Heap_sort(Test_array, N);//堆
					  time(&end);
					  print_s(Test_array, N, "Heap");
					  printf("Heap time= %lf s\n", difftime(end, start));
					  break;
			}
			case 5:
			{
					  time(&start);
					  Merge_sort(Test_array, N);//归并
					  time(&end);
					  //print_s(Test_array, N, "Merge");
					  printf("Merge time= %lf s\n", difftime(end, start));
					  break;
			}
			case 6:
			{
					  time(&start);
					  Quick_sort(Test_array,0,N-1);//快速
					  time(&end);
					  print_s(Test_array, N, "Quick");
					  printf("Quick time= %lf s\n", difftime(end, start));
					  break;
			}
			case 7:
			{
					  time(&start);
					  Bucket_sort(Test_array, N);//桶式
					  time(&end);
					  print_s(Test_array, N, "Bucket");
					  printf("Bucket time= %lf s\n", difftime(end, start));
					  break;
			}
			default:continue;
			}
		}
	system("pause");
}
