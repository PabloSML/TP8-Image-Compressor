#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <boost/filesystem.hpp>
#include "Allegro.h"
using namespace std;
using namespace boost::filesystem;

struct position {
	int posx;
	int posy;
	int posz;
};

class Tile
{
public:
	Tile() {
		selected = false;
		name = string("");
		image = nullptr;
		pos.posx = pos.posy = pos.posz = NULL;
	}

	Tile(string name, path orgPath, string imagePath, position pos);

	void select(void);
	void unSelect(void);
	bool isSelected(void);

	string getName(void);
	path getPath(void) { return orgPath; }

	void draw(Allegro* pAllegro, ALLEGRO_BITMAP* selected, ALLEGRO_BITMAP* image = NULL);

	position GetPos(void);

private:
	bool selected;
	string name;
	path orgPath;
	ALLEGRO_BITMAP* image;
	position pos;
};

list<Tile>* generateTileList(list<path>& pathList);
list<Tile>* generateTileList(list<path>& pathList, const char* defaultImg);