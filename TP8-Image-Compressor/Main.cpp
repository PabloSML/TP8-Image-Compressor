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
	boost::filesystem::path file = ("C:\\Users\\Agustín M\\source\\repos\\PabloSML\\TP8-Image-Compressor\\descarga.png");
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
int main(int argc, const char *argv[])
{
	userData myData;
	int parseResult = parseCmdLine(argc, argv, parseCallBack, &myData);

	if ((parseResult == PATH_AND_THRESHOLD || parseResult == JUST_PATH) && myData.isPathFull())
	{
		Allegro al_display;
		Menu menu(&al_display);

		list<path>* pngList;
		list<Tile>* pngTileList;
		list<path>* edaList;
		list<Tile>* edaTileList;
		bool gotoMenu;
		do
		{
			gotoMenu = false;
			enum menu_modes mode = menu.GetMode();

			if (mode == mode_compress)
			{

				while (!(myData.isDataFull()))
				{
					float temp;
					const char* message = "Please input valid threshold percentage (0% - 100%) in terminal";
					ALLEGRO_FONT* tempFont = al_load_ttf_font(TEXTFONT, al_display.GetDisplayH()*0.02, 0);
					al_display.setDisplayColor(0, 0, 0);
					al_display.printText(message, al_display.GetDisplayW() /2 , al_display.GetDisplayH() /2, align::center, tempFont);
					al_display.updateDisplay();
					cout << "Please input valid threshold" << endl;
					cin >> temp;

					if (temp >= 0.0 && temp <= 100.0)
						myData.setThreshold(temp);
				}

				pngList = lookForFiles(*(myData.getPath()), PNG_EXTENSION);
				pngTileList = generateTileList(*pngList);
				Pages page(pngTileList, p_comp, &al_display);
				enum pages_result result = page.SelectImages();
				if (result == r_sucess)
				{
					for (Tile t : *pngTileList)
					{
						path temp(t.getName());
						if (t.isSelected())
							compress(temp, myData.getThreshold());
					}
					cout << "success" << endl;
				}
				else if (result == r_menu)
				{
					gotoMenu = true;
				}
				else if (result == r_quit)
					cout << "quit" << endl;
				delete pngList;
				delete pngTileList;
			}
			else if (mode == mode_decompress)
			{
				edaList = lookForFiles(*(myData.getPath()), EDA_EXTENSION);
				edaTileList = generateTileList(*edaList, IMG_EDA_FILE);
				Pages page(edaTileList, p_decomp, &al_display);
				enum pages_result result = page.SelectImages();
				if (result == r_sucess)
				{
					for (Tile t : *edaTileList)
					{
						path temp(t.getName());
						if (t.isSelected())
							decompress(temp);
					}
					cout << "success" << endl;
				}
				else if (result == r_menu)
				{
					gotoMenu = true;
				}
				else if (result == r_quit)
					cout << "quit" << endl;
				delete edaList;
				delete edaTileList;
			}
		} while (gotoMenu);
	}

	else
	{
		cout << "Invalid Input" << endl;
	}
	
	system("pause");
	return 0;
}