#include "global.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

int cinIntCheck(int num)
{
	while (!(cin >> num))
	{
		cout << "ERROR: Input out of range: ";
		cin.clear();
		cin.ignore(132, '\n');
	}
	return num;
}

void pressEnterToContinue(string text)
{
	string s;
	cout << text;
	getline(cin, s);
}

void clearScreen() { std::system("cls"); }