#include <iostream>
#include <stdlib.h>
#define INFINITY 65535
// 最大顶点数，应由用户定义
#define MAXVEX 100
using namespace std;

typedef struct{ //顶点char类型 边int
  char vexs[MAXVEX];  //顶点表
  int arc[MAXVEX][MAXVEX];  //邻接矩阵
  int numNodes,numEdges;  //顶点数和边数
}MGraph;  //图的邻接矩阵

void CreateMGraph(MGraph *G);
void CreateMGraph(MGraph *G){
  int i,j,k,w;
  cout<<"Please input num of vertexs"<<endl;
  cin>>G -> numNodes;
  cout<<"Please input the num of edges"<<endl;
  cin>>G -> numEdges;
  cout<<"Please input vertex values"<<endl;
  for (i = 0 ; i < G -> numNodes;++i) { //输入顶点信息建立顶点表
    cin>>G -> vexs[i];
  }
  for(i = 0;i <G->numNodes;i++)
		for(j = 0;j <G->numNodes;j++)
			G->arc[i][j]=INFINITY;	// 邻接矩阵初始化
  for (k = 0 ; k < G -> numEdges; k++) {
    cout<<"Please inut two subscript (i & j) and one weigh (w)"<<endl;
    cin>> i >> j >> w;
    G -> arc[i][j] = w;
    G -> arc[j][i] = w;//无向图，矩阵对称
  }
}

int main(){
  MGraph G;
  CreateMGraph(&G);
  return 0;
}
