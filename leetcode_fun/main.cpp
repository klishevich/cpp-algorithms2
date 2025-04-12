#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int res = 1;
        vector<int> v = nums;
        sort(v.begin(), v.end());
        int countK = 0;
        for (int i = v.size() -1; i>=0;i--) {
            res *= v[i];
            countK++;
            if (countK == k) break;
        }
        for (int i: v)
            std::cout << i << ' ';  
        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;

    vector<int> nums = {8,3,9,3,8};
    int k = 2;
    int res = s.maximumScore(nums, k);
    cout << endl << res << endl;
    return 0;
}

