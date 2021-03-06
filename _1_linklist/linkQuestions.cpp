#include <iostream>
using namespace std;

/*  ================================Q1=============================
 *  void PublicNode(ListNode *pHead1, ListNode *pHead2);
 *  ---------------------------------------------------------------
 * 题目：两个链表的第一个公共节点
 * 输入两个链表，找出他们的第一个公共节点。
 * 链表节点已经定义
 *          ————本题摘自《剑指offer》
 * =================================================================*/
typedef struct ListNode {
        int m_nKey;
        ListNode *m_pNext;
}ListNode;

void PublicNode(ListNode *pHead1, ListNode *pHead2);
int IsPalindrome(int x);

/*  ================================Q2=============================
 *  void IsPalindrome(int x);
 *  ---------------------------------------------------------------
 *  题目：回文数
 *  题目描述：判断一个整数是否是回文数。回文数指正序（从左到右）和逆序读起来都是一样的
 *          ————本题摘自《LeetCode领扣》
 *  =================================================================*/





/*================================Answers============================*/
void PublicNode(ListNode *pHead1, ListNode *pHead2){
        /*
         * 常规的蛮力法时间复杂度为O(mn)，不是一个好的算法
         * 通过分析：这两个链表是单向链表，如果两个单向链表有公共的节点
         * 那么这两个链表从某一节点开始，m_pNext指向同一个节点。
         * 但是由于是单向链表，每个节点只有一个m_pNext，

         * **因此从第一个公共节点开始，之后他们所有的节点都是重合的，不可能再出现分叉**

         * 所以两个有公共节点而部分重合的链表，其拓扑形状看起来像一个Y而不是X
         * 经过分析我们发现，如果两个链表有公共节点，那么公共节点应该出现在链表的尾部。
         * 如果我们从两个链表的尾部向前比较，那么最后一个相同的节点就是我们要找的节点。
         * 为了从后往前找，我们使用两个辅助栈，使用空间换取时间，时间复杂度和空间复杂度
         * 都是O(m+n)。
         *
         */

}

int IsPalindrome(int x){
        /*
         * 思路①：
         * 将数字转换成字符串，并且检查字符串是否为回文。但是需要额外的非常量空间

         * 思路②：
         * 将数字本身反转，反转后的与原始数字比较是否相等，但是可能遇到整数溢出

         * 思路②Plus：
         * 为什么不考虑只反转int数字的一半？毕竟，如果数字是回文数，其后半部分
         * 反转后应该与原始数字的前半部分相同。

         * 算法：
         * 首先我们应该先处理一些临界情况。所有负数不可能是回文。
         * 现在先来考虑如何反转后半部分的数字。

         * 对于数字1221，如果执行1221%10我们将得到最后一位数字1，
         * 要得到倒数第二位数字，我们可以先通过除以10把最后一位数字从1221移除，1221/10=122，
         * 再求出上一步结果除以10的余数：122%10=2，就可以得到倒数第二位的数字。

         * 如果我们把最后以为数字乘以10，再加上倒数第二位数字，1*10+2=12，就得到了我们
         * 想要的反转后的数字。如果继续这个过程，我们将得到更多位数的反转数字。

         * 如果我们想要知道反转是否已经到达了一半，我们将原始数字除以10，然后再将反转后
         * 的数字乘以10，所以，当原始数字小于反转后的数字时，就意味着我们已经处理了一半位数的数字。
         *
         */
        if(x < 0 || (x % 10 == 0 && x != 0)) {
                //当x<0时，x不是回文数。同样的，如果数字最后一位是0，第一位也必须是0，只有0满足这一属性
                return 0;
        }
        int revertedNumber = 0;
        while (x > revertedNumber) {
                /*
                 * 当数字长度为奇数时，我们可以通过revertedNumber/10来去除处于中位的数字。
                 * 例如，当输入数字为12321时，在while循环的末尾我们可以得到x=12,revertedNumber=123
                 *
                 */
                revertedNumber = revertedNumber * 10 + x % 10;
                x /= 10;
        }
        return x == revertedNumber || x == revertedNumber / 10;
        /*
         * 算法复杂度：O(log_10(n))，对于每次迭代，我们都会将其除以10
         * 空间复杂度：O(1)
         */
}





int main() {
        int p = IsPalindrome(12321);
        cout<<p<<endl;
        return 0;
}
