#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define maxSize 100

typedef struct {
        int r[maxSize+1]; /* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
        int length; /* 用于记录顺序表的长度 */
}SqList;

void InsertSort(int R[],int n);
void QuickSort(int R[],int low,int high);
void ShellSort(int R[]);
void SelectSort(int R[],int n);
void SubMerge(int R[],int low,int mid,int high);
void MergeSort(int R[],int low,int high);
void PrintArr(int R[],int n);
void swap(int &a, int &b);
void swap(SqList *L,int i,int j);
void HeapAdjust(SqList *L, int s,int m);
void HeapSort(SqList *L);
void swap(SqList *L,int i,int j){
        int temp=L->r[i];
        L->r[i]=L->r[j];
        L->r[j]=temp;
}

void HeapSort(SqList *L){
        int i;
        for(i=L->length/2; i>0; i--) //把L中的r构建成一个大根堆
                HeapAdjust(L,i,L->length);
        for(i=L->length; i>1; i--) {
                swap(L,1,i);//将堆顶记录和当前未经排序子序列的最后一个记录交换
                HeapAdjust(L,1,i-1);//将L->r[1..i-1]重新调整为大根堆
        }
}

void HeapAdjust(SqList *L, int s,int m){
        /* 已知L->r[s..m]中记录的关键字除L->r[s]之外均满足堆的定义，
           本函数调整L->r[s]的关键字,使L->r[s..m]成为一个大顶堆 */
        int temp, j;
        temp = L->r[s];
        for(j=2*s; j<=m; j*=2) {//沿关键字较大的孩子结点向下筛选
                if (j < m && L->r[j] < L->r[j+1])
                        ++j; //j为关键字中较大的记录的下标
                if (temp >= L->r[j])
                        break; // rc应插入在位置s上
                L->r[s] = L->r[j];
                s = j;
        }
        L->r[s] = temp;  //插入
}

void SubMerge(int A[],int low,int mid,int high){
        int i,j,k;
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int L[n1];
        int R[n2];
        for(i = 0; i < n1; i++)
                L[i] = A[low + i];
        for(j = 0; j< n2; j++)
                R[j] = A[mid + 1 + j];
        i = 0, j=0, k = low;
        while (i < n1 && j < n2) {
                if (L[i] <= R[j])
                        A[k] = L[i++];
                else
                        A[k] = R[j++];
                k++;
        }
        while (i < n1)
                A[k++] = L[i++];
        while(j < n2)
                A[k++] = R[j++];
}

void MergeSort(int R[],int low,int high){
        int mid = (low + high) / 2;
        if (low < high) {
                MergeSort(R, low, mid);
                MergeSort(R, mid + 1, high);
                SubMerge(R, low, mid, high);
        }
}

void ShellSort(int R[],int n){
        int temp,gap;
        int i,j;
        for (gap = n/2; gap>0; gap /= 2) {
                for(i = gap; i<n; ++i)
                        temp = R[i];
                for(j=i; j>=gap&&R[j-gap]>temp; j-=gap)
                        R[j] = R[j-gap];
                R[j] = temp;
        }
}

void swap(int &a, int &b){
        int temp = a;
        a = b;
        b = temp;
}

void SelectSort(int R[],int n){
        //从头至尾顺序扫描序列，找出最小的一个关键字，和第一个关键字交换，重复。。
        cout<<"SelectSort:"<<endl;
        int i = 0,j;
        for (i=0; i<n; i++)
                for(j = i + 1; j < n; j++ )
                        if (R[j] < R[i])
                                swap(R[i],R[j]);



}

void QuickSort(int R[],int low,int high){
        int temp;
        int i = low,j = high;
        if (low<high) {
                temp=R[low];
                while (i<j) {
                        //下面这个循环完成了一趟排序，即数组中小于temp的关键字放在左边，
                        while (j>i&&R[j]>=temp) {
                                --j;//从右往左扫描，找到一个小于temp的关键字
                        }
                        if(i<j) {
                                R[i] = R[j];
                                ++i;
                        }
                        while (i<j&&R[i]<temp) {
                                ++i;
                        }
                        if (i<j) {
                                R[j]=R[i];
                                --j;
                        }
                }
                R[i] = temp;//将temp放在最终位置
                QuickSort(R,low,i-1);
                QuickSort(R,i+1,high);
        }
}


void InsertSort(int R[],int n){
        cout<<"直接插入排序"<<endl;
        //算法思想：每趟将一个待排序的关键字按照其值的大小插入到已经排好序的部分序列的适当位置上
        int i,j, temp;
        for (i=1; i<n; i++) {//将R[1]视作有序序列，从R[1]开始排序
                temp = R[i];
                j = i-1;
                // 下面这个循环完成了从待排关键字之前的关键字开始扫描，如果大于待排关键字，则后移一位
                while(j>=0&&temp<R[j]) {//从有序序列的最后一个值向前扫描找到恰当的位置
                        R[j+1]=R[j];
                        --j;
                }
                R[j+1]=temp;//找到插入位置，将temp暂存的待排关键字插入
        }
}

void PrintArr(int R[],int n){
        cout<<"\n开始输出数组"<<endl;
        int i = 0;
        for (i=0; i<n; i++)
                cout<<R[i]<<" ";

}

int main() {
        /* code */
        //int R[7] = {1,3,14,12,2,3};
        //  int n = 6;
        int i;
        #define N 9
        //InsertSort(R,n);
        //QuickSort(R,0,5);
        //SelectSort(R,n);
        //ShellSort(R,n);
        //MergeSort(R,0,5);
        SqList Al0;
        int d[N]={50,10,90,30,70,40,80,60,20};
        for(i=0; i<N; i++)
                Al0.r[i+1]=d[i];
        Al0.length=N;
        HeapSort(&Al0);
        //PrintArr(R,n);
        //
        return 0;
}
