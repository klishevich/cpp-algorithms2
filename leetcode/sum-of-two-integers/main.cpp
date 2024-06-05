// https://leetcode.com/problems/sum-of-two-integers/description/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

class Solution
{
public:
    int getSum(int a, int b)
    {
        return 0;
    }
};

int main()
{
    // Solution *s = new Solution();

    // int a, b;
    // // Example 1, res 3
    // a = 1;
    // b = 2;

    // int res = s->getSum(a, b);

    // AND &, res 4
    // 1 1 1
    // 1 0 0
    // 1 0 0 &
    // int a = 4;
    // int b = 7;
    // int res = a & b;

    // OR |, res 7
    // 1 1 1
    // 1 0 0
    // 1 1 1 |
    // int a = 4;
    // int b = 7;
    // int res = a | b;

    // XOR ^, res 3
    // 1 1 1
    // 1 0 0
    // 0 1 1 ^
    // int a = 4;
    // int b = 7;
    // int res = a ^ b;

    // NOT ~, res -5 Negate ALL BITS
    // 1 0 0
    // 0 1 1 ~
    // int a = 4;
    // int res = ~a;

    // NOT ~, res 3 Negate sagnificant bits
    // 1 0 0
    // 0 1 1 ~
    // int a = 4;
    // int res = (~a)&0b111;

    // Left Shift <<, res 20
    // 1 0 1
    // 1 0 1 0 0 <<
    // int a = 5;
    // int res = a << 2;

    // Right Shift >>, res 4 
    // 1 0 0 0 0
    // 0 0 1 0 0 >> 2
    int a = 16;
    int res = a >> 2;

    cout << "res: " << res << endl;
    return 0;
}
