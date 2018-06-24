/**
 * @Author: XU BAI <by777>
 * @Date:   29/05/18
 * @Last modified by:   by777
 * @Last modified time: 31/05/18
 * @Copyright: All Rights Reserved.
 */
#include <iostream>
#include <stdlib.h>
#define maxSize 20
#define STACKINCREMENT 10
#define STACKSIZE 100
using namespace std;

typedef struct sqStack {
        int elem[maxSize];
        int top;
}sqStack;

typedef struct stackNode {
        int data;
        struct stackNode* next;

}stackNode;

typedef struct {
        int data[maxSize];
        int top1;
        int top2;
}SqDoubleStack;//两栈共享空间

int chooseOptions();
sqStack initSqStack();//初始顺序栈
int sqPush(sqStack* sqstack, int a[], int length);//压顺序栈
int sqPop(sqStack* sqstack, int &elem);//出顺序栈
void initstackNode(stackNode *&top);
void likPush(stackNode* top, int data);//链栈的
int likPop(stackNode* top,int &elem);
int LIsEmpty(stackNode *top);
int visit(int elem);
int initDSTACK(SqDoubleStack &s);// 共享栈
int stackDPUSH(SqDoubleStack &s, int elem,int stackNum);
int stackDPOP(SqDoubleStack &s,int &elem,int stackNum);
int stackDTRAVERSE(SqDoubleStack s);

int stackDTRAVERSE(SqDoubleStack s){
        int i = 0;
        cout<<"Begin traverse stack1"<<endl;
        while (i <= s.top1) {
                visit(s.data[i++]);
        }
        cout<<endl;
        i = s.top2;
        cout<<"Begin traverse stack2"<<endl;
        while (i < maxSize) {
                visit(s.data[i++]);
        }
        return 0;
}

int stackDPOP(SqDoubleStack &s,int &elem,int stackNum){
        if (stackNum == 1) {
                if(s.top1== -1) return -1; //栈1空
                elem = s.data[s.top1--];
        }
        if (stackNum == 2) {
                if(s.top2 == maxSize) return -2; //栈2空
                elem = s.data[s.top2++];//栈2 要小心不要大意
                cout<<elem;
        }
        return 0;
}

int stackDPUSH(SqDoubleStack &s, int elem,int stackNum){
        if (s.top1 + 1 == s.top2) return -1; //
        if (stackNum == 1) {
                s.data[++s.top1] = elem;
        }
        else{
                s.data[--s.top2] = elem;
        }
        return 0;
}

int initDSTACK(SqDoubleStack &s){
        s.top1 = -1;
        s.top2 = maxSize;
        return 0;
}
int visit(int elem){
        cout<<elem<<" ";
        return 0;
}

int LIsEmpty(stackNode *top){
        if (top->next == NULL) {
                return 0;
        }
        else{
                return -1;
        }
}

int chooseOptions(){
        cout<<"plz choose stackNode(1) or sqStack(2)"<<endl;
        int option;
        cin>>option;
        switch (option) {
        case 1: cout<<"..."<<endl; break;
        case 2: initSqStack(); break;
        default: chooseOptions();
        }
        return option;
}

sqStack initSqStack(){
        sqStack stack;
        stack.top = -1;
        return stack;
}

int sqPush(sqStack* sqstack, int a[], int length){
        if (sqstack->top==maxSize-1) {
                cout<<"stackover"<<endl;
                return 0;
        }

        for (int i = 0; i < length; ++i) {
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

void initstackNode(stackNode *&top){
        top = (stackNode*)malloc(sizeof(stackNode));
        top->next = NULL;
}

void likPush(stackNode* top, int data){
        stackNode* p;
        p = (stackNode*)malloc(sizeof(stackNode));
        p->next = NULL;
        p->data = data;
        //尾插
        p->next = top->next;
        top->next = p;
}

int likPop(stackNode* top, int &elem){
        if (top->next == NULL) {
                return -1;
        }
        stackNode *p = top->next;
        elem = p->data;
        top->next = p->next;
        free(p);
        return 0;
}

int main() {
        //sqStack sqstack =  initSqStack();
        // int a[10] = {0,1,2,3,4,5,6,7,8,9};
        // int length = 10;
        // // sqPush(&sqstack,a,length);
        // stackNode *top ;
        // initstackNode(top);
        // int i;
        // for (i = 0;i < length; i++) {
        //   likPush(top,a[i]);
        // }
        // int elem;
        // while (likPop(top,elem)!=-1) {
        //   cout<<elem<<" ";
        // }
        //chooseOptions();
        int j = 0;
        int e;
        //cout<<"Int-type size:"<<sizeof(j)<<endl;
        SqDoubleStack s;
        initDSTACK(s);
        for(j=1; j<=5; j++) stackDPUSH(s,j,1);
        for(j=maxSize; j>=maxSize-2; j--) stackDPUSH(s,j,2);
        cout<<"--Traverse share-stack elem--"<<endl;
        stackDTRAVERSE(s);
        stackDPOP(s,e,2);
        cout<<"POP ELEM:"<<e;
        return 0;
}
