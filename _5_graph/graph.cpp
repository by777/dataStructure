#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define INF 65535
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

typedef struct {
        int a,b;//a和b为一条边所连的两个顶点
        int w;//边的权值
}Road;

bool visited[MAXVEX];//邻接矩阵访问标志的数组
//int path[MAXVEX];
//保存从V_0到V_i最短路径上V_i的前一个顶点，假设最短路径上的顶点序列为V0,V1,...，则path[V_i]
//为V_i-1。path的初态为：如果V_0到V_i有边，则path[V_i]=V_0，否则-1
//int dist[MAXVEX];
//表示当前已经找到的从V_0到每个重点V_j的最短路径的长度。它的初态为：若从V_0到V_i有边则
//dist[V_j]为边上的权值，否则置dist[V_j]为∞

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
void MiniSpanTree_Kruskal(MGraph G);//使用克鲁斯卡尔最小代价生成树
void sort(Road roads[],MGraph &G);
void Swapn(Road roads[],int i, int j);
void ShortestPath_Dijkstra(MGraph G, int v, int dist[], int path[]);
//求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和
void PrintPath_Dijkstra(int path[],int n);
void PrintPath_Floyd(int u, int v, int Path[][maxSize]);
void ShortestPath_Floyd(MGraph G,int Path[][maxSize]);
void InitMGraphDemo(MGraph *G);

void PrintPath_Floyd(int u, int v, int Path[][maxSize]){
        //输出从u到v的最短路径上顶点序列
        if (Path[u][v] == -1) {
                cout<<Path[u][v];//直接输出
        }
        else{
                int mid = Path[u][v];
                PrintPath_Floyd(u,mid,Path);
                PrintPath_Floyd(mid,v,Path);
        }
        /*
         * 例如：
         * 由Path[1][0] = 3可知，从顶点1到顶点0要经过顶点3，将3作为下一步的起点
         * 由Path[1][0] = -1可知，从顶点1到顶点0有直接相连的边，求解结束
         *
         */
}

void ShortestPath_Floyd(MGraph G,int Path[][maxSize]){
        /*
         * 弗洛伊德算法求解最短路径的一般过程
         * 1）设置两个矩阵A和Path，初始时将图的邻接矩阵赋值给A，将矩阵Path中的元素全部设置为-1
         * 2）以顶点k为中间顶点，k取0~n-1，对图中所有顶点对（i，j）进行如下检测和修改：
         *    如果A[i][j] > A[i][k] + A[k][J]，则将Path[i][j]改为k。
         *         *
         */
        int A[maxSize][maxSize];
        int i,j,k;
        for(i = 0; i < G.numNodes; i++)
                for (j = 0; j < G.numNodes; j++) {
                        A[i][j] = G.arc[i][j];
                        Path[i][j] = -1;
                }
        for(k = 0; k < G.numNodes; k++)
                for(i = 0; i < G.numNodes; i++)
                        for (j = 0; j < G.numNodes; j++) {
                                if (A[i][j] > A[i][k] + A[k][j]) {
                                        A[i][j] = A[i][k] + A[k][j];
                                        Path[i][j] = k;
                                }
                        }

}

void PrintPath_Dijkstra(int path[],int a){
        /*
         * path数组实际上保存了一棵树，这是一棵用双亲表示法存储的树，通过这棵树可以打印从源点
         * 到任何一个顶点最短路径上所经过的所有顶点。树的双亲表示法只能直接输出由叶子节点到根节点
         * 路径上的节点，而不能逆向输出，因此需要一个栈辅助输出
         *
         */
        int stack[maxSize],top = -1;
        cout<<"path[a]:"<<path[a]<<endl;
        //cout<<path[a];
        while (path[a] != -1) {
                //这个循环以叶子节点到根节点的顺序入栈
                stack[++top] = a;
                a = path[a];
        }
        stack[++top] = a;
        while (top != -1)
                cout<<stack[top--] <<" ";
        cout<<"\n--End--"<<endl;

}

