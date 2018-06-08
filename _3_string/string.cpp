#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define maxSize 256
using namespace std;

typedef struct{
  char strData[maxSize];
  int length;
}StringType;

typedef struct{
  char* ch;
  int length;
}LikStr;

int likStrAssign(LikStr &str, char *ch);

int strConcat(StringType &str, StringType substr);
void strInit(StringType &str, char strData[]);
void strPrint(StringType str);
int naiveComp(StringType str, StringType substr);
int naiveComp(StringType str, StringType substr){
  cout<<str.length<<" "<<substr.length;
  int i = 0;
  int j = 0;
  int k = i;
  while (i < str.length && j < substr.length) {
    if (str.strData[i] == substr.strData[j]) {
      cout<<"i="<<i<<endl;
      ++i;
      ++j;
    }
    else{
       j = 0;
       i=++k;//k记录上一次的起始位置
    }
  }
  cout<<k;
  if (j >= substr.length)  return k;
  else  return 0;
}
void strPrint(StringType str){
  for (int i = 0;i < str.length;++i) {
    cout<<str.strData[i]<<" ";
  }
}

void strInit(StringType &str, char strData[]){
  str.length = 0;
  int i;
  for (i = 0;strData[i]!= '\0';++i) {
    //cout<<strData[i]<<" ";
    str.strData[i] = strData[i];
    str.length++;
  }
  // str.strData[i] = '\0';
  // str.length++;
}

int strConcat(StringType &str, StringType substr){
  if (str.length + substr.length > maxSize) {
    return -1;
  }
  for (int i = 0;i<substr.length;++i) {
    str.strData[str.length + i] = substr.strData[i];
  }
  str.length = str.length + substr.length;
  return 0;
}

int main() {
  StringType str ;
  StringType subStr ;
  char strData[5] = {'b' , 'y' , '7' , '7' , '\0'};
  char subStrData[20] = {'7' , '7', '\0'};
  strInit(str,strData);
  strInit(subStr, subStrData);
  //strConcat(str, subStr);
  //strPrint(str);
  cout<<naiveComp(str,subStr);
  getchar();
  return 0;
}
