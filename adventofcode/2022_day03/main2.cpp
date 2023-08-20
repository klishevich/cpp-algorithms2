#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

template <typename Type>
auto setIntersection(set<Type> set0, set<Type> set1)
{
    set<Type> intersection;
    for (auto value : set0)
        if (set1.find(value) != set1.end())
            intersection.insert(value);
    return intersection;
}

string input();

int main()
{
    auto get_score = [](char ch)
    {
        if (ch <= 'Z')
            return ch - 'A' + 1 + 26;
        else
            return ch - 'a' + 1;
    };
    set<char> set2;
    set<char> set1;
    string str;
    int res = 0;
    int ii = 0;
    for (stringstream file(input()); getline(file, str); ii++)
    {
        set<char> set0(str.begin(), str.end());
        if (ii % 3 == 2)
        {
            set intersection1 = setIntersection(set0, set1);
            set intersection2 = setIntersection(intersection1, set2);
            char ch2 = *intersection2.begin();
            cout << "ch2 " << ch2 << " " << int(ch2) << " score " << get_score(ch2) << endl;
            res += get_score(ch2);
        }
        set2 = set1;
        set1 = set0;
    }
    cout << "result " << res << endl;
    return 0;
}

string input()
{
    return R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw
)";
}