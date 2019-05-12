#include <iostream>
#include <string>
#include "Filesystem.h"

list<path>* lookForFiles(path& dir, const char* fileExtension)
{
	list<path>* temp = new list<path>;
	for (directory_iterator itr(dir); itr != directory_iterator(); itr++)
	{
		string tempstr = itr->path().filename().string();
		if (tempstr.find(fileExtension) != string::npos && tempstr.find(fileExtension) == tempstr.length() - strlen(fileExtension))
		{
			temp->push_back(itr->path());
			cout << "se encontro un " << fileExtension << endl;
		}
	}
	return temp;
}