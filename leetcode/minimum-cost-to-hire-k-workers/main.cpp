// https://leetcode.com/problems/minimum-cost-to-hire-k-workers/description/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct WorkerInfo 
{
    int index;
    int quality;
    int wage;
    double wage_to_quality;

    WorkerInfo(int i, int q, int w) : index(i), quality(q), wage(w), wage_to_quality((double)w / (double)q) {}
};

struct CompareAscWQ
{
    inline bool operator() (const WorkerInfo& w1, const WorkerInfo& w2)
    {
        return (w1.wage_to_quality < w2.wage_to_quality);
    }
};

struct CompareAscQuality
{
    inline bool operator() (const WorkerInfo& w1, const WorkerInfo& w2)
    {
        return (w1.quality < w2.quality);
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
        sort(w_vec.begin(), w_vec.end(), CompareAscWQ());
        for (int i=0; i<w_vec.size(); i++) {
            WorkerInfo cur = w_vec[i];
            cout << "s: " << cur.index << " " << cur.quality << " " << cur.wage << " " << cur.wage_to_quality << endl;
        }

        int quality_sum = 0;
        double max_wq = 0.0;
        double total_wage = 0.0;
        priority_queue<WorkerInfo, vector<WorkerInfo>, CompareAscQuality> max_quality_queue;

        for (int i=0; i<w_vec.size(); i++) {
            WorkerInfo w = w_vec[i];
            if (i < k) {
                quality_sum += w.quality;
                max_wq = w.wage_to_quality;
                total_wage = (double)quality_sum * max_wq;
                max_quality_queue.push(w);
            } else {
                cout << "quality_sum: " << quality_sum << endl;
                cout << "max_wq: " << max_wq << endl;
                cout << "total_wage: " << total_wage << endl;
                cout << "w: " << w.index << " " << w.quality << " " << w.wage << " " << w.wage_to_quality << endl;
                WorkerInfo top_w = max_quality_queue.top();
                cout << "top_w: " << top_w.index << " " << top_w.quality << " " << top_w.wage << " " << top_w.wage_to_quality << endl;
                double new_max_wq = w.wage_to_quality;
                cout << "new_max_wq: " << new_max_wq << endl;
                int new_quality_sum = quality_sum - top_w.quality + w.quality;
                cout << "new_quality_sum: " << new_quality_sum << endl;
                double new_total_wage = (double)new_quality_sum * new_max_wq;
                cout << "new_total_wage: " << new_total_wage << endl;
                if (new_total_wage < total_wage) {
                    quality_sum = new_quality_sum;
                    max_wq = new_max_wq;
                    total_wage = new_total_wage;
                    max_quality_queue.pop();
                    max_quality_queue.push(w);
                }
            }
            WorkerInfo cur = max_quality_queue.top();
            cout << "i: " << cur.index << " " << cur.quality << " " << cur.wage << " " << cur.wage_to_quality << endl;
        }

        return total_wage;
    }
};

int main()
{
    Solution *s = new Solution();

    // Example 1, res 105
    // vector<int> quality{10, 20, 5};
    // vector<int> wage{70, 50, 30};
    // int k=2;

    // Example 2, res 30.66667
    // vector<int> quality{3, 1, 10, 10, 1};
    // vector<int> wage{4, 8, 2, 2, 7};
    // int k=3;

    // Example 3, res 25.50000
    // vector<int> quality{2, 1, 5};
    // vector<int> wage{17, 6, 4};
    // int k=2;

    // Example 4, expected 1528.00000 , but I get 1700.53125 
    vector<int> quality{32,43,66,9,94,57,25,44,99,19};
    vector<int> wage{187,366,117,363,121,494,348,382,385,262};
    int k=4;

    int res = s->mincostToHireWorkers(quality, wage, k); // 105
    cout << "res: " << res << endl;
    return 0;
}
