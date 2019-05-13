#pragma once

#include "Tile.h"
#include "Allegro.h"

class Pages
{
public:
	Pages(list<Tile>* ptile, int mode, Allegro* pallegro);
	~Pages();
	void UpdatePage();
	void NextPage();
	void PrevPage();
	int GetPageNum();

private:
	int pagenum;
	int totalpages;
	list<Tile>* pTile;
	Allegro* pAllegro;
	int mode;
};