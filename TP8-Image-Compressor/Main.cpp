//***********************************  INCLUDES  *******************************************
#include <iostream>
#include <iterator>
#include <list>
//#include <algorithm> no se como se usa, puede servir para el Quad Tree
#include <string>
#include <boost/filesystem.hpp>
#include "UserData.h"
#include "parser.h"
#include "Callback.h"
#include "lodepng.h"
using namespace std;
//***********************************  DEFINES  *******************************************
#define PATH_AND_THRESHOLD 2
#define JUST_PATH 1
//***********************************  FUNCION QUE ESTOY ARMANDO  *******************************************
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
//***********************************  MAIN  *******************************************
int main(int argc, const char *argv[])
{
	userData myData;
	int parseResult = parseCmdLine(argc, argv, parseCallBack, &myData);

	if (parseResult == PATH_AND_THRESHOLD && myData.isDataFull())	//en este caso se ingresaron ambas variables
	{
		cout << "Se recibieron ambas" << endl;
		list<path>* listaPNGs = lookForPNGs(*(myData.getPath()));
		delete listaPNGs;
	}

	else if (parseResult == JUST_PATH && myData.isPathFull())	//en este caso solamente se ingreso path
	{
		cout << "Se recibio el path" << endl;
	}

	else // en este caso se encontro un error en el parseo
	{
		cout << "Invalid input" << endl;
	}

	system("pause");
	return 0;
}


