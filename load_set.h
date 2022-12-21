#ifndef LOAD_SET_H
#define LOAD_SET_H

#include <vector>
#include <string>

int viewEntireSet(std::vector <std::string>& vectorS, std::string setName);

std::string selectAndListFile();

class loadAndOutputFlashcardSet
{
public:
	void loadFile();
	void displaySet();
	void shuffleSet(std::vector <std::string> & term, std::vector <std::string> & definition);

protected:
	std::vector <std::string> term, definition;
	std::string fileName, setName;
	int location{};
};

#endif
