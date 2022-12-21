#include "global.h"

#include <iostream>
#include <string>
#include <iomanip>
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

void clearScreen() { cout << "\033[2J\033[1;1H"; }