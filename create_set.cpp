#include "create_set.h"
#include "global.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string createSetName()
{
	string text{};
	bool invalidName{};

	do {
		invalidName = false;

		cout << "\nName your Flashcard Set: ";
		getline(cin >> ws, text);

		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == '<' || text[i] == '>' || text[i] == ':' || text[i] == '"' || text[i] == '/' || text[i] == '\\' ||
				text[i] == '|' || text[i] == '?' || text[i] == '*')
			{
				clearScreen();
				cout << "Invalid file name!\n";
				invalidName = true;
				break;
			}
		}
	} while (invalidName == true);

	return text;
}

void createOutputFile(string setName)
{
	string cont, failMessage = "", tempS;
	vector <string> termStorage, defStorage;
	bool inputFail{}, complete{};
	int cardNumber{};
	cardNumber = 1;

	do {
		clearScreen();
		cout << "Flashcards of " << setName << endl;
		cout << "Card #" << cardNumber << endl << endl;
		cout << "Term: \n";
		getline(cin >> ws, tempS);
		termStorage.push_back(tempS);

		cout << endl << endl;
		cout << "Definition: \n";
		getline(cin >> ws, tempS);
		defStorage.push_back(tempS);

		cardNumber++;
		clearScreen();
		do {
			clearScreen();
			cout << failMessage << endl;
			failMessage = "";
			inputFail = false;

			cout << "Would you like to add another card?\n"
				<< "'Y' or 'Yes' to continue\n"
				<< "'N' or 'No' to finish set\n";
			getline(cin >> ws, cont);

			if (cont == "y" || cont == "Y" || cont == "Yes" || cont == "yes")
			{

			}
			else if (cont == "n" || cont == "N" || cont == "No" || cont == "no")
			{
				complete = true;
			}
			else
			{
				failMessage = "Invalid Input!";
				inputFail = true;
			}
		} while (inputFail == true);
	} while (complete == false);

	saveToOutputFile(termStorage, defStorage, setName);
}

void saveToOutputFile(vector <string> & term, vector <string> & definition, string setName)
{
	string fileName;
	ofstream oFile;

	fileName = setName + ".txt";
	oFile.clear();
	oFile.open(fileName);

	for (int i = 0; i < term.size(); i++)
	{
		//prevents extra space in output file
		if (i != 0)
			oFile << endl;

		oFile << term[i] << endl << definition[i];
	}

	oFile.close();
	clearScreen();
	cout << setName << " has been created!\n";
}