#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

string input();

int main()
{
    std::map<std::string, int> shape_score;
    shape_score["A"] = 1;
    shape_score["B"] = 2;
    shape_score["C"] = 3;
    shape_score["X"] = 2;
    shape_score["Y"] = 0;
    shape_score["Z"] = 1;

    std::map<int, int> outcome_score;
    outcome_score[2] = 0;
    outcome_score[0] = 3;
    outcome_score[1] = 6;

    string str;
    int result = 0;
    for (stringstream file(input()); getline(file, str);)
    {
        istringstream iss(str);
        string s;
        vector<string> vect;
        while (getline(iss, s, ' '))
        {
            vect.push_back(s);
        }
        int opponent_move = shape_score[vect.at(0)];
        int game_outcome = shape_score[vect.at(1)];
        // cout << "opponent " << opponent_move << " game_outcome " << game_outcome << endl;
        int my_move = (game_outcome + opponent_move) % 3;
        my_move = my_move == 0 ? 3 : my_move; 
        // cout << "my_move " << my_move << endl;
        int game_score = my_move + outcome_score[game_outcome];
        // cout << "game_score " << game_score << endl;
        result += game_score;
    }
    cout << "result " << result << endl;
    return 0;
}

string input()
{
    return R"(B Z
C Z
C Z
A Y
B Z
C Y
C Z
C Y
C X
A Z
B Z
C Z
A Y
C Z
B X
C Y
C Z
C X
C X
C Y
C Y
C X
A Y
C Y
C Y
C X
C Z
C X
A X
C Z
C Y
C Z
C Z
C Z
A Z
C Z
B Z
A Y
A X
A Y
C Z
A Y
C Z
A Z
C Y
C Y
C Y
A X
C X
C X
C Y
A X
A Y
C X
A X
C Z
A Y
C Z
C Y
A Y
C Z
A X
A Y
A X
C X
C Z
A X
B Z
C Z
C Y
C X
C X
C Z
C X
C Z
A X
C Y
A Y
C Y
C Z
C X
B X
B Z
C Z
C X
A X
B Z
A Y
A Y
B Z
A Y
C Y
B Z
B X
C X
C X
C X
A X
A Z
A Y
A Y
C Y
C Z
C Z
C Z
A Y
C X
A Y
A X
C X
C X
A X
A Y
A X
A X
A Y
C Y
A Y
A Y
A X
C X
B Z
A X
C Y
C X
C Z
C Z
C Z
C Z
C Y
C X
C X
A X
A Y
A X
C Z
C X
C Y
C Y
C Z
C Z
B Z
C Z
C Y
C X
C Y
A X
A Y
C X
B Z
B Y
C Z
C Y
C X
A Y
C Y
B Z
A Z
C X
C Z
C Y
C X
C Z
A X
A Y
C Y
C Y
A Y
A X
A X
C X
C X
C Z
A Y
A Y
C Y
C Z
A X
A Y
C X
C X
C Y
C X
C Z
C X
C Z
C Z
C Z
C Z
A Y
B Z
C Y
C Z
A Z
C X
C X
A X
A Z
C Z
C X
C Z
A X
B Z
B Z
A X
C X
C X
B Z
B Z
B Z
C Z
C X
A Y
C Z
A X
C Y
C Z
C Z
C X
C X
C Z
C Y
C Y
C X
C X
A X
C Y
A X
C Y
C X
B X
B Z
C X
C X
B X
C Z
C Y
A X
C Z
C Z
C Z
C Y
C X
A Y
A Z
C Z
B Z
C Z
C X
A Y
C X
C X
A X
C X
C Z
A X
C Z
C Y
C Y
C Y
C Z
A X
C Y
C X
C Z
A X
C Z
C X
C X
C X
A Y
C Z
A Y
C Z
C Y
C Z
A Y
C X
C X
C X
C Y
C Z
C X
C Y
C X
A X
C X
C Y
C X
C Z
C X
B Z
C X
B Z
B X
C X
C X
C X
B X
A Y
A Y
A X
B Z
C X
A Z
C Y
C X
C X
C Y
A Y
A Z
C X
A Y
C Z
C X
C X
C Y
C Y
A Z
A X
C Z
C X
C Z
B Y
A Y
C Z
A Y
C Z
A X
C Y
C Y
C X
A Y
C X
C X
B X
C Z
C X
C Y
C Z
C Z
C Y
C Y
C Y
C X
B Z
C X
C X
C Y
C Y
C Z
B Z
C X
C Y
B Z
C Z
A Y
C X
C X
A Y
C Y
C Z
C X
A Y
A Y
C Z
C Z
C Z
A X
C X
C Z
C Z
C Z
A Y
A X
C X
C Z
C X
C X
C Y
A Y
C X
C Y
C Z
C Y
A X
C X
C X
C Z
A X
B X
C Y
A X
C Y
C Y
C X
C Z
B X
C X
C Z
A Y
C Z
C X
A X
C Y
A X
C Z
A X
C X
C Y
C X
C Z
C X
C X
C Y
A X
C Y
A Y
C Z
C X
C X
A X
A Z
C X
C X
C Y
B Z
A X
A X
C X
B Z
C Z
A Y
C Y
C Z
C X
A Z
C Y
A X
C Y
C Z
C Z
C X
C Y
C X
C Y
C Y
C X
A Y
B X
C X
A X
A Y
C Y
C Z
C Y
C X
A Y
C Z
C X
C X
A Z
C Y
C Z
A X
C X
C Z
A Y
A X
B X
C Z
B Z
C X
A Z
C Z
A X
A Y
C X
A X
B Z
C X
C Y
C Z
C Y
C Y
C Z
C X
B X
C Y
B Y
C Z
A Y
A Y
C Y
C Z
A X
C Z
C Y
B Z
C X
A X
C X
C X
C Y
C Y
C Z
A Y
C Z
A X
A Y
C X
C Y
C Z
C X
A X
B Z
C Z
A X
C X
C X
C X
B Z
C Z
C Y
B Z
A X
C Z
C Y
A X
C X
B Z
C Y
C X
C Z
C Z
C Z
C X
C Y
B X
A X
B Z
C X
C Y
C Z
C X
C Z
C Z
C Z
C Y
A X
C X
C Z
A X
C X
C Z
B X
C Z
B Z
A Y
A X
C Z
C Z
C Y
C Z
C Y
C Z
A Y
B Z
A Y
C X
A X
A X
A X
B Z
C Z
B Y
C Y
A Y
A Y
C Z
A Y
C Z
C Z
A Y
C Z
C Z
C Z
A Y
C Z
C Z
C Z
C Z
A Y
C Y
A Y
C Y
C X
C X
C Z
C X
C Z
C Y
A X
C Z
B X
C Z
A X
C Z
C Z
C Y
C Z
C Y
C X
C Y
B X
C Z
C X
C Y
A Y
C X
C Z
C X
C Z
C X
A Z
C Z
C X
C X
B Z
C Z
C X
A X
C Y
A Y
C X
C Z
C Z
A Y
A X
B Y
C Y
C Y
C Y
C X
A X
C Z
C Y
C Z
C X
C Z
C Z
C Y
B X
C X
C Z
C X
C X
C Y
A X
B Z
A X
C X
C Z
B Z
A Y
C Y
B Z
C X
A Z
A X
C Z
C Z
C X
A Y
B Y
C X
C Z
B Y
A Y
A Y
C X
A X
C Y
C X
C X
C Z
A X
A X
A X
B Z
C Y
C Z
C X
A X
B Z
C Z
C Z
C X
C X
C X
C X
C Z
C Y
C Z
C Z
C Z
A Y
C Z
C X
C Y
C X
B Y
A Y
C Z
C X
C Z
A X
A X
C Y
C Y
C X
C Z
C Z
C Z
C X
C Z
C X
C Y
C X
C X
C Y
C Y
B Z
C Z
C Z
B Z
C Y
C Z
C Y
B Z
C X
C Z
C Y
C Z
A Y
C Z
B Z
C Z
C X
C X
A Z
C Z
C X
A Y
A Z
A X
C Y
C X
C Z
C X
C X
C Y
C X
C Z
C X
C Y
C Y
C Z
C Y
C Y
C Y
A Z
A Y
C Z
C Y
C Z
C X
A X
C Z
C Z
A Y
C Z
C X
C X
C X
C Z
C X
C Z
C Y
A Z
C Z
C Y
C Z
C X
C Y
C Y
C X
C X
C Z
A Y
C Y
B Z
A Y
C Y
C X
C Z
C X
C Y
C Z
A Y
A X
C Z
B Y
C Y
A X
C Y
C Z
B Z
C Y
C Z
C Z
B Z
C X
A Y
C Z
C X
B Y
B Z
C Z
B Z
C X
A X
A X
B Z
C Z
C Z
C Z
C Y
A Y
C Z
B X
C Y
A Z
C Y
C Y
A Y
C X
C Y
B Z
C X
C X
C X
B Z
C X
B Z
A X
C Y
C Y
A X
C X
A Y
C X
A X
C Z
A X
C X
C X
A Y
C Z
C Z
C X
C X
B Z
A Y
C Y
C X
A Y
C Z
A X
C X
B Z
C X
C X
B X
B X
B Z
C Z
C X
A Y
B Z
B Y
C X
C Z
A Y
C Z
C X
C X
B Z
C X
A Y
A X
A Z
C Z
C Y
B Z
C X
A X
C X
A X
C X
C X
C Z
A X
B Z
C Z
C X
C X
A X
C Z
C X
C X
C Z
C Y
C X
A X
C X
C X
C X
A X
C Z
C Z
C Y
B Z
C X
A Y
C Z
C X
C Y
B X
A X
C X
B Z
C Y
B X
A Y
B X
C Z
C Y
C X
C Z
A Y
A Y
C X
A X
C X
C X
A Y
A X
B X
C Y
A Y
C X
C Z
A Y
C Z
B Z
C Z
A X
C Y
C Y
C Y
A Y
A Z
A Y
C X
C X
A Y
C Y
A X
C Y
A Y
C X
C Y
B Z
C Z
C Z
B X
C Y
B X
A Y
A Y
A X
A Y
C Z
C Z
C Y
B Z
A Z
C X
C Z
A X
C X
C X
C Z
C Y
C X
A Y
C Z
B Z
A Y
A X
C Y
B X
C Z
A Y
C X
C Y
C X
A X
C Z
C Z
C X
C Z
A X
C X
C X
A Z
B Z
A X
C Y
C X
A X
C X
C Z
C Y
A Y
C X
A Y
A X
C Y
A Y
C X
A Y
C X
B Z
C X
C X
C X
C Z
C Z
C Z
B Z
C X
B Z
C X
A X
A Y
A Y
A X
C Y
A X
C Y
A Y
B Z
C X
C X
C Y
C X
C Z
A X
A Y
C Z
A X
C X
C X
B X
C X
A Y
C X
C Z
B Z
A X
B Z
C Y
C Z
C Y
C Y
C X
C Z
C Z
C Z
A X
C X
A X
A Y
A X
C Z
C Z
A Z
C Y
B Z
A X
C Z
C Z
C X
C X
A X
A Z
C Z
C X
C X
C Y
C Y
C Y
A Y
A Y
C Z
A X
C Z
C X
A X
C Y
C Z
C Y
A X
A Y
A X
C Z
B Z
C Z
A X
C X
C Y
C X
C X
C Y
C Z
C Z
C Y
C X
A Y
C Y
C Z
B Z
C Y
C Y
A X
C Z
B Z
C X
B Z
B Z
C Z
C X
C Z
A X
C Z
C X
A Y
A X
A Y
C Z
C Z
C Z
C Z
C X
B Z
C Y
C X
B Z
C X
A X
A Y
C X
A Z
A Y
A X
C Y
C Z
C Y
C Z
B Z
C Y
C X
A Y
B Z
C Z
C Z
C Y
C X
C Z
A Y
C Y
A Y
C Z
B Z
C Z
A X
C Z
C Z
C Y
C X
C Y
A X
C Y
C Z
C X
A X
B Z
C Y
C X
C Z
C Y
A X
C X
A Y
A Y
C X
C Z
C Y
B Z
B X
C Y
C X
C X
C Z
C Y
C X
C Z
C Y
A X
B Y
A X
A Y
C X
A X
A X
A X
C Y
B X
B Z
C Z
C X
C Z
A Y
C Y
C X
B Z
A X
C X
A Y
C X
C X
C X
B Z
C Z
C X
B X
C Z
C Y
C X
C Y
C Z
C Z
C Z
A X
C X
C X
C X
B Z
C Z
A Y
C X
B Z
B Z
A Y
A Y
B Z
C X
C Y
A X
C Y
C X
C Y
C Y
C X
B Z
C Z
C Z
C Z
C Y
A Y
C Z
C Y
A X
C X
C Z
C Y
A Y
C Z
C X
B Z
C X
C Z
C Z
C Y
A X
A Y
C Z
A Y
C Z
C X
C Z
C Z
A X
A X
C X
B Z
B Z
C Y
A Y
C X
C X
C Z
C Z
A Y
C Y
C Z
A X
C X
C Y
A Y
C X
C X
A Z
C X
C Y
C Z
C X
B Z
C X
A X
C Z
C Z
A X
C Z
C Y
C Z
C Z
A Y
C X
C X
C X
C Y
C Z
C X
C X
C Y
B Z
A X
C X
A Y
B Z
A Y
A X
A X
B X
C Y
A Y
C Y
C Z
A X
C X
A Y
A Y
C Z
C X
C Z
C Z
C Z
C Z
A Y
A Y
A X
C X
A Y
C Y
A X
C X
C X
C X
B Z
C Z
B Z
A X
C Z
C Z
C Y
C X
C X
C X
C Y
A Z
B X
B Z
C X
B Z
A X
A Y
C Z
B Y
C X
C X
A Y
C Y
C Y
C Z
C X
A X
B Z
C X
A X
A X
C X
A X
C Y
B X
C Z
C Z
C Z
C Z
C X
C Z
C X
C Z
C Z
A X
C Z
C X
B Z
A Y
C Z
B Z
C Y
C X
C X
C Z
C Y
C X
C Z
C X
B X
C Z
A Y
C X
B Z
A Y
A X
C X
C X
B Z
C Y
C Z
C X
C Z
C Z
C Z
B X
C X
C X
C Y
B Z
A Y
C Y
C Z
A Z
A Y
C Z
C Y
C Y
A X
B Z
B Z
C X
A X
C Z
B Z
C Z
C Y
C Z
C Y
A X
C X
C Y
C X
B X
C Y
A Y
C X
C Z
A Z
C Y
A X
C Z
C Y
B Z
C Y
C Z
A Y
C Z
C X
A Y
C X
C Z
C X
B Z
C X
A X
C Z
C Z
C X
C Z
C X
C Z
C Z
A Z
A X
B Z
B X
C Z
C X
B Z
C X
C Y
C Z
C Z
A X
A X
C Y
B Z
A X
C X
C Z
A Z
A Z
C Z
C Y
C X
C Y
C Z
A Z
A X
A Y
C X
C Z
A Y
C Y
A Y
A X
C Z
C X
C Z
C X
B Z
A Y
C X
A X
C X
B X
C X
A X
C X
A X
C Y
A Y
C X
A Y
C X
C Z
C X
B Z
A X
C Z
A X
C Z
C Z
C Y
C Z
C Y
C X
A Y
C X
A X
C Z
C X
A Y
C Y
C X
C X
C Z
C X
C Y
C X
C X
C X
C X
A Y
A Y
A Y
C Z
C X
B Y
B Y
A Y
C Z
C X
A Y
C Z
C Y
C X
C Z
A X
C Z
C Z
C Y
A X
A X
C Z
C X
C X
C X
C Z
C Z
A Y
C Y
A X
B Z
C Z
C Y
C Z
A X
C Z
C X
C X
A Y
C Z
C X
C Z
C Z
A Y
C Y
C Z
A X
C Y
C Z
A X
C X
A X
C X
C Z
C X
C Z
C Z
C Y
C Y
A Y
C Y
A X
C Y
C X
C Z
C X
A X
C X
A X
A Y
A X
C Z
A X
C Y
C X
A Y
C Z
C Z
C X
B X
C Z
C Y
A Y
B Z
C Y
C X
B Z
C X
A Y
A X
A X
A X
C X
A X
C X
C Z
C X
A X
C Y
A Y
C X
C Z
C X
C Z
C Y
C X
A X
C X
C Y
A Y
A X
B Z
C Y
B Z
C Y
C X
A Y
C X
C Z
C X
C Y
A X
C Y
C Y
C Z
C Y
C X
C Z
C X
C X
C X
C Z
C X
A Y
A Y
C X
C Z
B Z
C X
C Y
C X
C X
C Z
C Z
C X
C X
A Z
A X
C X
B Z
C Z
C Y
C Z
C X
C X
C X
C Z
C X
A X
A X
C Z
C X
A Z
C X
A X
A X
C Z
A X
A Y
C Z
A Z
A Y
C Y
C X
A Y
A X
C Z
C X
A Y
B Z
C Z
A X
C Z
C X
A X
A Y
C Z
C Y
C Z
C Z
B Z
C X
C Z
C Z
C Y
C X
C Z
C X
C X
B Z
B Z
A Y
B X
B Z
C Z
A Z
C Y
C X
C Z
C X
C X
A X
C X
A Y
B X
C Z
C Y
C X
C Z
C Y
C Y
C X
B Z
C X
B Z
C Y
C Y
C Y
C X
C X
A X
A X
A X
C Z
A X
C Z
C X
C Y
C Z
C Y
A Y
C Y
A X
A Y
C Y
C Z
C Z
A Y
C X
C X
A X
C Y
C X
C Y
A X
C X
C Y
C Z
C Z
B Z
A Y
C X
B Z
C Y
A X
C Z
C X
C Z
B X
C Z
C Z
C Z
C X
C Z
C Z
C X
C Z
C Z
B X
A X
C Y
C Z
A Y
C Y
C Z
C Z
C X
A Y
A X
C Y
C Y
A Y
C Z
C X
C X
C X
A Y
C X
B X
C Z
C Z
C X
C Z
C X
A Y
A Z
C Z
C Z
B X
C Y
A Z
A Y
C Z
C X
C Z
C X
A X
A Y
C Y
A X
C Z
C X
C Z
B X
C X
C Z
B Z
C Z
C Y
C Y
A X
C Z
C X
C Y
C Z
C Z
A Y
C Z
C Y
C Y
A X
B Z
C Z
A X
C Y
C Y
C Z
A X
C X
C Z
C X
C X
C Z
C Y
C X
C Z
B Z
C Y
A X
A X
C X
C Z
A X
C X
B Z
C Y
C Z
C Y
C X
C Z
B Y
C X
C Z
A X
C X
A X
C X
C Z
B Z
C Z
C Z
A Z
C Y
C X
A X
C Z
A X
A Y
C X
C Z
C Y
A Y
C Y
C X
A X
C X
C Y
C X
C X
C Z
C Z
C X
C Z
A X
A X
C X
C Z
B Z
A X
C X
C Z
C Y
C X
B Z
C X
C X
C X
B X
C Y
A Y
C Z
A Z
A Y
A Y
C Y
B Z
C Z
C Y
C X
C Z
C X
B Z
B X
A X
A Z
A Y
C Z
C Y
C Y
C X
B Y
C Y
C X
C X
B X
C Y
C Z
B Z
C X
C Y
A Y
C Z
C X
C Z
A X
C Z
A X
A Y
C Y
A Y
C Y
C Z
A X
C Y
C Y
C X
B X
C Z
C X
C Z
C Z
C Z
C X
C Z
C Y
C X
C Y
C X
C X
C X
C X
A Y
C X
A Y
C X
C Z
A X
A Z
C Z
C X
C X
C X
C X
B Z
C Z
C Z
C Y
C X
C Z
C X
B Z
B Z
C Z
C Z
C X
C X
C Z
B Z
C X
A Y
C X
C Z
C X
C Y
C Z
C Z
C X
C Z
A Y
A Y
C X
C Z
C Z
C X
C X
B Z
C X
C Z
C Z
C X
C Z
A X
C Z
B Z
C Z
A Y
C Z
C X
C X
B Z
A Y
C Z
A Y
C Y
A Z
C X
A X
C X
A Y
C Z
C X
C Z
C Z
C X
C Z
A X
B Z
C Y
C Z
C Z
C X
C Z
B Z
C Y
C Z
C Z
A X
B Z
A X
B Z
C X
C Z
A Z
A Z
C X
A X
A X
B Z
A Y
A Y
A Z
C X
C Z
C Z
C X
C X
C X
A X
C X
C Z
C Y
C Z
C X
C Z
C X
A X
A Y
C X
A X
C X
B Z
B Z
B X
C X
A X
B X
C X
A Y
C Z
C Y
C Z
C X
A X
A Y
C Z
B Z
C X
B Z
C Z
B Z
A X
A X
C Y
B Z
C X
B Z
A Y
C Z
A Y
C Z
C X
A Z
C Z
C Z
B Z
A Y
B Z
C Y
C X
A Y
A X
A X
C X
C Y
B Z
C X
C Z
C Z
A X
A Y
C X
C Y
B Z
C Z
C X
A X
C Z
C X
C X
B Z
C Y
A Y
A X
C Z
B Z
C X
C Z
A Y
C X
B Z
C Y
B X
C X
C X
C Y
A Y
A X
C Y
C Y
C Z
C Y
C Y
C X
B X
C X
A Y
C Z
C Z
A Y
C Z
C Z
C Z
C Z
C Z
C Y
A Y
C Z
A X
C Y
C Z
C X
C Z
C X
A Z
C X
A Y
B Y
B Z
A Y
A Y
C Z
C X
B Z
B X
B Y
C X
C Z
B Z
A X
C X
C X
C Y
A X
C Z
C Y
A Y
A X
A X
B X
A Y
C Y
C Z
C Z
C X
C X
A X
C Z
A Z
A Y
A X
C X
A Y
B Z
C X
C Z
C Y
C Z
C Z
C X
C Z
A X
A Y
C X
C X
C X
C Z
C Y
C Z
B Z
C Z
B Z
A Y
A X
C Z
C X
C Z
C X
A X
C Z
C Z
C X
C X
C Z
A Y
A Z
A Y
C Z
C Z
C X
C Y
C X
C Y
A X
C X
A Y
B Z
B Z
C X
C X
C Z
C X
A Y
A Z
A Y
C X
C Z
A Y
C Y
C Z
B Z
A X
C X
C Z
C Z
A Y
A Y
A Y
A Y
C X
B Z
A Z
B X
A X
B X
C Z
C Z
C Z
B Z
A Y
C Z
C Y
C X
C Y
A Y
C X
C Y
C Y
A X
C Y
C X
C X
C X
C X
A Y
A Y
C X
C Z
C Z
A Y
C Z
A Y
C Z
C Z
C X
C X
C Z
C Y
C Z
A X
A X
C Y
B Z
A X
B Z
B Z
C X
C Z
C Y
A X
C Z
C Y
C Z
C Y
A Y
B X
C Y
C Y
C X
C X
C Z
C Z
C X
A Y
C Z
B Z
C Y
C X
C Y
C Z
C X
A X
A Y
C Z
B Z
C X
C Z
C X
C Z
C X
A X
C Z
A X
B Z
C X
)";
}