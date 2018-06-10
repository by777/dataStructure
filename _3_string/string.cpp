#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define maxSize 256
using namespace std;

typedef struct{
  char strData[maxSize+1];
  int length;
}StringType;

typedef struct{
  char* ch;
  int length;
}LikStr;

void getNext(StringType substr, int next[]);
void vLikStr(LikStr likstr);
void sqStrAssign(StringType &str, char strData[]);
void strPrint(StringType str);
int likStrAssign(LikStr &str, char *ch);
int strConcat(StringType &str, StringType substr);
int naiveComp(StringType str, StringType substr);
int KMP(StringType str, StringType substr, int next[]);

void vLikStr(LikStr likstr){
  LikStr l = likstr;
  int i = 0;
  if (l.length == 0) {
    cout<<"NULL STRING";
    return;
  }

  while (i < l.length) {
    cout<<l.ch[i];
    ++i;
  }
}

int likStrAssign(LikStr &str, char *ch){
  if (str.ch) {
    free(str.ch);
  }

  int len = 0;
  char *c = ch;

  while (*c) {
    ++len;
    ++c;
  }

  if (len == 0) {
    str.ch = NULL;
    str.length = 0;
    return 1;
  }

  else{
    str.ch = (char*)malloc(sizeof(char) * (len + 1));
    // 为 ‘\0’预留空间
    if(str.ch == NULL){
      return -1;
    }

    else{
      c = ch;
      for(int i = 0; i <= len; ++i, ++c){
        str.ch[i] = *c;
        //cout<<str.ch[i];
      }

      str.length = len;
      return 1;
    }
  }
}

int KMP(StringType str, StringType substr, int next[]){
  int i = 0, j = 0;

  while (i <= str.length && j <= substr.length) {

    if (j == 0 || str.strData[i] == substr.strData[j]) {
      ++i;
      ++j;
    }

    else{
      j = next[j];//
    }
  }

  if (j > substr.length) {
    return i - substr.length;
  }
  else{
    return -1;
  }

}

void getNext(StringType substr, int next[]){
  int i = 1, j = 0;
  next[1] = 0;
  while (i < substr.length) {
    if (j == 0 || substr.strData[i] == substr.strData[j]) {
      ++i;
      ++j;
      next[i] = j;////////////
    }
    else{
      j = next[j];//
    }
  }
}

int naiveComp(StringType str, StringType substr){

  int i = 0;
  int j = 0;
  int k = i;

  while (i <= str.length && j <= substr.length) {
    cout<<str.strData[i] <<"VS"<< substr.strData[j]<<endl;
    if (str.strData[i] == substr.strData[j]) {
      ++i;
      ++j;
    }
    else{
       j = 0;
       i=++k;//k记录上一次的起始位置
    }
  }

  if (j > substr.length)  return k+1;
  else  return -1;
}

void strPrint(StringType str){
  for (int i = 0;i < str.length;++i) {
    cout<<str.strData[i]<<" ";
  }
}

void sqStrAssign(StringType &str, char strData[]){
  str.length = 0;
  int i;
  for (i = 0;strData[i]!= '\0';++i) {
    str.strData[i] = strData[i];
    str.length++;
  }
  str.strData[i] = '\0';
  //str.length++;
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
  // StringType str ;
  // StringType subStr ;
  // char strData[6] = {'b' , 'y' , '1' , '7' ,'7' , '\0'};
  // char subStrData[20] = {'7' , '9', '\0'};
  // sqStrAssign(str,strData);
  // sqStrAssign(subStr, subStrData);
  // strConcat(str, subStr);
  // strPrint(str);
  // cout<<str.length<<endl;
  // cout<<naiveComp(str,subStr);
  LikStr likstr;
  likStrAssign(likstr,"abcd");
  vLikStr(likstr);
  getchar();
  return 0;
}
