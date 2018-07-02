#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define INFINITY 65535
#define maxSize 100
// 最大顶点数
#define MAXVEX 100
using namespace std;

typedef struct { //顶点char类型 边int
        char vexs[MAXVEX]; //顶点表
        int arc[MAXVEX][MAXVEX]; //邻接矩阵
        int numNodes,numEdges; //顶点数和边数
}MGraph;  //图的邻接矩阵

typedef struct EdgeNode {
        //边表节点
        int adjvex;//邻节点域，存储该顶点对应的下标
        int info;//权值
        struct EdgeNode *next;//指向下一个邻接点
}EdgeNode;

typedef struct VertexNode {
        //顶点表节点
        int in;//顶点入度
        char data;//顶点域，存储顶点信息
        EdgeNode *firstedge;//边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct {
        AdjList adjList;
        int numNodes,numEdges;//图中当前顶点数和边数
}GraphAdjList;

bool visited[MAXVEX];//邻接矩阵访问标志的数组

void CreateMGraph(MGraph *G);//邻接矩阵
void CreateALGraph(GraphAdjList *G);//邻接表建立
void MGDFS(MGraph G,int i);
void MGDFSTraverse(MGraph G);//邻接矩阵深度优先遍历
void MGBFSTraverse(MGraph *G);//邻接矩阵广度优先遍历
void CreateMGraphDemo(MGraph *G);//快速创建邻接矩阵Demo
void CreateALGraphDemo(MGraph G,GraphAdjList *&GL);//利用邻接矩阵快速构建邻接表Demo
void ALDFS(GraphAdjList *GL,int i);
void ALDFSTraverse(GraphAdjList *GL);//邻接表的深度优先递归算法
void ALBFSTraverse(GraphAdjList *GL);//邻接表的广度优先递归算法
void MiniSpanTree_Prim(MGraph G,int v0,int &sum);//使用Prime最小代价生成树

void MiniSpanTree_Prim(MGraph G,int v0,int &sum){
        /* 普里姆算法生成最小代价生成树
         * 普里姆算法思想：
         * 从图中任取出一个顶点，将它当成一棵树然后从与这棵树相接的边中选取一条最短（权值最小）
         * 的边，并将这条边及其所连接的顶点也并入到这棵树中，此时得到了一棵有两个顶点的树。
         * 然后从与这棵树相接的边中选取一条最短的边，并将这条边及其所连顶点并入当前树中，
         * 得到一棵具有3得到一棵具有3的顶点的树。以此类推……
         * 用Prim构造最小生成树的过程中，需要建立两个数组vset[]和lowcost[]。
         * lowcost[]存放当前生成树到剩余各顶点最短边的权值。
         * =============================================================================
         * 从树中某一结点V_0开始，构造生成树的算法如下：
         * 1）将V_0到其它顶点的所有边作为候选边；
         * 2）重复一下步骤n-1次，使得其它n-1个顶点被并入到生成树中。
         *  1. 从候选边中挑出权值最小的边输出，并将与该边另一端相接的顶点v并入到生成树中
         * ·2。考察所有剩余顶点V_i，如果（V，V_i）的权值比lowcost[V_i]小，则用(V,V_i)的权值更新lowcost[V_i]
         */
        //=======================BUG在此：DEMO建立错误：待修复==================
        int lowcost[maxSize],vset[maxSize],v;
        int i,min,j,k;
        for (i = 1; i < G.numNodes; ++i ) {
                lowcost[i] = G.arc[v0][i];//顶点v0到其余各顶点的距离
                vset[i] = 0;
        }
        vset[v0] = 1;//将v0并入树中
        sum = 0;
        for (i= 1; i < G.numNodes; ++i) {
                min = INFINITY;
                // 找出候选边中的最小者
                for(j = 1; j < G.numNodes; ++j) {
                        if (vset[j]==0&&lowcost[j]<min) {
                                //选出当前生成树到其余各顶点最短边中的一条
                                min = lowcost[j];
                                k = j;
                        }
                        printf("(%d, %d)\n", G.arc[k], k);/* 打印当前顶点边中权值最小的边 */
                        vset[k] = 1;
                        v = k;
                        sum += min;//sum记录了最小生成树的权值
                        //以刚并入的顶点v为媒介更新候选边
                        for(j = 1; j<G.numNodes; ++j)
                                if(vset[j]==0&&G.arc[v][j]<lowcost[j])
                                        lowcost[j] = G.arc[v][j]; //过程2）
                }
        }

}

