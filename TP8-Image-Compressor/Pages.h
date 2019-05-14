#pragma once

#include "Tile.h"
#include "Allegro.h"
#define PAGETEXTSIZE 50


enum ev_pages{	page_quit,page_right, page_left, page_select_all, page_deselect_all, page_back2menu,
				page_img1, page_img2, page_img3, page_img4, page_img5, page_img6, page_img7, page_img8, page_img9};

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
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* arrow[2];
	ALLEGRO_BITMAP* select[2];
	ALLEGRO_BITMAP* back2menu;
	int mode;
};