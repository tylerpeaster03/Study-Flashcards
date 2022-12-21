#include "edit_set.h"
#include "create_set.h"
#include "global.h"
#include "load_set.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void LoadForEdit::loadFileForEdit()
{
	LoadForEdit::loadFile();

	while (1)
	{
		location = viewEntireSet(term, setName);
		if (location == term.size()) //Allow "return to menu" to function
		{ 
			clearScreen();
			break;
		}

		editCard();
	}
}

void LoadForEdit::editCard()
{
	int choice{};

		clearScreen();
		cout << "Edit Menu:\n\n"
			<< "Original Term:\n" << term[location] << endl << endl
			<< "Original Definition:\n" << definition[location] << endl << endl
			<< "Would you like to edit the term, definition, or both?\n\n\n"
			<< "-------------------------------------\n"
			<< "1 ---\t Term\n"
			<< "2 ---\t Definition\n"
			<< "3 ---\t Both\n"
			<< "-------------------------------------\n"
			<< "4 ---\t Add Term AFTER Current Term\n"
			<< "5 ---\t Add Term BEFORE Current Term\n"
			<< "6 ---\t Remove CURRENT Term\n"
			<< "-------------------------------------\n"
			<< "7 ---\t RETURN TO MENU\n"
			<< "-------------------------------------\n";

		while (1)
		{
			choice = cinIntCheck(choice);
			if (choice < 1 || choice > 7)
				cout << "\nERROR: Input out of range\n";
			else
				break;
		}

		if (choice == 1)
		{
			editTextOnCard(term, location, "Term");
		}
		else if (choice == 2)
		{
			editTextOnCard(definition, location, "Definition");
		}
		else if (choice == 3)
		{
			editTextOnCard(term, location, "Term");
			editTextOnCard(definition, location, "Definition");
		}
		else if (choice == 4)
		{
			addVectorValue(1);
		}
		else if (choice == 5)
		{
			addVectorValue(-1);
		}
		else if (choice == 6)
		{
			while (1)
			{
				cout << "\n\nConfirm Changes?\n"
					<< "Confirm\t --- 1\n" << "Cancel\t --- 2\n";
				choice = cinIntCheck(choice);

				if (choice != 1 && choice != 2)
					"ERROR: Input out of range\n";
				else
					break;
			}

			if (choice == 1)
				removeVectorValue();
		}
		else if (choice == 7)
			return;
}

void LoadForEdit::editTextOnCard(vector <string>& vectorS, int location, string text)
{
	while (1)
	{
		string textEdit;
		int choice{};

		clearScreen();
		cout << "Edit Menu:\n\n"
			<< "Original " << text << ":" << endl << vectorS[location] << endl << endl
			<< "Edit " << text << ":" << endl;
		getline(cin >> ws, textEdit);

		while (1)
		{
		cout << "\n\nConfirm Changes?\n"
			<< "Confirm\t --- 1\n" << "Cancel\t --- 2\n";
		choice = cinIntCheck(choice);

			if (choice != 1 && choice != 2)
				"ERROR: Input out of range\n";
			else
				break;
		}

		if (choice == 1)
		{
			vectorS[location] = textEdit;
			saveToOutputFile(term, definition, setName);
		}
		if (choice == 2)
			break;

		break;
	}
}

void LoadForEdit::addVectorValue(int plusORminus1)
{
	int newLocation{};
	string newTerm, newDef, tempS;
	vector <string> holdTerm, holdDef;

	clearScreen();
	newLocation = location + plusORminus1;
	if (newLocation < 0)
		newLocation = 0;

	cout << "Card #" << newLocation + 1 << endl << endl << endl;
	cout << "Term:\n";
	getline(cin >> ws, newTerm);
	cout << endl << endl;
	cout << "Definition:\n";
	getline(cin >> ws, newDef);

	for (int i = 0; i < term.size() + 1; i++)
	{
		if (i == newLocation)
		{
			holdTerm.push_back(newTerm);
			holdDef.push_back(newDef);
		}
		else if (i < newLocation)
		{
			tempS = term[i];
			holdTerm.push_back(tempS);
			tempS = definition[i];
			holdDef.push_back(tempS);
		}
		else if (i > newLocation)
		{
			tempS = term[i - 1];
			holdTerm.push_back(tempS);
			tempS = definition[i - 1];
			holdDef.push_back(tempS);
		}
	}

	term.clear();
	definition.clear();
	for (int i = 0; i < holdTerm.size(); i++)
	{
		tempS = holdTerm[i];
		term.push_back(tempS);

		tempS = holdDef[i];
		definition.push_back(tempS);
	}

	saveToOutputFile(term, definition, setName);
}

void LoadForEdit::removeVectorValue()
{
	vector <string> ::iterator it;
	it = term.begin();
	it += location;
	term.erase(it);
	
	it = definition.begin();
	it += location;
	definition.erase(it);

	saveToOutputFile(term, definition, setName);
}
