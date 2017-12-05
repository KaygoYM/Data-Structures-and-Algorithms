// Dijkstra.cpp : 
// author:KAI

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 20
#define INFINITY 65535

typedef char VertexType;

//定义图 的邻接矩阵表示法结构
typedef struct Graph {
	VertexType ver[MaxSize + 1];//顶点V
	int edg[MaxSize][MaxSize];//边W
}Graph;

//邻接矩阵法图的生成函数
void CreateGraph(Graph *g)
{
	int i = 0;
	int j = 0;
	int VertexNum;
	VertexType Ver;

	printf("请连续输入图的顶点，如:ABC...:\n");
	while ('\n' != (Ver = getchar()))
		g->ver[i++] = Ver;
	g->ver[i] = '\0';

	VertexNum = strlen(g->ver);
	printf("请按行依次输入相应的的邻接矩阵，如:0 12 4...:\n");
	for (i = 0; i<VertexNum; i++)
	for (j = 0; j<VertexNum; j++)
		scanf_s("%d", &g->edg[i][j]);
}

//打印图的结点标识符和邻接矩阵
void PrintGraph(Graph g)
{
	int i, j;
	int VertexNum = strlen(g.ver);
	printf("图的顶点为:\n");
	for (i = 0; i<VertexNum; i++)
		printf("%c ", g.ver[i]);
	printf("\n");

	printf("图的邻接矩阵为:\n");
	for (i = 0; i<VertexNum; i++) {
		for (j = 0; j<VertexNum; j++)
			printf("%d\t", g.edg[i][j]);
		printf("\n");
	}
}

//求图的顶点数
int CalVerNum(Graph g)
{
	return strlen(g.ver);
}

//将不邻接的顶点之间的权值设置为INFINITY
void SetWeight(Graph *g)
{
	for (int i = 0; i<CalVerNum(*g); i++)
	for (int j = 0; j<CalVerNum(*g); j++)
	if (0 == g->edg[i][j])
		g->edg[i][j] = INFINITY;
}

//Dijkstra求最短路径函数
void Dijkstra(Graph g)
{
	int VertexNum = CalVerNum(g);
	int j;
	int mini;//最短距离
	int index = 0;
	int *used = (int *)malloc(sizeof(int)*VertexNum);//集合S known
	int *distance = (int *)malloc(sizeof(int)*VertexNum);
	int *parent = (int *)malloc(sizeof(int)*VertexNum);
	int *last = (int *)malloc(sizeof(int)*VertexNum);

	SetWeight(&g);					//设置权值

	for (int i = 0; i<VertexNum; i++) {
		used[i] = 0;
		distance[i] = g.edg[0][i];   //初始化为与编号为0的顶点的距离
		last[i] = 0;
	}

	used[0] = 1;//起点known 设为1
	parent[index++] = 0;

	for (int i = 0; i<VertexNum - 1; i++) {
		j = 0;
		mini = INFINITY;

		for (int k = 0; k<VertexNum; k++)
		if ((0 == used[k]) && (distance[k] < mini)) {
			mini = distance[k];
			j = k;			//j为刚刚找到的U中到源点路径最短的顶点
		}

		used[j] = 1;//known设为1

		for (int k = 0; k<VertexNum; k++)
		if ((0 == used[k]) && (distance[k] > distance[j] + g.edg[j][k])) {   //由于有顶点新加入S集合，对距离数组distance进行更新，比较原路径长度与以新加入的顶点为中间点的路径长度
			distance[k] = distance[j] + g.edg[j][k];
		}

		parent[index++] = j;
	}

	printf("%c到%c的最短路径经过顶点依次为:\n", g.ver[0], g.ver[VertexNum - 1]);
	for (int i = 0; i<index; i++)
		printf("%c ", g.ver[parent[i]]);
	printf("\n");

	printf("最短路径长度为: %d\n", mini);

}

void main()
{
	Graph g;
	CreateGraph(&g);
	PrintGraph(g);

	Dijkstra(g);
	system("pause");
}
