#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

string input();

vector<int> find_delimiter(string& str, string delimiter)
{
    vector<int> v;
    if (!str.empty()) {
        int start = 0;
        do {
            int idx = str.find(delimiter, start);
            if (idx == string::npos)
                break;
            int length = idx - start;
            v.push_back(idx);
            start += (length + delimiter.size());
        } while (true);
    }
    return v;
}

int get_prev_number(string& ss, vector<int>& spaces, int i) {
    int space_index = spaces[i];
    int prev_space_index = spaces[i-1];
    string r_ss = ss.substr(prev_space_index+1, space_index-prev_space_index-1);
    return stoi(r_ss);
}

vector<vector<int>> parse_game(string& s) {
    vector<vector<int>> res;

    int start = s.find(":", 0);
    vector<int> colons = find_delimiter(s, ";");
    vector<string> sss;
    for (int end : colons) {
        string ss = s.substr(start+1,end-start-1);
        sss.push_back(ss);
        start = end;
    }
    string last_ss = s.substr(start+1);
    sss.push_back(last_ss);

    for (string& ss : sss) {
        int r = 0;
        int g = 0;
        int b = 0;
        vector<int> spaces = find_delimiter(ss, " ");
        for (int i=0;i<spaces.size();i++) {
            int space_index = spaces[i];
            char next_char = ss[space_index+1];
            if (r == 0 && next_char == 'r') {
                r = get_prev_number(ss, spaces, i);
            }
            if (g == 0 && next_char == 'g') {
                g = get_prev_number(ss, spaces, i);
            }
            if (b == 0 && next_char == 'b') {
                b = get_prev_number(ss, spaces, i);
            }
        }
        vector<int> v1 {r, g, b};
        res.push_back(v1);
    }

    return res;
}

int main()
{
    vector<vector<vector<int>>> vec;
    string str;
    for (stringstream file(input()); getline(file, str);)
    {
        vector<vector<int>> v1 = parse_game(str);
        vec.push_back(v1);
    }
    int res = 0;
    for (int i=0; i<vec.size();++i) {
        int red_max = 0;
        int green_max = 0;
        int blue_max = 0;
        vector<vector<int>> v1 = vec[i];
        for (vector<int> v2 : v1) {
            if (v2[0]>red_max) red_max = v2[0];
            if (v2[1]>green_max) green_max = v2[1];
            if (v2[2]>blue_max) blue_max = v2[2];
        }
        int power_of_set = red_max * green_max * blue_max;
        res += power_of_set;
    }
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
)";
}