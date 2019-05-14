#pragma once

#include "Tile.h"
#include "Allegro.h"

enum ev_pages{};

class Pages
{
public:
	Pages(list<Tile>* ptile, int mode, Allegro* pallegro);
	~Pages();
	void SelectImages();

	void UpdatePage();
	void NextPage();
	void PrevPage();
	int GetPageNum();

private:
	enum ev_pages mouse_handler(display_pos pos);
	int pagenum;
	int totalpages;
	list<Tile>* pTile;
	Allegro* pAllegro;
	int mode;
};