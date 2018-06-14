#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define INFINITY 65535
// 最大顶点数
#define MAXVEX 100
using namespace std;

typedef struct{ //顶点char类型 边int
  char vexs[MAXVEX];  //顶点表
  int arc[MAXVEX][MAXVEX];  //邻接矩阵
  int numNodes,numEdges;  //顶点数和边数
}MGraph;  //图的邻接矩阵

typedef struct EdgeNode{
  //边表节点
  int adjvex;//邻节点域，存储该顶点对应的下标
  int info;//权值
  struct EdgeNode *next;//指向下一个邻接点
}EdgeNode;

typedef struct VertexNode{
  //顶点表节点
  char data;//顶点域，存储顶点信息
  EdgeNode *firstedge;//边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct{
  AdjList adjList;
  int numNodes,numEdges;//图中当前顶点数和边数
}GraphAdjList;

void CreateMGraph(MGraph *G);//邻接矩阵
void CreateALGraph(GraphAdjList *G);//邻接表建立
void CreateALGraph(GraphAdjList *G){
  int i,k,j;
  EdgeNode *e;
  cout<<"Please input numNodes and numEdges "<<endl;
  scanf("%d,%d",&G->numNodes,&G->numEdges);
  /* 读入顶点信息,建立顶点表 */
  for (i = 0; i <G -> numNodes; i++) {
    scanf(&G->adjList[i].data);//顶点信息
    G -> adjList[i].firstedge = NULL;//边表置为空表
  }
  for(k = 0; k < G -> numEdges; k++){
    cout << "Input edge(vi vj) numNodes " <<endl;
    scanf("%d,%d",&i,&j); /* 输入边(vi,vj)上的顶点序号 */
    e = (EdgeNode *)malloc(sizeof(EdgeNode));//申请边表节点
    e->adjvex=j;					/* 邻接序号为j */
    e->next=G->adjList[i].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
    G->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e */

    e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
    e->adjvex=i;					/* 邻接序号为i */
    e->next=G->adjList[j].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
    G->adjList[j].firstedge=e;		/* 将当前顶点的指针指向e */
  }
}

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
    cout<<"Please input two subscript (i & j) and one weigh (w)"<<endl;
    cin>> i >> j >> w;
    G -> arc[i][j] = w;
    G -> arc[j][i] = w;//无向图，矩阵对称
  }
}
///////////////////增加图结构示意图//////////////////
int main(){
  // MGraph G;
  // CreateMGraph(&G);
  GraphAdjList Q;
  CreateALGraph(&Q);

  return 0;
}
