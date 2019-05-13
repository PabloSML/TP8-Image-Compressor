#pragma once
#include "Allegro.h"
enum menu_modes{unselected ,mode_compress, mode_decompress};
#define BITMAP1 "allegrofiles\\Comp_botton"
#define BITMAP2 "allegrofiles\\Decomp_botton"
#define MENUTEXTSIZE 100

class Menu
{
public:
	Menu(Allegro* pallegro);
	~Menu();

	void UpdateMenu();
	int GetMode();

private:
	enum menu_modes mode;
	Allegro* pAllegro;
	ALLEGRO_BITMAP* bitmap[2];
	ALLEGRO_FONT* font;
};