void ALBFSTraverse(GraphAdjList *GL){
        cout<<"\n"<<"现在广度优先遍历邻接表"<<endl;
        int i;
        EdgeNode *p = NULL;
        int que[maxSize],front = 0,rear=0;
        for(i=0; i<GL->numNodes; i++)
                visited[i] = false;
        for(i=0; i<GL->numNodes; i++) {
                if (!visited[i]) {
                        visited[i] = true;
                        rear = (rear + 1) % maxSize;
                        que[rear] = i;
                        while(rear!=front) {
                                front = (front + 1) % maxSize;
                                i = que[front];
                                p = GL->adjList[i].firstedge;
                                while(p) {
                                        if (!visited[p->adjvex]) {
                                                visited[p->adjvex] = true;
                                                printf("%c ",GL->adjList[p->adjvex].data);
                                                rear = (rear + 1) % maxSize;
                                                que[rear] = p->adjvex;
                                        }
                                        p = p->next;
                                }
                        }
                }
        }
}

void ALDFSTraverse(GraphAdjList *GL){
        cout<<"现在深度优先遍历邻接表"<<endl;
        // 初始化visited数组
        int i;
        for(i=0; i<GL->numNodes; i++)
                visited[i] = false;
        for(i=0; i<GL->numNodes; i++)
                if(!visited[i])
                        ALDFS(GL,i);
}

void ALDFS(GraphAdjList *GL,int i){
        EdgeNode *p;
        visited[i] = true;
        printf("%c ",GL->adjList[i].data);//打印顶点
        p = GL->adjList[i].firstedge;
        while (p) {
                if (!visited[p->adjvex]) {//adjvex节点域，存储该顶点对应的下标
                        ALDFS(GL,p->adjvex);
                }
                p = p->next;
        }
}


void CreateALGraphDemo(MGraph G,GraphAdjList *&GL){
        int i,j;
        EdgeNode *e;
        GL = (GraphAdjList *)malloc(sizeof(GraphAdjList));
        GL->numNodes = G.numNodes;
        GL->numEdges = G.numEdges;
        for(i=0; i<G.numNodes; i++) {
                //读入顶点信息，建立顶点表
                GL->adjList[i].in = 0;
                GL->adjList[i].data = G.vexs[i];//顶点
                GL->adjList[i].firstedge = NULL;//将边表置为空表
        }
        for (i=0; i<G.numNodes; ++i) {
                // 建立边表
                for (j=0; j<G.numNodes; ++j) {
                        if (G.arc[i][j]==1) {
                                e = (EdgeNode*)malloc(sizeof(EdgeNode));
                                /*typedef struct EdgeNode{
                                   //边表节点
                                   int adjvex;//邻节点域，存储该顶点对应的下标
                                   int info;//权值
                                   struct EdgeNode *next;//指向下一个邻接点
                                   }EdgeNode;*/
                                e->adjvex = j;
                                e->next = GL->adjList[i].firstedge;
                                GL->adjList[i].firstedge = e;
                                GL->adjList[j].in++;
                        }
                }
        }
}

void MGBFSTraverse(MGraph *G){
        /* 图的广度优先搜索遍历（BFS）类似于树的层次遍历。
         * 它的基本思想是：
         * 首先访问起始节点v,然后选取与v邻接的全部顶点w1,w2,...进行访问，
         * 再依次访问与w1，w2...邻接的全部顶点（已经访问过的除外），以此类推。
         * 简单概括：
         * 1）任取图中一个节点访问，入队，并将这个节点标记为已访问过。
         * 2）当队列不空时循环执行：出队，依次检查出队顶点的所有邻接顶点，访问没有被访问过的邻接顶点并将其入队
         * 3）当队列为空时跳出循环，广度优先搜索完成
         */
        int que[maxSize],front = 0,rear=0,i,j;
        for(i = 0; i<G->numNodes; i++) {
                visited[i] = 0;
        }
        for (i = 0; i<G->numNodes; i++) {
                //对每一个顶点做循环
                if (!visited[i]) {
                        cout<<"访问节点:"<<G->vexs[i]<<endl;
                        visited[i] = 1;
                        //将此顶点入队列
                        rear = (rear + 1) % maxSize;
                        que[rear] = i;
                        while (front != rear) {
                                front = (front + 1) % maxSize;
                                j = que[front];
                                //判断其它顶点若与当前顶点存在边且未访问过
                                for(j = 0; j < G->numNodes; j++) {
                                        if(G->arc[i][j] == 1 && !visited[j]) {
                                                cout<<"更换节点:"<<G->vexs[j]<<endl;
                                                visited[j] = 1;
                                                rear = (rear + 1) % maxSize;
                                                que[rear] = j;
                                        }
                                }
                        }
                }
        }
}