void ShortestPath_Dijkstra(MGraph G, int v, int dist[], int path[]){
        /* 采用迪杰斯特拉算法求图中某一顶点到其余各顶点的最短路径
         * 执行过程：
         * 1） 从当前的dist[]数组中选出最小值，假设为dist[V_u]，将set[V_u]设置为1，表示
         *     当前新并入的节点为V_u。
         * 2） 循环扫描图中顶点，对每个顶点进行以下检测：
         *     假设当前顶点为V_j，检测V_j是否已经已经被并入S中，即看是否set[V_j]=1。
         *     若是，则什么也不做；如果set[V_j]=0，
         *     则比较dist[V_j]和dist[V_u]+w的大小，其中w为边<V_u,V_j>的权值。
         *     这个比较就是要看V_0经过旧的最短路径到达V_j和V_0经过含有V_u的新的最短路径
         *     到达V_j哪个更短，
         *     -----------------------------------------------------------------
         *     ######如果dist[V_j]>dist[V_u]+w,则用新的路径长度代替旧的，#########
         *     -----------------------------------------------------------------
         *     并把顶点V_u加入路径中，且作为路径上V_j之前的那个顶点；否则什么都不做。
         * 3） 对1）和2）循环执行n-1次（n为图中顶点个数），即可得到V_0到其余所有顶点
         *     的最短路径。ph
         */
        int set[maxSize];//=1代表被并入到最短路径中，初态为set[V0]=1，其余为0
        int i,j,u,min;
        for ( i = 0; i < G.numNodes; i++) {
                //初始化数组
                dist[i]=G.arc[v][i];//dist[V_j]为边上的权值，否则置dist[V_j]为∞
                set[i]=0;
                if (G.arc[v][i]<INF)
                        //如果V_0到V_i有边，则path[V_i]=V_0，否则-1
                        path[i]=v;

                else
                        path[i]=-1;
        }
        set[v] = 1;
        path[v] = -1;
        //初始化结束、关键操作开始
        for (i = 0; i < G.numNodes -1; i++) {
                min = INF;
                //这个循环每次从剩余顶点中选出一个顶点，通往这个顶点的路径在通往
                //所以剩余顶点的路径中长度是最短的
                for (j = 0; j < G.numNodes; j++) {
                        if(set[j] == 0 && dist[j] < min) {//j没有被并入且距离更短
                                u = j;
                                min=dist[j];
                        }
                }
                set[u] = 1;//将刚选出的顶点并入到最短路径中
                //将这个循环以刚并入的顶点作为中间点，对所有通往剩余顶点的路径进行检测
                for(j = 0; j < G.numNodes; j++) {
                        //判断顶点u的加入是否会出现通过顶点j的更短的路径，如果出现，就修改原来的路径及长度
                        if (set[j] == 0 && dist[u] + G.arc[u][j] < dist[j]) {
                                dist[j] = dist[u] + G.arc[u][j];
                                path[j] = u;
                        }
                }

        }//关键操作结束
//函数结束时，dist[]数组存放了v点到其余顶点的最短路径长度，path[]存放了v点到其余各顶点的最短路径
}

void Swapn(Road roads[],int i, int j){
        int temp;
        temp = roads[i].a;
        roads[i].a = roads[j].a;
        roads[j].a = temp;
        temp = roads[i].b;
        roads[i].b = roads[j].b;
        roads[j].b = temp;
        temp = roads[i].w;
        roads[i].w = roads[j].w;
        roads[j].w = temp;
}

int find(int* parent,int f){
        //查找连线顶点的尾部下标
        while (parent[f]>0) {
                f=parent[f];
        }
        //cout<<f<<" ";
        return f;
}

void sort(Road roads[],MGraph &G){
        //对权值进行排序
        int i, j;
        for ( i = 0; i < G.numEdges; i++)
        {
                for ( j = i + 1; j < G.numEdges; j++)
                {
                        if (roads[i].w > roads[j].w)
                        {
                                Swapn(roads, i, j);
                        }
                }
        }
        printf("权排序之后的为:\n");
        for (i = 0; i < G.numEdges; i++)
        {
                printf("(%d, %d) %d\n", roads[i].a, roads[i].b, roads[i].w);
        }
}

