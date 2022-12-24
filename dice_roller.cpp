#include <iostream>
#include <sstream>
#include <cmath>
#include <random>
#include <string>
#include <ctype.h>
#include <vector>
#include <numeric>
using namespace std;

int roll(int x);
int nconversion(string x);
int naltconversion(string x);

int main() {
	int result;
	int dicetype;
	int diceamount;
	int mod;
	string type;
	string amount;
	string modifier;
	string dietype;
	string check1 = "+";
	string check2 = "d";
	string check3 = "D";
	vector<int> results;
	cout << "Enter Die Type, Amount, and Modifiers or \"END\" to Cancel (Formats: x, xdx, x+x, xdx+x)\n\n";
	while (true)
	{
		results.clear();
		int dplace = -1;
		int plusplace = -1;
		cin >> dietype;
		if (dietype == "END")
		{
			break;
		}
		size_t found = dietype.find(check2);
		if (found != string::npos)
		{
			dplace = found;

		}
		else 
		{
			found = dietype.find(check3);
			if (found != string::npos)
			{
				dplace = found;

			}
		}
		found = dietype.find(check1);
		if (found != string::npos)
		{
			plusplace = found;

		}
		if (plusplace == -1 && dplace == -1)
		{
			dicetype = nconversion(dietype);
			if (dicetype == -1 || dicetype == 0)
			{
				cout << "Invalid Entry\n\n";
			}
			else
			{
				result = roll(dicetype);
				cout << "Rolled " << result << "\n(" << result << ")\n\n";
			}
		}
		else if (plusplace != -1 && dplace == -1)
		{
			type = dietype.substr(0, (plusplace));
			modifier = dietype.substr((plusplace+1));
			dicetype = nconversion(type);
			mod = nconversion(modifier);
			if (dicetype == -1 || mod == -1 || dicetype == 0)
			{
				cout << "Invalid Entry\n\n";
			}
			else
			{
				result = roll(dicetype);
				cout << "Rolled " << (result+mod) << "\n(" << result << ")+" << mod << "\n\n";
			}
		}
		else if (plusplace == -1 && dplace != -1)
		{
			type = dietype.substr((dplace+1));
			amount = dietype.substr(0, (dplace));
			dicetype = nconversion(type);
			diceamount = naltconversion(amount);
			if (diceamount == -1 || dicetype == -1 || dicetype == 0)
			{
				cout << "Invalid Entry\n\n";
			}
			else
			{
				for (int i = 0; i < diceamount; i++)
				{
					results.push_back(roll(dicetype));
				}
				int d =  results.size();
				result = accumulate(results.begin(),results.end(),0);
				cout << "Rolled " << result << "\n(";
				int c = 0;
				for (int i: results)
				{
					if (c == (d-1))
					{
						cout << i;
						break;
					}
					cout << i << ", ";
					c++;
				}
				cout << ")\n\n";
			}
		}
		else if (plusplace != -1 && dplace != -1)
		{
			type = dietype.substr((dplace+1),(plusplace - dplace - 1));
			amount = dietype.substr(0, (dplace));
			modifier = dietype.substr((plusplace+1));
			dicetype = nconversion(type);
			diceamount = naltconversion(amount);
			mod = nconversion(modifier);
			if (diceamount == -1 || dicetype == -1 || mod == -1 || dicetype == 0)
			{
				cout << "Invalid Entry\n\n";
			}
			else
			{
				for (int i = 0; i < diceamount; i++)
				{
					results.push_back(roll(dicetype));
				}
				int d =  results.size();
				result = (accumulate(results.begin(),results.end(),0)+mod);
				cout << "Rolled " << result << "\n(";
				int c = 0;
				for (int i: results)
				{
					if (c == (d-1))
					{
						cout << i;
						break;
					}
					cout << i << ", ";
					c++;
				}
				cout << ")+" << mod << "\n\n";
			}
		}
	}
}

int nconversion(string x)
{
	if (x.empty())
	{
		return -1;
	}
	for (int i = 0; i < size(x); i++) 
	{
      if (isdigit(x[i]) == false)
	  {
		return -1;
	  }
    }
	int checkv = stoi(x);
	return checkv;
}

int naltconversion(string x)
{
	if (x.empty())
	{
		return 1;
	}
	for (int i = 0; i < size(x); i++) 
	{
      if (isdigit(x[i]) == false)
	  {
		return -1;
	  }
    }
	int checkv = stoi(x);
	return checkv;
}

int roll(int x)
{
	random_device rd;
	mt19937 engine{ rd() };
	uniform_int_distribution<> randomDie(1, x);
	return randomDie(engine);
}