void CreateMGraphDemo(MGraph *G){
        int i,j;
        G->numEdges = 15;
        G->numNodes = 9;
        // 读入顶点信息建立顶点表
        G->vexs[0] = 'A';
        G->vexs[1] = 'B';
        G->vexs[2] = 'C';
        G->vexs[3] = 'D';
        G->vexs[4] = 'E';
        G->vexs[5] = 'F';
        G->vexs[6] = 'G';
        G->vexs[7] = 'H';
        G->vexs[8] = 'I';
        // 初始化图
        for (i = 0; i< G->numNodes; i++) {
                for (j = 0; j < G->numNodes; j++) {
                        G->arc[i][j]=0;
                }
        }
        G->arc[0][1]=1;
        G->arc[0][5]=1;
        G->arc[1][2]=1;
        G->arc[1][8]=1;
        G->arc[1][6]=1;
        G->arc[2][3]=1;
        G->arc[2][8]=1;
        G->arc[3][4]=1;
        G->arc[3][7]=1;
        G->arc[3][6]=1;
        G->arc[3][8]=1;
        G->arc[4][5]=1;
        G->arc[4][7]=1;
        G->arc[5][6]=1;
        G->arc[6][7]=1;
        for(i = 0; i < G->numNodes; i++)
        {
                for(j = i; j < G->numNodes; j++)
                {
                        G->arc[j][i] =G->arc[i][j];
                }
        }
}

void MGDFS(MGraph G,int i){
        /*
         * 图的深度优先搜索遍历（DFS）类似于二叉树的先序遍历。
         * 它的基本思想是：
         * 首先访问出发点v,并将其标记为已访问过，然后选取与v邻接的未被访问的任一个顶点，并访问它
         * 再选取与w邻接的未被访问过的任一节点并访问，以此重复进行。
         */
        int j;
        visited[i] = 1;
        printf("%c ", G.vexs[i] );//操作
        for(j=0; j<G.numNodes; j++) {
                if (G.arc[i][j]==1&&visited[j]) {
                        MGDFS(G,j);//对未访问的邻接顶点递归调用
                }
        }
}

void MGDFSTraverse(MGraph G){
        int i;
        for (i=0; i<G.numNodes; i++) {
                //初始所有顶点状态都是未访问过状态
                visited[i]=0;
        }
        for(i=0; i<G.numNodes; i++) {
                if (!visited[i]) {
                        MGDFS(G,i);//对为访问过的节点DFS
                }
        }
}

void CreateALGraph(GraphAdjList *G){
        int i,k,j;
        EdgeNode *e;
        cout<<"请输入顶点数和边数(逗号分隔)："<<endl;
        scanf("%d,%d",&G->numNodes,&G->numEdges);
        cout<<"读入顶点信息,建立顶点表"<<endl;
        for (i = 0; i <G->numNodes; i++) {
                scanf(&G->adjList[i].data);//顶点信息
                G->adjList[i].firstedge = NULL;//边表置为空表
        }
        for(k = 0; k < G->numEdges; k++) {
                cout << "输入边(vi,vj)上的顶点序号:\n" <<endl;
                scanf("%d,%d",&i,&j); /* 输入边(vi,vj)上的顶点序号 */
                e = (EdgeNode *)malloc(sizeof(EdgeNode));//申请边表节点
                e->adjvex=j; /* 邻接序号为j */
                e->next=G->adjList[i].firstedge; /* 将e的指针指向当前顶点上指向的结点 */
                G->adjList[i].firstedge=e; /* 将当前顶点的指针指向e */

                e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
                e->adjvex=i; /* 邻接序号为i */
                e->next=G->adjList[j].firstedge; /* 将e的指针指向当前顶点上指向的结点 */
                G->adjList[j].firstedge=e; /* 将当前顶点的指针指向e */
        }
}

void CreateMGraph(MGraph *G){
        // 无向网图的邻接矩阵表示
        int i,j,k,w;
        cout<<"请输入顶点数："<<endl;
        cin>>G->numNodes;
        cout<<"请输入边数："<<endl;
        cin>>G->numEdges;
        cout<<"读入顶点信息，建立顶点表"<<endl;
        for (i = 0; i < G->numNodes; ++i) { //输入顶点信息建立顶点表
                cin>>G->vexs[i];
        }
        for(i = 0; i <G->numNodes; i++)
                for(j = 0; j <G->numNodes; j++)
                        G->arc[i][j]=INFINITY; // 邻接矩阵初始化
        for (k = 0; k < G->numEdges; k++) {
                cout<<"输入边(vi,vj)上的下标i，下标j和权w："<<endl;
                cin>> i >> j >> w;
                G->arc[i][j] = w;
                G->arc[j][i] = w;//无向图，矩阵对称
        }
}
///////////////////增加图结构示意图//////////////////
int main(){
        // MGraph G;
        // CreateMGraph(&G);
        MGraph MG;
        //CreateALGraph(&Q);
        CreateMGraphDemo(&MG);
        //MGDFSTraverse(G);
        //MGBFSTraverse(&MG);
        GraphAdjList* GLDemo = NULL;
        CreateALGraphDemo(MG,GLDemo);//利用邻接矩阵MG创建了邻接表GL
        ALDFSTraverse(GLDemo);
        ALBFSTraverse(GLDemo);
        int sum = 0;
        int v0 = 0;
        MiniSpanTree_Prim(MG,v0,sum);
        cout<<"最小代价："<<sum<<endl;
        return 0;
}
