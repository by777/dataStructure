// Copyright (c) 2018 by XU BAI. All Rights Reserved.
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct LNode{
  int data;
  struct LNode* next;
}LNode;

LNode* createliklist(void);//尾插法
LNode* createliklistH(void);//头插法
LNode* chooseCreate(int choose);
LNode* createliklistManu(int a[], int len);
void inversion(LNode *head);//逆置
LNode* mergelik(LNode *head_1,LNode *head_2);//合并有序链表
void visitliklist(LNode *head);
void delElement(LNode* head, int x);//按值删除

LNode* createliklistH(void){
  LNode* head, *p;
  head = (LNode*)malloc(sizeof(LNode));
  head -> next = NULL;// 不可缺少

  for (int i = 10; i <= 20; ++i) {
    /* code */
    p = (LNode*)malloc(sizeof(LNode));
    p -> data = i;

    p -> next = head -> next;
    head -> next = p;
  }
  return head;
}

LNode* createliklist(void){
  /* 尾插法 */
  LNode *head, *p, *q;
  head = p = (LNode *)malloc(sizeof(LNode));
  p ->next = NULL;
  for(int i = 0; i <= 10 ; i++){
    q = (LNode *)malloc(sizeof(LNode));
    q -> data = i;
    q -> next = p -> next;
    p -> next = q;
    p = q;
  }
  return head;
}

void visitliklist(LNode *head){
  cout<<"----------visit-----------"<<endl;
  LNode *v = head -> next;
  while (v) {
    cout<<v -> data<<" ";
    v = v -> next;
  }
  cout<<endl;
}

LNode* chooseCreate(int choose){
  LNode* head = NULL;
  switch (choose) {
    case 1:head = createliklist();break;
    case 2:head = createliklistH();break;
  }
  return head;
}

void delElement(LNode* head, int x){
  //删除值为x的第一个元素
  LNode *p = head ;
  LNode *q = p -> next;
  while (q!=NULL&&q->data!=x) {
    /* code */
    p = q;
    q = q -> next;
  }
  // 此处教材错误，若不判断先q是否为空将无法继续执行
  if (q!=NULL&&q->data==x) {
    /* code */
    p -> next = q -> next;
    free(q);
  }
  else{
    cout<<"NOT MATCHED"<<endl;
  }
}

LNode* createliklistManu(int a[], int len){

  LNode *head = NULL;
  head = (LNode*)malloc(sizeof(LNode));
  LNode *p = head ;
  p -> next = NULL;
  for(int i = 0; i < len; ++i){
    LNode *q = NULL;
    q = (LNode*)malloc(sizeof(LNode));
    q -> data = a[i];
    q -> next = p -> next;
    p -> next = q;
    p = q;
  }
  return head;
}

void inversion(LNode *head){
  // 逆置链表
  // 保存head后继节点，取下head，遍历剩余节点，前插法插入head
  LNode *p = head -> next;
  LNode *q = NULL;
  head -> next = NULL;
  while (p!=NULL) {
    /* code */
     q = p;
     p = p -> next;
     q -> next = head -> next;
     head -> next = q;//q前插入操作

  }
}

LNode* mergelik(LNode *La, LNode *Lb) {
  LNode *Lc, *pc, *ptr;
  Lc = La;
  pc = La;
  LNode *pa = La -> next;
  LNode *pb = Lb -> next;
  while (pa!=NULL&&pb!=NULL) {
    if (pa -> data < pb -> data) {
      // 将pa所指的节点合并，pc、pa指向下一个节点
      pc -> next = pa;
      pc = pa;
      pa = pa -> next;
    }
    else if (pa -> data > pb -> data) {
      pc -> next = pb;
      pc = pb;
      pb = pb -> next;
    }
    else{
      pc -> next = pa;
      pc = pa;
      pa = pa -> next;
      ptr = pb;
      pb = pb -> next;
      free(ptr);
    }
    if (pa!=NULL){
      pc -> next = pa;
    }
    if (pb!=NULL) {
      pc -> next = pb;
    }
  }
  free(Lb);
  return Lc;
}

int main() {
  /*
  cout<<"createliklist(1) or createliklistH(2)?"<<endl;
  int choose;cin>>choose;
  LNode* head = chooseCreate(choose);
  visitliklist(head);cout<<endl;
  int value;cin>>value;
  delElement(head, value);
  visitliklist(head);
  */

  int a[] = {0,1,5,11,20};
  LNode *head_1 = createliklistManu(a,5);
  int b[] = {0,2,4,5,11,22};
  LNode *head_2 = createliklistManu(b,6);
  LNode* merResult = mergelik(head_1, head_2);
  visitliklist(merResult);

  return 0;
}