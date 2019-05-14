#pragma once
#include "Allegro.h"
enum menu_modes{mode_quit, unselected ,mode_compress, mode_decompress};
#define BITMAPC "allegrofiles\\Comp_botton.png"
#define BITMAPD "allegrofiles\\Decomp_botton.png"
#define SMODE "allegrofiles\\Selectedmode.png"
#define MENUTEXTSIZE 100

class Menu
{
public:
	Menu(Allegro* pallegro);
	~Menu();

	enum menu_modes GetMode();

private:
	void UpdateMenu();
	enum menu_modes mouse_handler(display_pos pos);
	enum menu_modes mode;
	Allegro* pAllegro;
	ALLEGRO_BITMAP* bitmap[2];
	ALLEGRO_BITMAP* select;
	ALLEGRO_FONT* font;
};