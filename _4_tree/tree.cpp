#include <iostream>
#include <stdlib.h>
#include <string.h>
#define maxSize 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef char ElemType;
typedef int status;
using namespace std;

typedef struct BTNode{
  // 二叉链表节点
  ElemType data;
  struct BTNode *lChild;
  struct BTNode *rChild;
  //struct BTNode *parent;三叉链表节点
}BTNode;

string str = "ABDH#K###E##CFI###G#J##";//注意叶子节点以空收尾
int index = 0;

status initBTree(BTNode *T);
void createBTree(BTNode *&T);
void PreOrderTraverse(BTNode *T);
void levelTraverse(BTNode *T);//层次遍历二叉树
void visit(BTNode *q);
void visit(BTNode *q){
  if (q!=NULL) {
    cout<<q -> data;
  }
}

void levelTraverse(BTNode *T){
  /* 先将二叉树头节点入队列，然后出队列，访问该节点，
   * 如果它有左子树，
   * 则将 ||左子树|| 的根节点入队；
   * 如果它有右子树， 则将 ||右子树|| 的根节点入队
   * 然后出队，对出队节点访问，直至队列为空
  */
  int front, rear;
  BTNode *que[maxSize];//使用循环队列层次遍历二叉树
  front = rear = 0;
  BTNode *q;
  if (T != NULL) {
    rear = (rear + 1) % maxSize;
    que[rear] = T;
    while (front != rear) {
      front = (front + 1) % maxSize;
      q = que[front];//头节点出队
      visit(q);
      if (q->lChild != NULL) {
        rear = (rear + 1) % maxSize;
        que[rear] = q -> lChild;
      }
      if (q->rChild != NULL) {
        rear = (rear + 1) % maxSize;
        que[rear] = q -> rChild;
      }
    }
  }
}

int getDepth(BTNode *T);  // 计算二叉树深度

int getDepth(BTNode *T){
  int LD,RD;
  if (T == NULL) {
    return 0;
  }
  else{
    LD = getDepth(T -> lChild);
    RD = getDepth(T -> rChild);
    return (LD > RD ? LD : RD) + 1;
  }
}

void PreOrderTraverse(BTNode *T){
  if(T==NULL)  return;
  visit(T);
  PreOrderTraverse(T->lChild);
  //cout<<T -> data;中
  PreOrderTraverse(T->rChild);
    //cout<<T -> data;后
}

void createBTree(BTNode *&T){
  // 按照前序输入构造二叉树
  //cout<<"create"<<endl;
  char ch = str[index++];
  if (ch == '#') {
    T = NULL;
  }
  else{
    T =(BTNode*) malloc(sizeof(BTNode));
    if(!T)  exit(-1);
    T -> data = ch;//根节点
    createBTree(*&T -> lChild);
    createBTree(*&T -> rChild);//递归创建子树
  }
}

status initBTree(BTNode *T){
  T = NULL;
  return OK;
}

int main() {
  BTNode *T;
  initBTree(T);
  createBTree(T);
  cout<<"PreOrderTraverse"<<endl;
  PreOrderTraverse(T);
  cout<<"DEPTH"<<endl;
  cout<<getDepth(T);
  cout<<"levelTraverse"<<endl;
  levelTraverse(T);
  return 0;
}
