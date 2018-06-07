#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define maxSize 256
using namespace std;

typedef struct{
  char strData[maxSize];
  int length;
}StringType;

int strConcat(StringType str, StringType substr);
void strInit(StringType &str, char strData[]);
void strPrint(StringType str);

void strPrint(StringType str){
  for (int i = 0;str.strData[i]!= '\0';i++) {
    cout<<str.strData[i-1]<<" ";
  }
}

void strInit(StringType &str, char strData[]){
  for (int i = 0;strData[i]!= '\0';i++) {
    str.strData[i] = strData[i];
  }
}

int strConcat(StringType str, StringType substr){
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
  char strData[5] = {'a' , 'b' , 'c' , 'd' , '\0'};
  strInit(str,strData);
  strPrint(str);
  getchar();
  return 0;
}
