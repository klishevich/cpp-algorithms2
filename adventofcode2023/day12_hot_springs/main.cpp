#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
string input();

void parse_string(const string &str, string &springs, vector<int> &segments) {
    stringstream str_stream(str);
    int idx = 0;
    string s;
    while (getline(str_stream, s, ' ')) {
        if (idx == 0) springs = s;
        if (idx == 1) {
            stringstream s_stream(s);
            string s2;
            while (getline(s_stream, s2, ',')) segments.push_back(stoi(s2));
        }
        idx++;
    }
}

// vector<string> get_all_combinations(const string &springs, const vector<int> &segments) {
//     int len1 = springs.length();
//     int len2 = 0;
//     for (int seg : segments) len2 =+ seg;
//     int rest_len = len1 - len2;
//     int spaces = segments.size() - 1;
    

// }

bool has_no_dots(const string &s, int start, int length) {
    // cout << "has_no_dots s " << s << " start " << start << " length " << length << endl;
    if (start + length > s.length()) return false;
    for (int i=start;i<start+length;i++) {
        if (s[i]=='.') return false;
    }
    return true;
}

bool has_no_hash(const string &s, int start, int length) {
    // cout << "has_no_hash s " << s << " start " << start << " length " << length << endl;
    if (start + length > s.length()) return false;
    for (int i=start;i<start+length;i++) {
        if (s[i]=='#') return false;
    }
    return true;
}

int calc(const string &spr, const vector<int> &segms) {
    // cout << "spr " << spr << " spr.length "<< spr.length() << endl;
    int spr_len = spr.length();
    if (spr_len == 0) return 0;
    // for (int seg : segms) cout << seg << " ";
    // cout << endl;
    int all_segms_len = 0;
    for (int seg : segms) all_segms_len+=seg;
    int all_segms_len2 = all_segms_len + segms.size();
    if (spr_len < all_segms_len2 - 1) return 0;
    if (segms.size() == 1) {
        int res = 0;
        for (int i=0;i<spr_len - segms[0] + 1;i++) if (has_no_dots(spr, i, segms[0])) res++;
        return res;
    }
    int res = 0;
    int cur_segm_len = segms[0];
    vector<int> sub_segms(segms.begin()+1, segms.end());
    for (int i=0;i<spr_len;i++) {
        // cout << "i "<< i << " spr " << spr << " cur_segm_len " << cur_segm_len << endl;
        if (has_no_hash(spr,0,i) && has_no_dots(spr,i,cur_segm_len) && has_no_hash(spr,i+cur_segm_len,1)) {
            string sub_spr = spr.substr(i+cur_segm_len+1);
            res += calc(sub_spr, sub_segms);
        }
    }
    return res;
}

int main()
{
    vector<string> data;
    string str;
    int res = 0;
    for (stringstream file(input()); getline(file, str);) {
        cout << str << endl;
        string springs;
        vector<int> segments;
        parse_string(str, springs, segments);
        // cout << "springs " << springs << endl;
        // cout << endl;
        res += calc(springs, segments);
    }
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(???.### 1,1,3
.??..??...?##. 1,1,3
?#?#?#?#?#?#?#? 1,3,1,6
????.#...#... 4,1,1
????.######..#####. 1,6,5
?###???????? 3,2,1
)";
}