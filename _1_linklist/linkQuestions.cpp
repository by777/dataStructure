/* 题目：两个链表的第一个公共节点
 * 输入两个链表，找出他们的第一个公共节点。
 * 链表节点已经定义
 *
 *          本题摘自《剑指offer》
 */
typedef struct ListNode {
        int m_nKey;
        ListNode *m_pNext;
}ListNode;
void PublicNode(ListNode *pHead1, ListNode *pHead2);

















/*================================Key============================*/
void PublicNode(ListNode *pHead1, ListNode *pHead2){
        /*
         * 常规的蛮力法时间复杂度为O(mn)，不是一个好的算法
         * 通过分析：这两个链表是单向链表，如果两个单向链表有公共的节点
         * 那么这两个链表从某一节点开始，m_pNext指向同一个节点。
         * 但是由于是单向链表，每个节点只有一个m_pNext，
         * **因此从第一个公共节点开始，之后他们所有的节点都是重合的，不可能再出现分叉**
         * 所以两个有公共节点而部分重合的链表，其拓扑形状看起来像一个Y而不是X
         * 经过分析我们发现，如果两个链表有公共节点，那么公共节点应该出现在链表的尾部
         *
         */

}
int main() {

        return 0;
}
