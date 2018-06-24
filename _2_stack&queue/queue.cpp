/**
 * @Author: XU BAI <by777>
 * @Date:   29/06/04
 * @Last modified by:   by777
 * @Last modified time: 06/06/18
 * @Copyright: All Rights Reserved.
 */
#include <iostream>
#include <stdlib.h>
#define maxSize 100
using namespace std;

typedef struct QNode {
        // 队列节点类型定义
        int data;
        struct QNode *next;
}QNode;

typedef struct {
        // 队列类型定义
        QNode *front;
        QNode *rear;
}LiQueue;

typedef struct sqQueue {
        char data[maxSize];
        int front;
        int rear;
}sqQueue;//静态队列

sqQueue initCirQueue(void);
void initLQueue(LiQueue *&q);
void enLQueue(LiQueue *q, int elem);
int isLQueueEmpty(LiQueue *q);
int inSqCircle(sqQueue &Q, int e);
int delSqCircle(sqQueue &Q,char &e);

int deLQueue(LiQueue *q, int &elem) {
        if (isLQueueEmpty(q) == 0) {
                return -1;
        }
        QNode *p = q->front;
        if (q->front == q->rear) {
                // 队列只有一个节点时，需要额外处理
                q->front = q->rear = NULL;
        }
        else{
                q->front = q->front->next;
        }
        elem = p->data;
        free(p);
        return 0;
}

void enLQueue(LiQueue *q, int elem){
        QNode *p = (QNode*)malloc(sizeof(QNode));
        p->data = elem;
        p->next = NULL;
        if (q->rear == NULL) {
                // 若队列为空，则新节点是队首节点也是队尾节点
                q->front = q->rear = p;
        }
        else{
                // 让新节点链接到链尾，让rear指向它
                q->rear->next = p;
                q->rear = p;
        }
}

int isLQueueEmpty(LiQueue *q){
        if (q->rear == NULL || q->front == NULL) {
                // 注意此处链队空的条件
                return 0;
        }
        else{
                return -1;
        }
}
void initLQueue(LiQueue *&q){
        q = (LiQueue*)malloc(sizeof(LiQueue));
        q->front = q->rear = NULL;
}

sqQueue initCirQueue(void){
        sqQueue Q;
        Q.front = Q.rear = 0;
        return Q;
}

int inSqCircle(sqQueue &Q, char e){
        if ((Q.rear+1)%maxSize == Q.front) {
                return -1;
        }
        // 插入数据后移动指针
        Q.data[Q.rear] = e;
        Q.rear = (Q.rear + 1) % maxSize;
        return 0;
}

int delSqCircle(sqQueue &Q,char &e){
        if (Q.front  == Q.rear) {
                cout<<"queue over "<<endl;
                return -1;
        }
        cout<<Q.data[Q.front];
        // 移除数据后移动指针
        Q.front = (Q.front + 1) % maxSize;
        return 0;
}


int main(){

/*
   静态循环队列
   sqQueue sq = initCirQueue();
   inSqCircle(sq,'b');
   char elem;
   delSqCircle(sq,elem);
   cout<<elem;
 */
/*
   链式队列的入队和出队
   LiQueue *q = NULL;
   int elem;
   initLQueue(q);
   enLQueue(q,1);enLQueue(q,2);enLQueue(q,3);
   deLQueue(q,elem);
 */

        return 0;
}
