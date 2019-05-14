#include <stdio.h>

#include "Menu.h"


Menu::Menu(Allegro* pallegro)
{
	pAllegro = pallegro;
	bitmap[0] = al_load_bitmap(BITMAPC);
	bitmap[1] = al_load_bitmap(BITMAPD);
	select = al_load_bitmap(SMODE);
	font = al_load_ttf_font(TEXTFONT, MENUTEXTSIZE,0);
	mode = unselected;

}

Menu::~Menu()
{

}

enum menu_modes Menu::GetMode()
{
	mode = unselected;
	
	UpdateMenu();

	bool done = false;
	al_event ev;

	while (!done)
	{
		ev = pAllegro->getNextEvent();
		switch (ev)
		{
		case ev_quit:
			mode = mode_quit;
			done = true;
			break;
		case ev_mode_comp:
			mode = mode_compress;
			UpdateMenu();
			break;
		case ev_mode_decomp:
			mode = mode_decompress;
			UpdateMenu();
			break;
		case ev_mouse:
			enum menu_modes m = mouse_handler(pAllegro->GetMousePos());
			if (m != unselected)
				mode = m;
			done = true;
		}

	}
	return mode;

}

void Menu::UpdateMenu()
{
	pAllegro->setDisplayColor(0, 0, 0);
	int scale_x = pAllegro->GetDisplayW() / DISPLAY_W;
	int scale_y = pAllegro->GetDisplayH() / DISPLAY_H;
	pAllegro->printText("Select Mode:", 650 * scale_x, 300 * scale_y, center, font);
	//al_draw_bitmap(bitmap[0], 400, 700, 0);
	//al_draw_bitmap(bitmap[1], 400, 1150, 0);

	pAllegro->drawImage(bitmap[0], 400 * scale_x, 700 * scale_y, scale_x, scale_y);
	pAllegro->drawImage(bitmap[1], 400 * scale_x, 1150 * scale_y, scale_x, scale_y);

	switch (mode)
	{
	case mode_compress:
		pAllegro->drawImage(select, (400-10) * scale_x, (700-10) * scale_y, scale_x, scale_y);
		break;
	case mode_decompress:
		pAllegro->drawImage(select, (400-10) * scale_x, (1150-10) * scale_y, scale_x, scale_y);
		break;
	}

	pAllegro->updateDisplay();
}

enum menu_modes Menu::mouse_handler(display_pos pos)
{
	int scale_x = pAllegro->GetDisplayW() / DISPLAY_W;
	int scale_y = pAllegro->GetDisplayH() / DISPLAY_H;

	if ((pos.x >= 400 * scale_x) && (pos.x <= (400 + 500)*scale_x))
	{
		if ((pos.y >= 700 * scale_y) && (pos.y <= (700 + 150)*scale_y))
			return mode_compress;
		else if ((pos.y >= 1150 * scale_y) && (pos.y <= (1150 + 150)*scale_y))
			return mode_decompress;
		else
			return unselected;
	}
	else
		return unselected;
}
