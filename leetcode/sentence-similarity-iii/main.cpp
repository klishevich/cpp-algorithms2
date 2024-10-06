// https://leetcode.com/problems/sentence-similarity-iii/description/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string> v_s1;
        vector<string> v_s2;
        string s;
        istringstream iss1(sentence1);
        while (getline(iss1, s, ' ')) v_s1.push_back(s);
        istringstream iss2(sentence2);
        while (getline(iss2, s, ' ')) v_s2.push_back(s);
        vector<string>* pv_SMax = v_s1.size() > v_s2.size() ? &v_s1 : &v_s2;
        vector<string>* pv_SMin = v_s1.size() > v_s2.size() ? &v_s2 : &v_s1;

        int i_LenSMin = pv_SMin->size();
        int i_Left;
        for (i_Left=0; i_Left < i_LenSMin; i_Left++) {
            if ((*pv_SMin)[i_Left] != (*pv_SMax)[i_Left]) {
                break;
            }
        }
        int i_Right;
        int i_LenSMax = pv_SMax->size();
        for (i_Right=0; i_Right < i_LenSMin; i_Right++) {
            if ((*pv_SMin)[i_LenSMin-1-i_Right] != (*pv_SMax)[i_LenSMax-1-i_Right]) {
                break;
            }
        }

        return i_Left + i_Right >= i_LenSMin;
    }
};

int main()
{
    Solution *s = new Solution();

    string a, b;
    // Example 1, res true
    // a = "My name is Haley"; b = "My Haley";

    // Example 2, res false
    // a = "of"; b = "A lot of words";

    // Example 3, res true
    a = "Eating right now"; b = "Eating";

    int res = s->areSentencesSimilar(a, b);

    cout << "res: " << res << endl;
    return 0;
}
