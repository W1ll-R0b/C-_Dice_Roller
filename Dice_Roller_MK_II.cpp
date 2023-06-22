#include <chrono>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
using namespace std;

int roll(int x) {
  random_device rd;
  mt19937 engine{rd()};
  uniform_int_distribution<> randomDie(1, x);
  return randomDie(engine);
}

int main() {
  vector<int> Rolled;
  int diceno = 1;
  int modifier = 0;
  int value = 0;
  size_t plusminus;
  while (false == false) {
    Rolled.clear();
    diceno = 1;
    modifier = 0;
    cout << "\nEnter dice prompt to roll, \"stat-gen\" for character stat "
            "generation, or -1 to quit\n(XdX+X)\n\n";
    string input;
    cin >> input;
    if (input == "-1") {
      break;
    }
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
    if (input.find_first_not_of("0123456789") == string::npos && input != "0") {
      int value(stoi(input));
      Rolled.push_back(roll(value));
    } else if (input.find_first_not_of("+-dD0123456789") == string::npos &&
               input != "0") {
      size_t D = input.find_first_of("dD");
      plusminus = input.find_first_of("+-");

      if (D != input.find_last_of("dD") ||
          plusminus != input.find_last_of("+-")) {
        cout << "\nInvalid Input\n";
        continue;
      }

      if (D != string::npos && D != 0) {
        if (input.substr(0, D).find_first_not_of("0123456789") ==
                string::npos &&
            input.substr(0, D) != "0") {
          diceno = stoi(input.substr(0, D));
          input = input.substr((D + 1), (input.size() - D - 1));
        } else {
          cout << "\nInvalid Input\n";
        }
      }
      plusminus = input.find_first_of("+-");
      if (plusminus != string::npos && plusminus != 0) {
        if (input.substr(0, plusminus).find_first_not_of("0123456789") ==
                string::npos &&
            input.substr((plusminus + 1), (input.size() - 1 - plusminus))
                    .find_first_not_of("0123456789") == string::npos) {
          value = stoi(input.substr(0, plusminus));
          modifier = stoi(
              input.substr((plusminus + 1), (input.size() - 1 - plusminus)));
        } else {
          cout << "\nInvalid Input\n";
        }
      } else if (plusminus == 0) {
        cout << "\nInvalid Input\n";
        continue;
      } else {
        value = stoi(input);
      }

      int i = 0;
      while (i < diceno) {
        Rolled.push_back(roll(value));
        i++;
      }
    } else {
      cout << "\nInvalid Input\n";
      continue;
    }

    int sum = accumulate(Rolled.begin(), Rolled.end(), 0);
    if (modifier != 0) {
      if (input[plusminus] == '+') {
        sum = sum + modifier;
      }
      if (input[plusminus] == '-') {
        sum = sum - modifier;
      }
    }
    cout << "\nRolled " << sum;

    int ii = 0;
    cout << "\n(";
    while (ii < Rolled.size()) {
      cout << Rolled[ii];
      if (ii < (Rolled.size() - 1)) {
        cout << " + ";
      }
      ii++;
    }
    cout << ")";
    if (input[plusminus] == '-') {
      cout << " - " << modifier << endl;
    } else
      cout << " + " << modifier << endl;
  }
}