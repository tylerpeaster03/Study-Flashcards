//Name: Tyler Peaster
/*
A rewrite of flashcard software I was working on. I started the original project before
fully understanding how to take advantage of OOP, header files, etc, so as it got bigger,
it got hard to navigate and had code re-use. This rewrite brings those same features (and more!)
with better use of OOP.
*/
//Start Date: 12/16/2022
#include "create_set.h"
#include "edit_set.h"
#include "global.h"
#include "load_set.h"
#include "manage_set.h"

#include <iostream>
#include <string>
using namespace std;

class ManageFlashcardSet
{
public:
	ManageFlashcardSet()
	{
		manageOptions();
	}
private:
};

class EditFlashcardSet
{
public:
	EditFlashcardSet()
	{
		edit.loadFileForEdit();
	}

private:
	LoadForEdit edit;
};

class ViewFlashcardSet
{
public:
	ViewFlashcardSet()
	{
		load.loadFile();
		load.displaySet();
	}

private:
	loadAndOutputFlashcardSet load;
};

class CreateFlashcardSet
{
public:
	CreateFlashcardSet()
	{
		setName = createSetName();
		createOutputFile(setName);
	}

private:
	string setName;
};

class Menu {
public:
	void menuDisplay()
	{
		/*
		Putting clearScreen(); here will cause the program to never open properly in debug mode. 
		I have no idea why. Instead, put clearScreen(); before returning to menu.
		*/
		cout << "Welcome to the Flashcard Study program!\n\n"
			<< "Load Set\t --- 1\n"
			<< "Edit Set\t --- 2\n"
			<< "Create Set\t --- 3\n"
			<< "Manage Set\t --- 4\n"
			<< "Exit Program\t --- 5\n";
		menuChoice = cinIntCheck(menuChoice);

		if (menuChoice == 1)
		{
			ViewFlashcardSet vfs;
		}
		else if (menuChoice == 2)
		{
			EditFlashcardSet efs;
		}
		else if (menuChoice == 3)
		{
			CreateFlashcardSet cfs;
		}
		else if (menuChoice == 4)
		{
			ManageFlashcardSet mfs;
		}
		else if (menuChoice == 5)
		{
			clearScreen();
			cout << "Thank you for choosing this program!\n";
			exit(0);
		}
		else
		{
			clearScreen();
			cout << "ERROR: Input out of range!\n\n";
		}
	}

private:
	int menuChoice{};
};


int main()
{
	/*
	To Do:
	In the future, add a multiple choice test option
	*/
	Menu m;

	while (1)
		m.menuDisplay();
}