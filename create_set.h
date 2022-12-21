#ifndef CREATE_SET_H
#define CREATE_SET_H

#include <string>
#include <vector>

std::string createSetName();

void createOutputFile(std::string setName);

void saveToOutputFile(std::vector <std::string> & term, std::vector <std::string> & definition, std::string setName);

#endif
