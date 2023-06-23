#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <regex>
using namespace std;


int roll(int x) 
{
    if (x == 0)
    {
        return 0;
    }
    else
    {
        random_device rd;
        mt19937 engine{rd()};
        uniform_int_distribution<> randomDie(1, x);
        return randomDie(engine);
    }

}

void print(vector<int> Rolled, string input, int diceno, int value, int modifier);

int main() {

    regex reg1 ("\\d*[dD]\\d{1,100}[+-]\\d{1,100}");
    regex reg2 ("\\d*[dD]\\d{1,100}");
    regex reg3 ("\\d{1,100}[+-]\\d{1,100}");
    vector<int> Rolled;
    int diceno = 1;
    int modifier = 0;
    int value = 0;
    while (true) {
        Rolled.clear();
        diceno = 1;
        modifier = 0;
        cout << "\nEnter dice prompt to roll, \"stat-gen\" for character stat "
                "generation, or -1 to quit\n(XdX+X)\n\n";
        string input;
        cin >> input;
        if (input == "stat-gen") {
            vector<int> stats;
            vector<int> sums;
            sums.clear();
            int iii = 0;
            while (iii < 6) {
                stats.clear();
                int iiii = 0;
                while (iiii < 4) {
                stats.push_back(roll(6));
                iiii++;
                }
                sort(stats.begin(), stats.end());
                int sum = stats[1] + stats[2] + stats[3];
                sums.push_back(sum);
                cout << "\nRolled " << sum << endl
                    << "(" << stats[3] << ", " << stats[2] << ", " << stats[1] << ", *"
                    << stats[0] << "*)\n";
                iii++;
            }
            float average = (accumulate(sums.begin(), sums.end(), 0) / 6.00);
            cout << "Average: " << average << endl;
            continue;
            }
        else if(regex_match(input, reg1) == true)
        {
            size_t dplace = input.find_first_of("dD");
            size_t modplace = input.find_first_of("+-");
            if (input[0] != 'd' && input[0] != 'D')
            {
                diceno = stoi(input.substr(0, dplace));

            }
            value = stoi(input.substr(dplace + 1, (modplace - dplace)));
            modifier = stoi(input.substr(modplace + 1, (input.size() - modplace)));
        }
        else if(regex_match(input, reg2) == true)
        {

            size_t dplace = input.find_first_of("dD");
            if (input[0] != 'd' && input[0] != 'D')
            {
                diceno = stoi(input.substr(0, dplace));
            }
            value = stoi(input.substr(dplace + 1, (input.size() - dplace)));
        }
        else if(regex_match(input, reg3) == true)
        {
            size_t modplace = input.find_first_of("+-");
            value = stoi(input.substr(0, modplace));
            modifier = stoi(input.substr(modplace + 1, (input.size() - modplace)));
        }
        else if(input.find_first_not_of("0123456789") == string::npos)
        {
            value = stoi(input);
        }
        else if(input == "-1")
        {
            break; 
        }
        else
        {
            cout << "\nInvalid Entry\n"; 
            continue;
        }
        print(Rolled, input, diceno, value, modifier);
    }



}

void print(vector<int> Rolled, string input, int diceno, int value, int modifier)
{
    int check = 0;
    for (int i = 0; i < diceno; i++) 
    {
        Rolled.push_back(roll(value));
    }

    int sum = accumulate(Rolled.begin(), Rolled.end(), 0);
    if (modifier != 0) {
    if (input.find("+") != string::npos) 
    {
       sum = sum + modifier;
            check = 1;
    }
    else if (input.find("-") != string::npos) 
    {
        sum = sum - modifier;
        check = 2;
    }
    }
    cout << "\nRolled " << sum;
    int ii = 0;
    cout << "\n(";
    while (ii < Rolled.size()) 
    {
        cout << Rolled[ii];
        if (ii < (Rolled.size() - 1)) 
        {
            cout << " + ";
        }
        ii++;
    }
    cout << ")";
    if (check == 1)
    {
        cout << " + " << modifier << endl;
    }
    else if (check == 2)
    {
        cout << " - " << modifier << endl;
    }
    else
    {
        cout << endl;
    }
}