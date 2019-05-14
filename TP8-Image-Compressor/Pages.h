#pragma once

#include "Tile.h"
#include "Allegro.h"
#define PAGETEXTSIZE 50
#define IMG_RIGHT "allegrofiles\\Right.png"
#define IMG_LEFT "allegrofiles\\Left.png"
#define IMG_DONE "allegrofiles\\Done.png"
#define IMG_MENU "allegrofiles\\Menu.png"
#define IMG_S_ALL "allegrofiles\\Select_all.png"
#define IMG_SELECTED "allegrofiles\\Selectedimage.png"
#define IMG_UN_ALL "allegrofiles\\Unselect_all.png"
#define IMG_EDA_FILE "allegrofiles\\Edafile.png"



enum ev_pages{	page_quit,page_right, page_left, page_select_all, page_deselect_all, page_back2menu,
				page_img1, page_img2, page_img3, page_img4, page_img5, page_img6, page_img7, page_img8, page_img9};

enum page_mode {p_comp, p_decomp};

enum pages_result {r_quit, r_menu, r_sucess, r_null};

class Pages
{
public:
	Pages(list<Tile>* ptile, enum page_mode mode, Allegro* pallegro);
	~Pages();
	enum pages_result SelectImages();

	void UpdatePage();
	void NextPage();
	void PrevPage();

private:
	void selectTile(int pos);
	void SelectAll();
	void DeselectAll();
	enum pages_result mouse_handler(display_pos pos);
	int pagenum;
	int totalpages;
	list<Tile>* pTile;
	Allegro* pAllegro;
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* arrow[2];
	ALLEGRO_BITMAP* select[2];
	ALLEGRO_BITMAP* selected;
	ALLEGRO_BITMAP* back2menu;
	ALLEGRO_BITMAP* done;
	ALLEGRO_BITMAP* edafile;

	enum page_mode mode;
};