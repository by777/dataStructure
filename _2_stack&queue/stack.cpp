/**
 * @Author: XU BAI <by777>
 * @Date:   29/05/18
 * @Last modified by:   by777
 * @Last modified time: 29/05/18
 * @Copyright: All Rights Reserved.
 */
#include <iostream>
#include <stdlib.h>
#define maxSize 100
using namespace std;

typedef struct sqStack{
  int elem[maxSize];
  int top;
}sqStack;

typedef struct likStack{
  int* bottom;
  int* top;
  int* stacksize;
}likStack;


int chooseOptions();
sqStack initSqStack();
int sqPush(sqStack sqstack, int a[], int length);
int sqPop(sqStack sqstack);

int chooseOptions(){
  cout<<"plz choose likStack(1) or sqStack(2)"<<endl;
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

int sqPush(sqStack sqstack, int a[], int length){
  if (sqstack.top==maxSize-1) {
    cout<<"stackover"<<endl;
    return 0;
  }

  // for (int i = 0;i < length; ++i) {
  //   cout<<i<<" ";
  //   ++sqstack.top;
  //   cout<<sqstack.top;
  //   sqstack.elem[sqstack.top] = i;
  // }
  return 1;
}

int sqPop(sqStack sqstack){
  if (sqstack.top == -1) {
    cout<<"stack empty"<<endl;
    return -32767;
  }
  // return sqstack.elem[sqstack.top--];
  return -32767;
}

int main() {
  // sqStack sqstack =  initSqStack();
  // int a[10] = {0,1,2,3,4,5,6,7,8,9};
  // int length = 10;
  // sqPush(sqstack,a,length);
  // cout<<sqstack.top<<endl;
  // int i;
  // while (sqstack.top != -1) {
  //   i = sqPop(sqstack);
  //   cout<<i<<" "<<endl;
  // }
  chooseOptions();

   return 0;
 }
