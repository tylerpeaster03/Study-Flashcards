#include "load_set.h"
#include "global.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>
using namespace std;

int viewEntireSet(vector <string>& vectorS, string setName)
{//pass term to list all terms, pass definition to list all definitions
	int choice{};

	clearScreen();
	cout << "All Flashcards of " << setName << endl << endl << endl;

	for (int i = 0; i < vectorS.size(); i++)
		cout << i + 1 << " ----\t" << vectorS[i] << endl;

	cout << endl << vectorS.size() + 1 << " ----\t" << "RETURN TO MENU\n\n";

	while (1)
	{
		cout << "\n\nEnter the corresponding number: ";
		choice = cinIntCheck(choice);
		choice--;

		if (choice < 0 || choice > vectorS.size())
		{
			cout << "ERROR: Input out of range\n\n";
		}
		else
			break;
	}

	return choice;
}

string selectAndListFile()
{
	string tempS;
	vector <string> fileNamesVector;
	int counter{}, choice{};
	counter = 1;
	namespace fs = filesystem;

	for (const auto& entry : fs::directory_iterator(".")) {
		// Get the file name and extension
		string fileName = entry.path().filename().string();
		string fileExtension = entry.path().extension().string();

		// Check if the file is a .txt file
		if (fileExtension == ".txt")
		{
			fileName = fileName.substr(0, fileName.length() - 4);
			cout << counter << " ---\t" << fileName << endl;

			tempS = fileName;
			fileNamesVector.push_back(tempS);

			counter++;
		}
	}
	if (counter == 1)
	{
		clearScreen();
		cout << "No sets have been created yet!\n\n";
		return NULL;
	}

	do {
		cout << "\n\nInput the corresponding number: ";
		choice = cinIntCheck(choice);
		choice--;
		if (choice < 0 || choice >= fileNamesVector.size())
		{
			cout << "\nERROR: Input outside of range.\n";
		}
	} while (choice < 0 || choice >= fileNamesVector.size());

	tempS = fileNamesVector[choice];
	tempS += ".txt";

	return tempS;
}

void loadAndOutputFlashcardSet::loadFile()
{
	ifstream iFile;
	string tempS;

	iFile.clear();
	clearScreen();

	fileName = selectAndListFile();
	setName = fileName.substr(0, fileName.length() - 4);
	iFile.open(fileName);

	if (!iFile.is_open())
	{
		clearScreen();
		cout << "FATAL ERROR: File: '" << fileName << "' could not be opened!";
		exit(1);
	}

	while (iFile.good())
	{
		getline(iFile >> ws, tempS);
		term.push_back(tempS);

		getline(iFile >> ws, tempS);
		definition.push_back(tempS);
	}
	iFile.close();
}

void loadAndOutputFlashcardSet::displaySet()
{
	int tempI{};
	string choice;
	string shuffleConfirm{};
	location = 0;	//This tracks what card we are on
	/*
	Note:
	Location should correspond to a data slot in the term/def vectors.
	When presented to the user, they need to see Location++, since 
	the set is shown to be 1... end when in the vector its 0... end
	*/
	cin.ignore();
	while (1)
	{
		clearScreen();
		cout << setName << endl;
		cout << "Card #" << location + 1 << " / " << term.size() << endl;
		cout << "-------------------------------------\n";
		cout << "TERM: \n" << term[location];
		cout << endl << endl;

		pressEnterToContinue("-------------------------------------\nFlip Card\t --- ENTER\n-------------------------------------\n");

		clearScreen();
		cout << setName << endl;
		cout << "Card #" << location + 1 << " / " << term.size() << endl;
		cout << "-------------------------------------\n";
		cout << "DEFINITION: \n" << definition[location];
		cout << endl << endl;

		cout
			<< "-------------------------------------\n"
			<< "Flip Card\t --- ENTER\n"
			<< "-------------------------------------\n"
			<< "Next Card\t --- 1\n"
			<< "Previous Card\t --- 2\n"
			<< "-------------------------------------\n"
			<< "View Entire Set\t --- 3\n"
			<< "Shuffle Set\t --- 4\n"
			<< "-------------------------------------\n"
			<< "Return to Menu\t --- 5\n"
			<< "-------------------------------------\n";
		getline(cin, choice);

		if (choice == "\n")
		{
			
		}
		else if (choice == "1")
		{
			location++;
			if (location >= term.size())
				location = 0;
		}
		else if (choice == "2")
		{
			location--;
			if (location < 0)
				location = term.size() - 1;
		}
		else if (choice == "3")
		{
			tempI = location;
			location = viewEntireSet(term, setName);
			if (location == term.size())	//Allows "return to menu" w/o auto-reset to 0
				location = tempI;
		}
		else if (choice == "4")
		{
			cout << "\nAre you sure you want to shuffle this set?\n"
				<< "'Y' or 'Yes' to Confirm Shuffle\n"
				<< "'N' or 'No' to Cancel Shuffle\n";
			getline(cin >> ws, shuffleConfirm);

			if (shuffleConfirm == "Y" || shuffleConfirm == "y" || shuffleConfirm == "Yes" || shuffleConfirm == "yes")
				loadAndOutputFlashcardSet::shuffleSet(term, definition);
		}
		else if (choice == "5")
		{
			clearScreen();
			break;
		}
	}
}

void loadAndOutputFlashcardSet::shuffleSet(vector <string>& term, vector <string>& definition)
{
	vector <string> termShuf, defShuf, termOrg, defOrg;
	bool moveOn{};
	int k = 0, numericChoice{}, countOut = 0, countIn = 0, x = 0, y = 0;
	string tempS, shufCount, indivTerm, indivDef, setName, choice, finTerm, finDef, shuffleConfirm;

	//Clear variables for multiple shuffles
	termShuf.clear();
	defShuf.clear();
	termOrg.clear();
	defOrg.clear();
	countOut = 0;
	countIn = 0;
	x = 0;
	y = 0;

	for (int i = 0; i < term.size(); i++)
	{
		shufCount = to_string(i + 1000);

		tempS = term[i] + shufCount;
		termShuf.push_back(tempS);

		tempS = definition[i] + shufCount;
		defShuf.push_back(tempS);
	}

	mt19937 rng;
	rng.seed(random_device()());

	std::shuffle(termShuf.begin(), termShuf.end(), rng);

	while (countOut < term.size())
	{
		indivTerm = termShuf[countOut];
		indivDef = defShuf[countIn];

		x = indivTerm.size();
		y = indivDef.size();

		if (indivTerm[x - 1] == indivDef[y - 1] && indivTerm[x - 2] == indivDef[y - 2]
			&& indivTerm[x - 3] == indivDef[y - 3] && indivTerm[x - 4] == indivDef[y - 4])
		{
			tempS = indivTerm;
			termOrg.push_back(tempS);

			tempS = indivDef;
			defOrg.push_back(tempS);

			countOut++;
			countIn = 0;
		}
		else
			countIn++;
	}

	for (int i = 0; i < term.size(); i++)
	{
		finTerm = termOrg[i];
		finDef = defOrg[i];

		finTerm = finTerm.substr(0, finTerm.length() - 4);
		finDef = finDef.substr(0, finDef.length() - 4);

		term[i] = finTerm;
		definition[i] = finDef;
	}
}