// https://leetcode.com/problems/number-of-atoms/description/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctype.h>

using namespace std;

class Solution
{
public:
	void myprint(map<string,int>* counter, string str) {
		string r = "";
		for (auto const &p : *counter) {
    		r += p.first;
    		r += to_string(p.second);
		}
		cout << str << ": " << r << endl;
	}

    string countOfAtoms(string formula) {
    	map<string,int> result_counter;
    	vector<map<string,int>>  counter_stack;
    	int cur_ind = 0;
    	do {
    		char cur_char = formula[cur_ind];
    		if (cur_char == '(') {
    			map<string,int> new_counter;
    			counter_stack.push_back(new_counter);
    			cur_ind++;
    		} else if (cur_char == ')') {
    			string mult = "";
    			cur_ind++;
    			do {
    				cur_char = formula[cur_ind];
    				if (isdigit(cur_char)) {
    					mult.push_back(cur_char);
    					cur_ind++;
    				}

    			} while (isdigit(formula[cur_ind]));
    			int mult_int = mult == "" ? 1 : stoi(mult);
    			map<string,int> last_counter = counter_stack.back();
    			counter_stack.pop_back();
    			map<string,int>* target_counter = counter_stack.size() > 0 ? &counter_stack.back() : &result_counter;
    			for (auto const &p : last_counter) {
    				int cur_cnt = target_counter->count(p.first) ? target_counter->at(p.first) : 0;
    				int rr = cur_cnt + p.second * mult_int;
    				if (cur_cnt) target_counter->at(p.first) = rr;
    				else target_counter->insert({ p.first, rr });
    			}
    		} else {
    			string cur_elem = "";
    			string cur_counter = "";
    			map<string,int>* target_counter = counter_stack.size() > 0 ? &counter_stack.back() : &result_counter;
    			do {
    				char cur_char = formula[cur_ind];
    				if (isalpha(cur_char)) {
    					if(isupper(cur_char) and cur_elem.length() != 0) {
    						int target_cnt = target_counter->count(cur_elem) ? target_counter->at(cur_elem) : 0;
		    				int cur_counter_int = cur_counter == "" ? 1 : stoi(cur_counter);
		    				if (target_cnt) target_counter->at(cur_elem) = target_cnt + cur_counter_int;
		    				else target_counter->insert({ cur_elem, target_cnt + cur_counter_int });
		    				cur_elem = "";
		    				cur_counter = "";
    					}
   						cur_elem.push_back(cur_char);
    				} else {
    					cur_counter.push_back(cur_char);
    				}
    				cur_ind++;
    			} while (formula[cur_ind] != ')' && formula[cur_ind] != '(' && cur_ind < formula.length());

    			if (cur_elem.length() != 0) {
				    int target_cnt = target_counter->count(cur_elem) ? target_counter->at(cur_elem) : 0;
					int cur_counter_int = cur_counter == "" ? 1 : stoi(cur_counter);
					if (target_cnt) target_counter->at(cur_elem) = target_cnt + cur_counter_int;
		    		else target_counter->insert({ cur_elem, target_cnt + cur_counter_int });
    			}
    		}
    	} while (cur_ind < formula.length());
    	string res = "";
    	for (auto const &p : result_counter) {
    		res += p.first;
    		if (p.second > 1) {
    			res += to_string(p.second);
    		}
		}
        return res;
    }
};

int main()
{
	Solution *s = new Solution();
	// string str = "H2O";
	// string str = "Mg(OH)2"; // H2MgO2
	string str = "K4(ON(SO3)2)2"; // K4N2O14S4

    string res = s->countOfAtoms(str);

    cout << "res: " << res << endl;
    return 0;
}
