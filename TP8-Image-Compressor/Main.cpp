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
#include "Filesystem.h"
#include "Tile.h"
#include "Compressor.h"
using namespace std;
//***********************************  DEFINES  *******************************************
#define PATH_AND_THRESHOLD 2
#define JUST_PATH 1
#define PNG_EXTENSION ".png"
//***********************************  FUNCION QUE ESTOY ARMANDO  *******************************************



//***********************************  MAIN  *******************************************
/*
int main(int argc, const char *argv[])
{
	userData myData;
	int parseResult = parseCmdLine(argc, argv, parseCallBack, &myData);

	if (parseResult == PATH_AND_THRESHOLD && myData.isDataFull())	//en este caso se ingresaron ambas variables
	{
		cout << "Se recibieron ambas" << endl;
		list<path>* pngList = lookForFiles(*(myData.getPath()), PNG_EXTENSION);
		list<Tile>* tileList = generateTileList(*pngList);

		delete pngList;
		delete tileList;
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
}*/
/*PRUEBA PARA COMPRESOR*/

int main(void)
{
	boost::filesystem::path file = ("C:\\Users\\Agustín M\\source\\repos\\PabloSML\\TP8-Image-Compressor\\descarga.png");
	list<boost::filesystem::path> lista;
	if (boost::filesystem::is_regular_file(file))
	{
		compress(file, 100, lista);
	}
	else
	{
		cout << "not a file" << endl;
	}
	getchar();
	return 0;
}