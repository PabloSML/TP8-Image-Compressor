//***********************************  INCLUDES  *******************************************
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <boost/filesystem.hpp>
#include "UserData.h"
#include "parser.h"
#include "Callback.h"
#include "lodepng.h"
#include "Filesystem.h"
#include "Menu.h"
#include "Tile.h"
#include "Compressor.h"
#include "Decompressor.h"
#include "Pages.h"
using namespace std;
//***********************************  DEFINES  *******************************************
#define PATH_AND_THRESHOLD 2
#define JUST_PATH 1
#define PNG_EXTENSION ".png"
#define EDA_EXTENSION ".eda"
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
		list<Tile>* pngTileList = generateTileList(*pngList);

		for (path t : *pngList)
		{
			compress(t, myData.getThreshold());
		}

		list<path>* edaList = lookForFiles(*(myData.getPath()), EDA_EXTENSION);
		for (path t : *edaList)
		{
			decompress(t);
		}
		list<Tile>* edaTileList = generateTileList(*edaList, IMG_EDA_FILE);

		delete edaList;
		delete pngList;
		delete pngTileList;
		delete edaTileList;
	}

	else if (parseResult == JUST_PATH && myData.isPathFull())	//en este caso solamente se ingreso path
	{
		cout << "Se recibio el path" << endl;
		list<path>* edaList = lookForFiles(*(myData.getPath()), EDA_EXTENSION);
		for (path t : *edaList)
		{
			decompress(t);
		}

		delete edaList;
	}

	else // en este caso se encontro un error en el parseo
	{
		cout << "Invalid input" << endl;
	}

	system("pause");
	return 0;
}*/


/*PRUEBA PARA COMPRESOR*/
/*
int main(void)
{
	boost::filesystem::path file = ("C:\\Users\\Agust�n M\\source\\repos\\PabloSML\\TP8-Image-Compressor\\descarga.png");
	//list<boost::filesystem::path> lista;
	if (boost::filesystem::is_regular_file(file))
	{
		compress(file, 100);
	}
	else
	{
		cout << "not a file" << endl;
	}
	cout << "press enter";
	getchar();
	return 0;
}*/
 /*prueba allegro*/
int main()
{
	Allegro al_display;
	Menu menu(&al_display);
	std::cout << menu.GetMode() << std::endl;

	getchar();
}