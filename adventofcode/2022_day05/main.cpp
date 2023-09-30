#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

string input();

vector<int> find_delimiter(string str, string delimiter)
{
    vector<int> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
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

void print_vec_vec(vector<vector<char>> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void print_vec_vec2(vector<vector<int>> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void print_vec(vector<int> &v)
{
    for (int r : v)
        cout << r << " ";
    cout << endl;
}

void print_vec2(vector<char> &v)
{
    for (int r : v)
        cout << r << " ";
    cout << endl;
}

int char_to_num(char c)
{
    return c - 48;
}

tuple<int, int> get_number_of_colums()
{
    string str;
    int res = 0;
    int ii = 0;
    for (stringstream file(input()); getline(file, str); ii++)
        if (str[1] == '1')
            return {ii, char_to_num(str[str.length() - 2])};
    return {-1, -1};
}

int main()
{
    int numbers_line_index;
    int stacks_cnt;
    tie(numbers_line_index, stacks_cnt) = get_number_of_colums();
    vector<vector<char>> stacks_vec(stacks_cnt);
    vector<vector<char>> stacks_rev_vec;
    vector<vector<int>> commands_vec;

    int i = 0;
    string str;
    for (stringstream file(input()); getline(file, str); i++)
    {
        if (i < numbers_line_index)
        {
            for (int j = 0; j < stacks_cnt; j++)
            {
                int char_index = 1 + 4 * j;
                if (char_index >= str.length())
                    break;
                char c = str[char_index];
                if (c != 32)
                    stacks_vec[j].push_back(c);
            }
        }
        else if (i > numbers_line_index + 1)
        {
            vector<int> d_vec = find_delimiter(str, " ");
            int moves = stoi(str.substr(d_vec[0] + 1, d_vec[1]));
            int from = char_to_num(str[d_vec[2] + 1]) - 1;
            int to = char_to_num(str[d_vec[4] + 1]) - 1;
            commands_vec.push_back({moves, from, to});
        }
    }

    for (i = 0; i < stacks_vec.size(); i++)
    {
        vector<char> v = stacks_vec[i];
        vector<char> rv;
        for (int j = v.size() - 1; j >= 0; j--)
            rv.push_back(v[j]);
        stacks_rev_vec.push_back(rv);
    }

    print_vec_vec(stacks_rev_vec);
    print_vec_vec2(commands_vec);

    for (auto v : commands_vec)
    {
        int moves = v[0];
        int from = v[1];
        vector<char> *from_vec_ref = &stacks_rev_vec[from];
        int to = v[2];
        vector<char> *to_vec_ref = &stacks_rev_vec[to];
        for (int ii = 0; ii < moves; ii++)
        {
            char ch = from_vec_ref->back();
            from_vec_ref->pop_back();
            to_vec_ref->push_back(ch);
        }
    }

    print_vec_vec(stacks_rev_vec);
    string res;
    for (auto e : stacks_rev_vec)
    {
        res.push_back(e.back());
    }
    cout << "res " << res << endl;
    return 0;
}

string input()
{
    return R"(    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
)";
}