/**
 * @Author: XU BAI <by777>
 * @Date:   29/06/04
 * @Last modified by:   by777
 * @Last modified time: 04/06/18
 * @Copyright: All Rights Reserved.
 */
#include <iostream>
#include <stdlib.h>
#define maxSize 100
using namespace std;

typedef struct sqQueue{
  char data[maxSize];
  int front;
  int rear;
}sqQueue;

sqQueue initCirQueue(void);
int inSqCircle(sqQueue &Q, int e);
int delSqCircle(sqQueue &Q,char &e);

sqQueue initCirQueue(void){
  sqQueue Q;
  Q.front = Q.rear = 0;
  return Q;
}

int inSqCircle(sqQueue &Q, char e){
  if ((Q.rear+1)%maxSize == Q.front) {
    return -1;
  }
  // 插入数据后移动指针
  Q.data[Q.rear] = e;
  Q.rear = (Q.rear + 1) % maxSize;
  return 0;
}

int delSqCircle(sqQueue &Q,char &e){
  if (Q.front  == Q.rear) {
    cout<<"queue over "<<endl;
    return -1;
  }
  cout<<Q.data[Q.front];
  // 移除数据后移动指针
  Q.front = (Q.front + 1) % maxSize;
return 0;
}

int main(){

sqQueue sq = initCirQueue();
inSqCircle(sq,'b');
char elem;
delSqCircle(sq,elem);
cout<<elem;

return 0;
}
