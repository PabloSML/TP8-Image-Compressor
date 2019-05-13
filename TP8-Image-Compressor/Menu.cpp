#include <stdio.h>

#include "Menu.h"


Menu::Menu(Allegro* pallegro)
{
	pAllegro = pallegro;
	bitmap[0] = al_load_bitmap(BITMAP1);
	bitmap[1] = al_load_bitmap(BITMAP2);
	font = al_load_ttf_font(TEXTFONT, MENUTEXTSIZE,0);
	mode = unselected;

}

Menu::~Menu()
{

}

int Menu::GetMode()
{
	pAllegro->setDisplayColor(0, 0, 0);
	pAllegro->printText("Select Mode:", 650, 300, center, font);
	al_draw_bitmap(bitmap[0], 400, 700, 0);
	al_draw_bitmap(bitmap[1], 400, 1150, 0);
	pAllegro->updateDisplay();

	bool done = false;

	while (!done)
	{

	}

}
