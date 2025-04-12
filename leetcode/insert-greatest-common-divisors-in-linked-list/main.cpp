/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* prevEl = nullptr;
        ListNode* curEl = head;

        do {
            if (prevEl != nullptr) {
                int min = std::min(prevEl->val, curEl->val);
                int max = std::max(prevEl->val, curEl->val);
                int newVal = this->gcd(max, min);
                ListNode* newNode = new ListNode(newVal, curEl);
                prevEl->next = newNode;
            }
            prevEl = curEl;
            curEl = curEl->next;
        } while (curEl != nullptr);
        return head;
    }

    int gcd(int a, int b) {
        return b==0 ? a : this->gcd(b, a%b);
    }
};