/**
 * @Author: XU BAI <by777>
 * @Date:   29/05/18
 * @Last modified by:   by777
 * @Last modified time: 29/05/18
 * @Copyright: All Rights Reserved.
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define maxSize 1000
using namespace std;

typedef struct LNode {
        int data;
        struct LNode* next;
}LNode;

typedef struct {
        //线性表的静态链表存储结构
        char data;
        int cur;//游标（cursor），为0时表示无指向
}Component,StaticLinkList[maxSize];

LNode* createliklist (void);//尾插法
LNode* createliklistH(void);//头插法
LNode* chooseCreate(int choose);//主选择
LNode* createliklistManu(int a[], int len);//手工创建链表
LNode* mergelik(LNode *head_1,LNode *head_2);//合并有序链表
void visitliklist(LNode *head);//遍历
void delElement(LNode* head, int x);//按值删除
void inversion(LNode *head);//逆置
int initStaticList(StaticLinkList &space);
int mallocSSL(StaticLinkList &space);
void freeSSL(StaticLinkList &space,int k);//将下标为k的空闲节点回收到备用链表
int staticListLength(StaticLinkList L);// 获取静态链表长度
int staticListInsert(StaticLinkList &L,int i,char e);
int staticListDel(StaticLinkList &L,int i);  //删除在L中第i个数据元素
int staticListTraverse(StaticLinkList L);// 遍历静态链表
void staticListTest1();// 静态链表的测试用例

int staticListTraverse(StaticLinkList L){
        int j = 0;
        int i = L[maxSize-1].cur;
        while (i) {
                cout<<L[i].data;
                i = L[i].cur;
                j++;
        }
        return j;
        cout<<endl;
        return 0;
}

int staticListDel(StaticLinkList &L,int i){
        //删除在L中第i个数据元素
        int k,j;
        if (i < 1 || i > staticListLength(L)) {
                return -1;
        }
        k = maxSize -1;
        for (j = 1; j <= i -1; j++) {
                k = L[k].cur;
        }
        j = L[k].cur;
        L[k].cur = L[j].cur;
        freeSSL(L,j);
        return 0;
}

int staticListInsert(StaticLinkList &L,int i,char e){
        int k,j,l;
        k = maxSize - 1;//k是最后一个元素的下标
        if (i < 1 || i > staticListLength(L) + 1) {
                return -1;
        }
        j = mallocSSL(L);//获取空闲分量的下标
        if (j) {
                L[j].data=e;
                for (l = 1; l <= i -1; l++) {
                        // 找到第i个元素之前的位置
                        k = L[k].cur;
                }
                L[j].cur = L[k].cur;//将第i个元素之前的cur赋值给新元素的cur
                L[k].cur = j;//将新元素的下标赋值给第i个元素之前的元素cur
                return 0;
        }
        return -1;
}

int staticListLength(StaticLinkList L){
        int j = 0;
        int i = L[maxSize-1].cur;
        while (i) {
                i = L[i].cur;
                j++;
        }
        return j;
}

void freeSSL(StaticLinkList &space,int k){
        //将下标为k的空闲结点回收到备用链表
        space[k].cur = space[0].cur;
        space[0].cur = k;
}

int initStaticList(StaticLinkList &space){
        // 将一维数组space中各分量链成一个备用链表，space[0].cur为头指针，‘0’表示空指针
        int i;
        for (i = 0; i < maxSize - 1; i++)
                space[i].cur = i + 1;
        space[maxSize-1].cur = 0;// 目前静态链表为空，最后一个元素的cur为0
        return 0;
}

int mallocSSL(StaticLinkList &space){
        // 若备用空间链表为空则返回分配的节点下标，否则返回0
        int i = space[0].cur;
        if (space[0].cur) {
                space[0].cur = space[i].cur;
                /* 由于要拿出一个分量来使用了， */
                /* 所以我们就得把它的下一个 */
                /* 分量用来做备用 */
        }
        return i;
}

LNode* createliklistH(void){
        LNode* head, *p;
        head = (LNode*)malloc(sizeof(LNode));
        head->next = NULL;// 不可缺少

        for (int i = 10; i <= 20; ++i) {
                /* code */
                p = (LNode*)malloc(sizeof(LNode));
                p->data = i;
                p->next = head->next;
                head->next = p;
        }
        return head;
}

LNode* createliklist(void){
        /* 尾插法 */
        LNode *head, *p, *q;
        head = p = (LNode *)malloc(sizeof(LNode));
        p->next = NULL;
        for(int i = 0; i <= 10; i++) {
                q = (LNode *)malloc(sizeof(LNode));
                q->data = i;
                q->next = p->next;
                p->next = q;
                p = q;
        }
        return head;
}

void visitliklist(LNode *head){
        cout<<"-#-"<<endl;

        if (head->next == NULL||head==NULL) {
                cout<<"plz create linklist first!"<<endl;
                return;
        }
        cout<<"----------visit-----------"<<endl;
        LNode *v = head->next;
        while (v) {
                cout<<v->data<<" ";
                v = v->next;
        }
        cout<<endl;
}