void MiniSpanTree_Kruskal(MGraph G){
        /* 主要思想：每次找出候选边中最小权重的值，并入到生成树中
         * 执行过程：将图中边按权值从小到大排序，然后从最小边开始扫描各边，并检查当前边是否
         * 为候选边，即否该边的并入会构成回路，如果不构成回路，则将该边并入当前生成树中。
         */
        int i,j,m,n;
        int k = 0;
        int parent[MAXVEX]; //定义一数组用来判断是否形成环路
        Road roads[MAXVEX];//边集数组
        // 构建边集数组并排序
        for(i = 0; i<G.numNodes -1; i++) {
                for(j = i+1; j < G.numNodes; j++) {
                        if (G.arc[i][j]<INF) {
                                roads[k].a=i;
                                roads[k].b=j;
                                roads[k].w=G.arc[i][j];
                                k++;
                        }
                }
        }
        sort(roads,G);
        for (i = 0; i<G.numNodes; i++ ) {
                parent[i]=0;//初始化数组为0
        }
        cout<<"打印最小生成树："<<endl;
        for(i=0; i<G.numEdges; i++) {
                n = find(parent,roads[i].a);
                m = find(parent,roads[i].b);

                if (m!=n) {
                        parent[n]=m;//将此边的结尾顶点放入下标为起点的parent中
                        printf("(%d, %d) %d\n", roads[i].a, roads[i].b, roads[i].w);
                }
        }

}

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
        int lowcost[maxSize],vset[maxSize],v;
        int i,min,j,k;
        v = v0;

        //vset[v0] = 1;//将v0并入树中
        for (i = 0; i < G.numNodes; ++i ) {
                lowcost[i] = G.arc[v0][i];//顶点v0到其余各顶点的距离
                //cout<<G.arc[v0][i]<<" ";
                vset[i] = 0;
        }
        vset[v] = 1;
        sum = 0;
        for (i= 0; i < G.numNodes - 1; ++i) {
                min = INF;
                for(j = 0; j < G.numNodes; ++j) // 找出候选边中的最小者
                        if (vset[j]==0&&lowcost[j]<min) { //选出当前生成树到其余各顶点最短边中的一条
                                min = lowcost[j];
                                k = j;
                        }
                vset[k] = 1;
                v = k;
                sum += min;        //sum记录了最小生成树的权值
                //以刚并入的顶点v为媒介更新候选边
                for(j = 0; j<G.numNodes; ++j)
                        if(vset[j]==0&&G.arc[v][j]<lowcost[j])
                                lowcost[j] = G.arc[v][j];         //过程2）

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
                        if (i==j)
                                G->arc[i][j]=0;
                        else
                                G->arc[i][j] = G->arc[j][i] = INF;
                }
        }
        G->arc[0][1]=10;
        G->arc[0][5]=11;
        G->arc[1][2]=18;
        G->arc[1][8]=12;
        G->arc[1][6]=16;
        G->arc[2][8]=8;
        G->arc[2][3]=22;
        G->arc[3][8]=21;
        G->arc[3][6]=24;
        G->arc[3][7]=16;
        G->arc[3][4]=20;
        G->arc[4][7]=7;
        G->arc[4][5]=26;
        G->arc[5][6]=17;
        G->arc[6][7]=19;
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
                        G->arc[i][j]=INF; // 邻接矩阵初始化
        for (k = 0; k < G->numEdges; k++) {
                cout<<"输入边(vi,vj)上的下标i，下标j和权w："<<endl;
                cin>> i >> j >> w;
                G->arc[i][j] = w;
                G->arc[j][i] = w;//无向图，矩阵对称
        }
}

void InitMGraphDemo(MGraph *G)
{
        int i, j;
        /* printf("请输入边数和顶点数:"); */
        G->numEdges=16;
        G->numNodes=9;
        for (i = 0; i < G->numNodes; i++) /* 初始化图 */
                G->vexs[i]=i;
        for (i = 0; i < G->numNodes; i++) /* 初始化图 */
                for ( j = 0; j < G->numNodes; j++) {
                        if (i==j)
                                G->arc[i][j]=0;
                        else
                                G->arc[i][j] = G->arc[j][i] = INF;
                }

        G->arc[0][1]=1;
        G->arc[0][2]=5;
        G->arc[1][2]=3;
        G->arc[1][3]=7;
        G->arc[1][4]=5;
        G->arc[2][4]=1;
        G->arc[2][5]=7;
        G->arc[3][4]=2;
        G->arc[3][6]=3;
        G->arc[4][5]=3;
        G->arc[4][6]=6;
        G->arc[4][7]=9;
        G->arc[5][7]=5;
        G->arc[6][7]=2;
        G->arc[6][8]=7;
        G->arc[7][8]=4;

        for(i = 0; i < G->numNodes; i++)
                for(j = i; j < G->numNodes; j++)
                        G->arc[j][i] =G->arc[i][j];



}

///////////////////增加图结构示意图//////////////////
int main(){
        // MGraph G;
        // CreateMGraph(&G);
        MGraph MG;
        //CreateALGraph(&Q);
        //CreateMGraphDemo(&MG);
        InitMGraphDemo(&MG);
        //  MiniSpanTree_PrimD(MG);
        //CreateMGraphD(&MG);
        //MGDFSTraverse(MG);
        //MGBFSTraverse(&MG);
        //GraphAdjList* GLDemo = NULL;
        //CreateALGraphDemo(MG,GLDemo);//利用邻接矩阵MG创建了邻接表GL
        //ALDFSTraverse(GL//Demo);
        //ALBFSTraverse(GLDemo);
        //int sum = 0;
        //int v0 = 0;
        //MiniSpanTree_Prim(MG,v0,sum);
        //cout<<"最小代价："<<sum<<endl;
        //MiniSpanTree_Kruskal(MG);
        //int v = 0;
        //int PATH[MG.numNodes],DIST[MG.numNodes];
        //ShortestPath_Dijkstra(MG,v,DIST,PATH);
        int Path[maxSize][maxSize];
        ShortestPath_Floyd(MG,Path);
        PrintPath_Floyd(0,5,Path);
        //PrintPath_Dijkstra(PATH,MG.numNodes);
        // for(int i = 0; i < MG.numNodes; i++) {
        //         cout<<"PATH:"<<i<<": "<<PATH[i]<<" ";
        //         cout<<"\n";
        //         //  cout<<"DIST:"<<DIST[i]<<" ";
        // }
        return 0;
}
