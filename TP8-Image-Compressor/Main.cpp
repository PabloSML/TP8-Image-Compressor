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
						path temp = t.getPath();
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
						path temp = t.getPath();
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