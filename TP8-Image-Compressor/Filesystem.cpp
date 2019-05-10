#include <iostream>
#include <string>
#include "Filesystem.h"

list<path>* lookForPNGs(path& dir)
{
	list<path>* temp = new list<path>;
	for (directory_iterator itr(dir); itr != directory_iterator(); itr++)
	{
		string tempstr = itr->path().filename().string();
		if (tempstr.find(".png") == tempstr.length() - 4)
		{
			temp->push_back(itr->path());
			cout << "se encontro un png" << endl;
		}
	}
	return temp;
}