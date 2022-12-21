#include "manage_set.h"
#include "create_set.h"
#include "global.h"
#include "load_set.h"

#include <iostream>
#include <stdio.h>
using namespace std;

void manageOptions()
{
	int choice{};
	clearScreen();
	while (1)
	{
		cout << "Manage Set Menu:\n\n";
		cout << "1 ---\t Rename a Set\n"
			<< "2 ---\t Erase a Set\n"
			<< endl
			<< "3 ---\t RETURN TO MENU\n";
		choice = cinIntCheck(choice);
		if (choice != 1 && choice != 2 && choice != 3)
		{
			clearScreen();
			cout << "ERROR: Input outside of range!\n\n";
		}
		else 
			break;
	}
	if (choice == 1)
	{
		editSetName();
	}
	else if (choice == 2)
	{
		deleteFile();
	}
	else
	{
		clearScreen();
		return;
	}
}

void deleteFile()
{
	string fileName;
	int confirm{}, status{};
	char fileNameChar[250]{};

	clearScreen();

	cout << "Select the set you would like to ERASE!\n\n";
	fileName = selectAndListFile();

	clearScreen();
	while (1)
	{
		cout << "Are you SURE you want to delete '" << fileName.substr(0, fileName.length() - 4) << "' ?" << endl << endl;
		cout << "1 ---\t Confirm\n" << "2 ---\t Cancel\n";
		confirm = cinIntCheck(confirm);
		if (confirm != 1 && confirm != 2)
		{
			clearScreen();
			cout << "ERROR: Input outside of range!\n\n";
		}
		else
			break;
	}
	if (confirm == 1)
	{
		for (int i = 0; i < fileName.size(); i++)
			fileNameChar[i] = fileName[i];

		clearScreen();
		status = remove(fileNameChar);
		if (status == 0)
			cout << fileName.substr(0, fileName.length() - 4) << " has been erased.\n\n";
		else
			cout << "ERROR: File could not be erased.\n"
			<< "You can either try again, or manually remove the file via the directory of this program.\n\n";
	}
	else if (confirm == 2)
		return;

}

void editSetName()
{
	string fileName, newName;
	char fileNameChar[250]{}, newNameChar[250]{};
	int status{};

	clearScreen();

	cout << "Select the Set Name you want to edit!\n\n";
	fileName = selectAndListFile();

	clearScreen();
	cout << "Original Set Name:\n" << fileName.substr(0, fileName.length() - 4) << endl << endl;
	newName = createSetName();
	newName += ".txt";

	for (int i = 0; i < fileName.size(); i++)
		fileNameChar[i] = fileName[i];

	for (int i = 0; i < newName.size(); i++)
		newNameChar[i] = newName[i];

	status = rename(fileNameChar, newNameChar);

	if (status == 0)
	{
		clearScreen();
		cout << fileName.substr(0, fileName.length() - 4) << " is now named " << newName.substr(0, newName.length() - 4) << "!\n\n";
	}
	else
	{
		clearScreen();
		cout << "Sorry, something went wrong.\n" << "You can try again later, or manually change the set name in the directory of this program.\n\n";
	}

	/*
	2AM Idea:
	Google if file can be coppied in c++

	otherwise,
	ask user for new name
	copy contents of selected file into array
	output same array into new text file with edited name
	use deleteFile() on prev file with same name 
	*/
}