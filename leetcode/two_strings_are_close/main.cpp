#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    map<char,int> getMap(const string &str) {
        map<char,int> m;
        for(const char& c : str) {
            auto pos = m.find(c);
            if (pos == m.end()) {
                m[c] = 1;
            } else {
                m[c] = m.at(c) + 1;
            }
        }
        return m;
    }

    void fillVectors(const map<char,int> &m, vector<char> &char_vec, vector<int> &int_vec) {
        for (const auto &[c, i]: m) {
            char_vec.push_back(c);
            int_vec.push_back(i);
        }
        sort(char_vec.begin(), char_vec.end());
        sort(int_vec.begin(), int_vec.end()); 
    }

    bool closeStrings(string word1, string word2) {
        map<char,int> m1 = this->getMap(word1);
        vector<char> char_vec1;
        vector<int> num_vec1;
        this->fillVectors(m1, char_vec1, num_vec1);
        map<char,int> m2 = this->getMap(word2);
        vector<char> char_vec2;
        vector<int> num_vec2;
        this->fillVectors(m2, char_vec2, num_vec2);
        if (char_vec1.size() != char_vec2.size()) return false;
        for (int i=0; i<char_vec1.size(); ++i) {
            if (char_vec1[i] != char_vec2[i]) return false;
        }
        if (num_vec1.size() != num_vec2.size()) return false;
        for (int i=0; i<num_vec1.size(); ++i) {
            if (num_vec1[i] != num_vec2[i]) return false;
        }
        return true;
    }
};

int main()
{
    Solution* s = new Solution();
    bool res = s->closeStrings("abc", "bca");
    cout << "res1 " << res << endl;
    res = s->closeStrings("a", "aa");
    cout << "res2 " << res << endl;
    res = s->closeStrings("cabbba", "abbccc");
    cout << "res3 " << res << endl;
    return 0;
}
