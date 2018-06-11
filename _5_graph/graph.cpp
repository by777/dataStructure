#include <iostream>
#include <stdlib.h>
#include <string.h>
#define maxSize 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

using namespace std;

// 邻接矩阵 A[i][j] = 1 表示i,j之间有边（可以有权值）
typedef struct{
  int no;
  char info;
}VertxtType;//顶点

typedef struct{
  int edges[maxSize][maxSize];
  int n,e;//存放顶点数和边数
  VertxtType vex[maxSize];//图的邻接矩阵类型
}MGraph;//图的邻接矩阵
