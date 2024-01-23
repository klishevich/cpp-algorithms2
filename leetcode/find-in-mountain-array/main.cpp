#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findInMountainArray(int target, vector<int> &mountainArr) {
        int topIndex = this->findTop(0, mountainArr.size()-1, mountainArr);
        cout << "topIndex " << topIndex << endl;
        int firstRes = this->findTarget(0, topIndex, target, true, mountainArr);
        if (firstRes != -1)
            return firstRes;
        else
            return this->findTarget(topIndex, mountainArr.size()-1, target, false, mountainArr);
    }

    int findTop(int leftIndex, int rightIndex, vector<int> &m) {
        if (rightIndex - leftIndex < 2) {
            if (m[leftIndex] > m[rightIndex])
                return leftIndex;
            else return rightIndex;
        }
        int centerIndex = leftIndex + (rightIndex - leftIndex) / 2;
        if (m[centerIndex-1]<m[centerIndex] && m[centerIndex]>m[centerIndex+1])
            return centerIndex;
        bool isAsc = (m[centerIndex-1]<m[centerIndex]);
        if (isAsc)
            return this->findTop(centerIndex, rightIndex, m);
        else
            return this->findTop(leftIndex, centerIndex, m);
    }

    int findTarget(int leftIndex, int rightIndex, int target, bool isAscArr, vector<int> &m) {
        cout << "leftIndex " << leftIndex << " rightIndex " << rightIndex << endl;
        if (rightIndex - leftIndex < 2) {
            if (m[leftIndex] == target)
                return leftIndex;
            else if (m[rightIndex] == target)
                return rightIndex;
            else
                return -1;
        }
        int centerIndex = leftIndex + (rightIndex - leftIndex) / 2;
        if (m[centerIndex] == target)
            return centerIndex;
        if ((m[centerIndex] < target && isAscArr) || (m[centerIndex] > target && !isAscArr))
            return this->findTarget(centerIndex, rightIndex, target, isAscArr, m);
        else
            return this->findTarget(leftIndex, centerIndex, target, isAscArr, m);
    }
};

int main()
{
    Solution *s = new Solution();

    // vector<int> vec{1,2,3,4,5,3,1};
    // int target = 3; // output 2

    // vector<int> vec{0,1,2,4,2,1};
    // int target = 3; // output -1

    vector<int> vec{1,2,3,4,5,3,1};
    int target = 2; // output 1

    int res = s->findInMountainArray(target, vec);
    cout << "res " << res << endl;
    return 0;
}
