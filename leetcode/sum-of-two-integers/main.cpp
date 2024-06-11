// https://leetcode.com/problems/sum-of-two-integers/description/
#include <iostream>
#include <bitset>

using namespace std;

class Solution
{
public:
    int getSum(int a, int b)
    {
        cout << "a " << bitset<8>(a) << " " << a << endl;
        cout << "b " << bitset<8>(b) << " " << b << endl;
        int c = a^b;
        int d = a&b;
        cout << "c " << bitset<8>(c) << " " << c << endl;
        cout << "d " << bitset<8>(d) << " " << d << endl << endl;
        return b==0 ? a : getSum(c, d << 1);
    }
};

int main()
{
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
    // int a = 16;
    // int res = a >> 2;

    // ------------------- From Leet Code ------------------
    // Set Union | 
    // 1 0 1 0 0 - 20
    // 0 0 1 0 1 - 5
    // 1 0 1 0 1 - 4
    // int a = 20;
    // int b = 5;
    // int res = a | b;

    // Set Intersection & 
    // 1 0 1 0 0 - 20
    // 0 0 1 0 1 - 5
    // 1 0 1 0 0 - 4
    // int a = 20;
    // int b = 5;
    // int res = a & b;

    // Set Substraction & ~
    // 1 0 1 0 0 - 20
    // 0 0 1 0 1 - 5
    // 1 0 0 0 0 - 16
    // int a = 20;
    // int b = 5;
    // int res = a & ~b;

    // Set negation all bits ALL_BITS ^A
    // 1 1 1 1 1 - 31
    // 0 0 1 0 1 - 5
    // 1 1 0 1 0 - 26
    // int all_bits = 31;
    // int a = 5;
    // int res = all_bits ^a;

    // Set bit A |= 1 << bit
    // 0 0 1 0 1 - 5
    // 0 0 1 1 1 - 7
    // int a = 5;
    // int res = a |= 1 << 1;

    // Clear bit A &= ~(1 << bit)
    // 0 1 1 0 1 - 13
    // 0 1 0 0 1 - 9
    // int a = 13;
    // int res = a &= ~(1 << 2);

    // Test bit (A & 1 << bit) != 0
    // 0 1 1 0 1 - 13
    // int a = 13;
    // int res = (a & 1 << 2) != 0;

    // Extract last bit A&-A or A&~(A-1) or x^(x&(x-1))
    // 0 1 1 0 1 - 13
    // 0 1 1 0 0 - 12
    // 1 1 0 0 0 - 24
    // int a = 24;
    // int res = a&-a;

    // Remove last bit A&(A-1)
    // 0 1 1 0 1 - 13
    // 0 1 1 0 0 - 12
    // 1 1 0 0 0 - 24
    // int a = 12;
    // int res = a&(a-1);

    // Get all 1-bits ~0
    // unsigned int res = ~0;

    // ----- solution -----

    Solution *s = new Solution();

    int a, b;
    // Example 1, res 3
    a = 3;
    b = 2;

    int res = s->getSum(a, b);

    cout << "res: " << res << endl;
    return 0;
}
