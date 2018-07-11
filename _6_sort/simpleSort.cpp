#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define maxSize 100

void InsertSort(int R[],int n);
void PrintArr(int R[],int n);
void PrintArr(int R[],int n){
        cout<<"开始输出数组"<<endl;
        int i = 0;
        for (i=0; i<n; i++) {
                cout<<R[i]<<"-";
        }
}
void InsertSort(int R[],int n){
        cout<<"直接插入排序"<<endl;
        //算法思想：每趟将一个待排序的关键字按照其值的大小插入到已经排好序的部分序列的适当位置上
        int i,j, temp;
        for (i=1; i<n; i++) {
                temp = R[i];
                j = i-1;

                // 下面这个循环完成了从待排关键字之前的关键字开始扫描，如果大于待排关键字，则后移一位
                while(j>=0&&temp<R[j]) {
                        R[j+1]=R[j];
                        --j;
                }
                R[j+1]=temp;//找到插入位置，将temp暂存的待排关键字插入
        }
}
int main() {
        /* code */
        int R[6] = {1,3,14,12,2,3};
        int n = 6;
        InsertSort(R,n);
        PrintArr(R,n);

        return 0;
}
