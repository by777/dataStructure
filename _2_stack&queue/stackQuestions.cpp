/* #1
 * C语言里算术表达式中的括号只有小括号。编写算法，
 * 判断一个表达式中的括号是否正确配对，表达式已经
 * 存在字符数组exp[]中，表达式字符个数为n
 *
 * #2
 * 编写一个函数，求后缀式的值，后缀式exp[]以‘\0’作为结束
 * 并假设数字为1位，所有数字可整除
 *
 * #3
 * 十进制整数向其它进制数d（二、八、十六）的转换
 * 转换法则： n = (n div d) * d + n mod d
 * 其中：div为整除运算，mod
 */
#include <iostream>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define STACKOVER -1
#define maxSize 100
using namespace std;

int match(char exp[],int n);
int op(int a,char Op, int b);
int com(char exp[]);
void conversion(int n, int d);
void conversion(int n, int d){
/* #3 */
        int stack[maxSize];
        int top = -1;
        int k;
        while (n > 0) {
                k = n % d;
                stack[++top] = k;
                n = n / d;
        }
        while (top != -1) {
                cout<<stack[top--];

        }

}
int match(char exp[], int n){
/* #1 */
        char stack[maxSize];
        int top = -1;
        for (int i = 0; i < n; i++) {
                if (exp[i] == '(') {
                        stack[++top] = exp[i];
                }
                if(exp[i] == ')') {
                        if (top != -1) {
                                top--;
                        }
                        else{
                                return ERROR;
                        }
                }
        }
        return OK;
}

int op(int a,char Op, int b){
        if (Op == '+') return a + b;
        if (Op == '-') return a - b;
        if (Op == '*') return a * b;
        if (Op == '/') {
                if (b == 0) {
                        std::cout << "ERROR" << '\n';
                        return ERROR;
                }
                else{
                        return a / b;
                }
        }
        return ERROR;
}

int com(char exp[]){
        /* #2 */
        int stack[maxSize], a, b, result;
        char Op;
        int top = -1;
        for (int i = 0; exp[i]!= '\0'; i++) {
                if (exp[i] >= '0' && exp[i] <= '9') {
                        // 遇到数字则入栈
                        //cout<<exp[i];
                        stack[++top] = exp[i] - '0'; //字符型转换为整数
                }
                else{
                        Op = exp[i];
                        //注意此处除法顺序十分重要，除数要确保在运算符的右侧
                        b = stack[top--];
                        a = stack[top--];
                        result = op(a,Op,b);
                        stack[++top] = result;//运算结果入栈
                }
        }

        return stack[top];
}

int main() {
        /*#1
           char exp[10] = {'1' , '*' , '(' , '1' , '+' , '3' , ')' };
           int len = 7;
           int result = match(exp,len);
           cout<<result;
         */
        /*#2
           char exp[11] = {'1' ,'1' ,'1' , '1' , '*' , '+' , '+' , '1' , '/' , '\0' };
           int result = com(exp);
           cout<<result<<endl;
         */
        conversion(1348,2);
        return 0;
}
