#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <deque>

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

template <typename T>
void print_vec(vector<T> &vec)
{
    for (auto v : vec) {
        for (auto c : v)
            cout << c << " ";
        cout << endl;
    }
    cout << endl;
}

int char_to_num(char c)
{
    return c - 48;
}

tuple<int, int> get_number_of_colums()
{
    string str;
    int ii = 0;
    for (stringstream file(input()); getline(file, str); ii++)
        if (str[1] == '1')
            return {ii, char_to_num(str[str.length() - 2])};
    return {-1, -1};
}

int main()
{
    bool is_part_1 = true;
    int numbers_line_index;
    int stacks_cnt;
    tie(numbers_line_index, stacks_cnt) = get_number_of_colums();
    vector<deque<char>> stacks_vec(stacks_cnt);

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
                if (c != ' ')
                    stacks_vec[j].push_front(c);
            }
        }
        else if (i > numbers_line_index + 1)
        {
            vector<int> d_vec = find_delimiter(str, " ");
            int moves = stoi(str.substr(d_vec[0] + 1, d_vec[1]));
            int from = char_to_num(str[d_vec[2] + 1]) - 1;
            int to = char_to_num(str[d_vec[4] + 1]) - 1;
            deque<char> *from_deque_ref = &stacks_vec[from];
            deque<char> *to_deque_ref = &stacks_vec[to];
            deque<char> tmp_deque;
            for (int ii = 0; ii < moves; ii++)
            {
                char ch = from_deque_ref->back();
                from_deque_ref->pop_back();
                if (is_part_1) {
                    tmp_deque.push_back(ch);
                } else {
                    tmp_deque.push_front(ch);
                }
            }
            for (char c : tmp_deque) {
                to_deque_ref->push_back(c);
            }
        }
    }

    print_vec<deque<char>>(stacks_vec);

    for (auto e : stacks_vec)
        cout << e.back();

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