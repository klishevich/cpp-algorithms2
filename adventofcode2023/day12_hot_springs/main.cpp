#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
string input();

void parse_string(const string &str, string &springs, vector<int> &segments) {
    stringstream str_stream(str);
    int idx = 0;
    string s;
    while (getline(str_stream, s, ' ')) {
        if (idx == 0) {
            springs = s+"?"+s+"?"+s+"?"+s+"?"+s;
        }
        if (idx == 1) {
            stringstream s_stream(s);
            string s2;
            vector<int> temp_seg;
            while (getline(s_stream, s2, ',')) temp_seg.push_back(stoi(s2));
            for(int i=0;i<5;i++) segments.insert( segments.end(), temp_seg.begin(), temp_seg.end() );
        }
        idx++;
    }
}

bool no_dot(const string &s, int start, int length) {
    if (start + length > s.length()) return false;
    for (int i=start;i<start+length;i++) {
        if (s[i]=='.') return false;
    }
    return true;
}

bool no_hash(const string &s, int start, int length) {
    if (start + length > s.length()) return false;
    for (int i=start;i<start+length;i++) {
        if (s[i]=='#') return false;
    }
    return true;
}

long calc(const string &spr, int spr_off, const vector<int> &segms, int offset, map<pair<int,int>,long> &cache) {
    pair<int,int> pp = {spr_off, offset};
    if (cache.count(pp)) return cache[pp];
    int spr_len = spr.length() - spr_off;
    if (spr_len == 0) return 0;
    int all_segms_len = 0;
    for (int i=offset;i<segms.size();i++) all_segms_len+=segms[i];
    int all_segms_len2 = all_segms_len + segms.size() - offset;
    if (spr_len < all_segms_len2 - 1) return 0;
    if (segms.size() - offset == 1) {
        long res = 0;
        for (int i=0;i<spr_len - segms[offset] + 1;i++) {
            if (no_hash(spr,spr_off,i) && no_dot(spr, spr_off+i, segms[offset]) && no_hash(spr,spr_off+i+segms[offset],spr_len-(i+segms[offset]))) res++;
        }
        return res;
    }
    long res = 0;
    int cur_segm_len = segms[offset];
    for (int i=0;i<spr_len;i++) {
        if (no_hash(spr,spr_off,i) && no_dot(spr,spr_off+i,cur_segm_len) && no_hash(spr,spr_off+i+cur_segm_len,1)) {
            res += calc(spr, spr_off + i+cur_segm_len+1, segms, offset + 1, cache);
        }
    }
    cache.insert({pp, res});
    return res;
}

int main()
{
    vector<string> data;
    string str;
    long res = 0;

    for (stringstream file(input()); getline(file, str);) {
        cout << str << endl;
        string springs;
        vector<int> segments;
        parse_string(str, springs, segments);
        // cout << "springs " << springs << endl;
        // for (int seg : segments) cout << seg << " ";
        // cout << endl;
        map<pair<int,int>,long> cache;
        long t_res = calc(springs, 0, segments, 0, cache);
        cout << "t_res " << t_res << endl;
        res += t_res;
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