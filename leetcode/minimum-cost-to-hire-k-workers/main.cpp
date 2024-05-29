// https://leetcode.com/problems/minimum-cost-to-hire-k-workers/description/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct WorkerInfo 
{
    int index;
    int quality;
    int wage;
    double wage_to_quality;

    WorkerInfo(int i, int q, int w) : index(i), quality(q), wage(w), wage_to_quality((double)w / (double)q) {}
};

struct less_than_wq
{
    inline bool operator() (const WorkerInfo& w1, const WorkerInfo& w2)
    {
        return (w1.wage_to_quality < w2.wage_to_quality);
    }
};

class Solution
{
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k)
    {
        vector<WorkerInfo> w_vec;
        for (int i=0; i<quality.size(); i++) {
            WorkerInfo w = WorkerInfo(i, quality[i], wage[i]);
            w_vec.push_back(w);
        }
        sort(w_vec.begin(), w_vec.end(), less_than_wq());
        for (int i=0; i<w_vec.size(); i++) {
            WorkerInfo cur = w_vec[i];
            cout << "i: " << cur.index << " " << cur.quality << " " << cur.wage << " " << cur.wage_to_quality << endl;
        }
        return 0;
    }
};

int main()
{
    Solution *s = new Solution();

    // Example 1, res 105
    vector<int> quality{10, 20, 5};
    vector<int> wage{70, 50, 30};
    int k=2;

    // Example 2, res 30.66667
    // vector<int> quality{3, 1, 10, 10, 1};
    // vector<int> wage{4, 8, 2, 2, 7};
    // int k=3;

    int res = s->mincostToHireWorkers(quality, wage, k); // 105
    cout << "res: " << res << endl;
    return 0;
}
