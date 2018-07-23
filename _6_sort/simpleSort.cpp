#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define maxSize 100

void InsertSort(int R[],int n);
void QuickSort(int R[],int low,int high);
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

int main() {
        /* code */
        int R[6] = {1,3,14,12,2,3};
        int n = 6;
        //InsertSort(R,n);
        QuickSort(R,0,5);
        PrintArr(R,n);

        return 0;
}