LNode* chooseCreate(){
        int option;
        cout<<"#####################################################"<<endl;
        cout<<"#                                                   #"<<endl;
        cout<<"#                                                   #"<<endl;
        cout<<"# 1.Create linklist with tail interpolation         #"<<endl;
        cout<<"# 2.Create linklist with head interpolation         #"<<endl;
        cout<<"# 3.Traversal                                       #"<<endl;
        cout<<"# 3.Create linklist manually                        #"<<endl;
        cout<<"# 4.Delete element by value                         #"<<endl;
        cout<<"# 5.Traversal element linklist                      #"<<endl;
        cout<<"# 6.Merge two linklist                              #"<<endl;
        cout<<"#                                                   #"<<endl;
        cout<<"#####################################################"<<endl;

        cin>>option;
        LNode* head = NULL;
        head->next = NULL;
        switch (option) {
        case 1: head = createliklist(); break;
        case 2: head = createliklistH(); break;
        // case 3:visitliklist(head);break;
        default: chooseCreate();
        }
        return head;
}

void delElement(LNode* head, int x){
        //删除值为x的第一个元素
        if (head->next == NULL) {
                cout<<"plz create linklist first!"<<endl;
                return;
        }
        LNode *p = head;
        LNode *q = p->next;
        while (q!=NULL&&q->data!=x) {
                /* code */
                p = q;
                q = q->next;
        }
        // 此处参考教材错误，若不判断先q是否为空将无法继续执行
        if (q!=NULL&&q->data==x) {
                /* code */
                p->next = q->next;
                free(q);
        }
        else{
                cout<<"NOT MATCHED"<<endl;
        }
}

LNode* createliklistManu(int a[], int len){

        LNode *head = NULL;
        head = (LNode*)malloc(sizeof(LNode));
        LNode *p = head;
        p->next = NULL;
        for(int i = 0; i < len; ++i) {
                LNode *q = NULL;
                q = (LNode*)malloc(sizeof(LNode));
                q->data = a[i];
                q->next = p->next;
                p->next = q;
                p = q;
        }
        return head;
}

void inversion(LNode *head){
        // 逆置链表
        // 保存head后继节点，取下head，遍历剩余节点，前插法插入head
        if (head->next == NULL) {
                cout<<"plz create linklist first!"<<endl;
                return;
        }
        LNode *p = head->next;
        LNode *q = NULL;
        head->next = NULL;
        while (p!=NULL) {
                /* code */
                q = p;
                p = p->next;
                q->next = head->next;
                head->next = q;//q前插入操作
        }
}

LNode* mergelik(LNode *La, LNode *Lb) {
        if (La->next == NULL || Lb->next == NULL) {
                cout<<"plz create two linklist first!"<<endl;
                return NULL;
        }
        LNode *Lc, *pc, *ptr;
        Lc = La;
        pc = La;
        LNode *pa = La->next;
        LNode *pb = Lb->next;
        while (pa!=NULL&&pb!=NULL) {
                if (pa->data < pb->data) {
                        // 将pa所指的节点合并，pc、pa指向下一个节点
                        pc->next = pa;
                        pc = pa;
                        pa = pa->next;
                }
                else if (pa->data > pb->data) {
                        pc->next = pb;
                        pc = pb;
                        pb = pb->next;
                }
                else{
                        pc->next = pa;
                        pc = pa;
                        pa = pa->next;
                        ptr = pb;
                        pb = pb->next;
                        free(ptr);
                }
                if (pa!=NULL) {
                        pc->next = pa;
                }
                if (pb!=NULL) {
                        pc->next = pb;
                }
        }
        free(Lb);
        return Lc;
}

void staticListTest1(){
        StaticLinkList L;
        initStaticList(L);
        int i;
        i=staticListInsert(L,1,'F');
        i=staticListInsert(L,1,'E');
        i=staticListInsert(L,1,'D');
        i=staticListInsert(L,1,'B');
        i=staticListInsert(L,1,'A');
        printf("\n在L的表头依次插入FEDBA后：\n");
        staticListTraverse(L);
        i=staticListInsert(L,3,'C');
        printf("\n在L的“B”与“D”之间插入“C”后：\n");
        staticListTraverse(L);
        i=staticListDel(L,1);
        printf("\n在L的删除“A”后：\n");
        staticListTraverse(L);
        printf("\n");
}

int main() {
        /*
           int value;cin>>value;
           delElement(head, value);
           visitliklist(head);
         */


        LNode* head = chooseCreate();
        visitliklist(head); cout<<endl;

        int a[] = {0,1,5,11,20};
        LNode *head_1 = createliklistManu(a,5);
        int b[] = {0,2,4,5,11,22};
        LNode *head_2 = createliklistManu(b,6);
        LNode* merResult = mergelik(head_1, head_2);
        visitliklist(merResult);
        getchar();
        return 0;
}
