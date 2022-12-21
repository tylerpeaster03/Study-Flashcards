#ifndef EDIT_SET_H
#define EDIT_SET_H

#include "load_set.h"
/*
Let users see all terms and defs AT THE SAME TIME
Show as list (use viewall?)
When editing a term, try and find a way to put the pre-existing stream into the getline
Save term edit, overwrite original file

don't forget classes exist!
*/

class LoadForEdit : public loadAndOutputFlashcardSet
{
public:
	void loadFileForEdit();
	void editCard();
	void editTextOnCard(std::vector <std::string>& vectorS, int location, std::string text);
	void addVectorValue(int plusORminus1);
	void removeVectorValue();
private:
	int location{};
};

#endif