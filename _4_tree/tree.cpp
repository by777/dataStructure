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

typedef struct BTNode {
        // 二叉链表节点
        ElemType data;
        struct BTNode *lChild;
        struct BTNode *rChild;
        //struct BTNode *parent;三叉链表节点
}BTNode;

typedef struct BiThrNode {
        ElemType data;
        struct BiThrNode *lChild,*rChild;
        int lTag,rTag;
}BiThrNode;

string str = "ABDH#K###E##CFI###G#J##";//注意叶子节点以空收尾
int index = 0;

status initBTree(BTNode *T);
int getDepth(BTNode *T);  // 计算二叉树深度
void createBTreeDemo(BTNode *&T);//快速创建一个二叉树
void PreOrderTraverse(BTNode *T);
void levelTraverse(BTNode *T);//层次遍历二叉树
void visit(BTNode *q);
void inBiThreadTree(BiThrNode *T,BiThrNode *&pre);//二叉树的中序线索化
void createInBiThreadTree(BiThrNode *root);//// 通过中序遍历建立中序线索二叉树的主程序
BiThrNode *first(BiThrNode *p);
BiThrNode *next(BiThrNode *p);
void inBiThrTraverse(BiThrNode *root);//遍历中序线索二叉树
void createBThTreeDemo(BiThrNode *&T);//快速创建未线索化的二叉树
void createBThTreeDemo(BiThrNode *&T){
        // 按照前序输入构造待线索化二叉树
        //cout<<"\n生成了一个还未线索化的二叉树"<<endl;
        char ch = str[index++];
        if (ch == '#') {
                T = NULL;
        }
        else{
                T =(BiThrNode*) malloc(sizeof(BiThrNode));
                if(!T) exit(-1);
                T->data = ch;//根节点
                createBThTreeDemo(*&T->lChild);
                if(T->lChild) /* 有左孩子 */
                        T->lTag=0;
                createBThTreeDemo(*&T->rChild);//递归创建子树
                if(T->rChild) /* 有右孩子 */
                        T->rTag=0;
        }
}

BiThrNode *first(BiThrNode *p){
        // 求以p为根的中序线索二叉树中，中序序列下的第一个节点
        while(p->lTag == 0) {
                p = p->lChild;
        }
        return p;
}

BiThrNode *next(BiThrNode *p){
        // 求以p为根的中序线索二叉树中，中序序列下后继节点
        if (p->rTag == 0) {
                return first(p->rChild);
        }
        else{
                return p->rChild;
        }
}

void inBiThrTraverse(BiThrNode *root){
        for(BiThrNode *p = first(root); p != NULL; p = next(p)) {
                cout<<p->data;
        }
}

void createInBiThreadTree(BiThrNode *root){
        // 通过中序遍历建立中序线索二叉树的主程序
        BiThrNode *pre = NULL;
        if (root != NULL) {
                inBiThreadTree(root,pre);
                pre->rChild = NULL;//非空二叉树，线索化
                pre->rTag = 1;//处理中序遍历最后一个节点
        }
}

void inBiThreadTree(BiThrNode *T,BiThrNode *&pre){
        /* 二叉树中序线索化分析：
         * 1）既然要对二叉树进行中序线索化，首先要有个中序遍历的框架，
         * 这里采用二叉树递归遍历算法，在遍历过程中连接上合适的线索即可
         * 2）线索化的规则是：左线索指针指向当前节点在中序遍历中的前驱节点，
         * 右线索指针指向其后继节点。
         * 因此我们需要一个指针p指向当前正在访问的节点，pre指向其前驱节点，
         * p的左线索如果存在则让其指向pre，pre的右线索如果存在则让其指向p。
         * 这样就完成了一对线索的连接，按照这样的规则遍历下去，遍历完成时，线索化结束
         * 3）上一步中pre始终指向p的前驱的具体过程是：
         * 当p将要离开一个访问过的节点时，pre指向p；
         */
        if (T==NULL)
                return;
        inBiThreadTree(T->lChild,pre);//递归，左子树线索化
        if( T->lChild == NULL) {
                //建立当前节点的前驱线索
                T->lChild = pre;
                T->lTag = 1;
        }
        if (pre != NULL && pre->rChild == NULL) {
                //建立当前节点的后继线索
                pre->rChild = T;
                pre->rTag = 1;
        }
        pre = T;
        T = T->rChild;
        inBiThreadTree(T,pre);
}

void visit(BTNode *q){
        if (q!=NULL) {
                cout<<q->data;
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
                                que[rear] = q->lChild;
                        }
                        if (q->rChild != NULL) {
                                rear = (rear + 1) % maxSize;
                                que[rear] = q->rChild;
                        }
                }
        }
}



int getDepth(BTNode *T){
        int LD,RD;
        if (T == NULL) {
                return 0;
        }
        else{
                LD = getDepth(T->lChild);
                RD = getDepth(T->rChild);
                return (LD > RD ? LD : RD) + 1;
        }
}

void PreOrderTraverse(BTNode *T){
        if(T==NULL) return;
        visit(T);
        PreOrderTraverse(T->lChild);
        //cout<<T -> data;中
        PreOrderTraverse(T->rChild);
        //cout<<T -> data;后
}

void createBTreeDemo(BTNode *&T){
        // 按照前序输入构造二叉树
        //cout<<"create"<<endl;
        char ch = str[index++];
        if (ch == '#') {
                T = NULL;
        }
        else{
                T =(BTNode*) malloc(sizeof(BTNode));
                if(!T) exit(-1);
                T->data = ch;//根节点
                createBTreeDemo(*&T->lChild);
                createBTreeDemo(*&T->rChild);//递归创建子树
        }
}

status initBTree(BTNode *T){
        T = NULL;
        return OK;
}

int main() {
        // BTNode *T;
        // initBTree(T);
        // createBTreeDemo(T);
        // cout<<"PreOrderTraverse"<<endl;
        // PreOrderTraverse(T);
        // cout<<"DEPTH"<<endl;
        // cout<<getDepth(T);
        // cout<<"levelTraverse"<<endl;
        // levelTraverse(T);
        BiThrNode *biTh;
        createBThTreeDemo(biTh);
        createInBiThreadTree(biTh);
        inBiThrTraverse(biTh);
        return 0;
}
