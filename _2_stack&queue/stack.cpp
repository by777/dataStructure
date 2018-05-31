/**
 * @Author: XU BAI <by777>
 * @Date:   29/05/18
 * @Last modified by:   by777
 * @Last modified time: 31/05/18
 * @Copyright: All Rights Reserved.
 */
#include <iostream>
#include <stdlib.h>
#define maxSize 100
#define STACKINCREMENT 10
#define STACKSIZE 100
using namespace std;

typedef struct sqStack{
  int elem[maxSize];
  int top;
}sqStack;

typedef struct stackNode{
  int data;
  struct stackNode* next;

}stackNode;


int chooseOptions();

sqStack initSqStack();
int sqPush(sqStack* sqstack, int a[], int length);
int sqPop(sqStack* sqstack, int &elem);

stackNode* initstackNode();
int likPush(stackNode* top, int data);

int chooseOptions(){
  cout<<"plz choose stackNode(1) or sqStack(2)"<<endl;
  int option;
  cin>>option;
  switch (option) {
    case 1:cout<<"..."<<endl;break;
    case 2:initSqStack();break;
    default: chooseOptions();
  }
  return option;
}

sqStack initSqStack(){
  sqStack stack ;
  stack.top = -1;
  return stack;
}

int sqPush(sqStack* sqstack, int a[], int length){
  if (sqstack->top==maxSize-1) {
    cout<<"stackover"<<endl;
    return 0;
  }

  for (int i = 0;i < length; ++i) {
    sqstack->elem[++sqstack->top] = i;
  }
  return 0;
}

int sqPop(sqStack* sqstack, int &elem){

  if (sqstack->top == -1) {
    cout<<"stack empty"<<endl;
    return sqstack->top;
  }
  elem = sqstack->elem[sqstack->top--];
  return sqstack->top;
}

stackNode* initstackNode(){
  stackNode* top;
  top = (stackNode*)malloc(sizeof(stackNode));
  top -> next = NULL;
  return (top);

}

int likPush(stackNode* top, int data){
  stackNode* p;
  p = (stackNode*)malloc(sizeof(stackNode));
  if (!p) {
    return -1;
  }
  p -> data = data;
  //尾插
  p -> next = top -> next;
  top -> next = p;
  return 0;

}

int main() {
  sqStack sqstack =  initSqStack();
  int a[10] = {0,1,2,3,4,5,6,7,8,9};
  int length = 11;
  sqPush(&sqstack,a,length);
  int elem;
  while (sqstack.top!=-1) {
    //flag > 0 ,elem接收pop
    cout<<sqPop(&sqstack,elem);
  }



  //chooseOptions();

   return 0;
 }
