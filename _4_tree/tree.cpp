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
void PreOrderTraverse(BTNode *T){
  if(T==NULL)  return;
  cout<<T -> data;
  PreOrderTraverse(T->lChild);
  PreOrderTraverse(T->rChild);
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
  return 0;
}
