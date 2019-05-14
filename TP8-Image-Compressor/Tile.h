#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <boost/filesystem.hpp>
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
		originalPath = nullptr;
		image = nullptr;
		pos.posx = pos.posy = pos.posz = NULL;
	}

	Tile(string name, const char* imagePath, position pos);

	void select(void);
	void unSelect(void);
	bool isSelected(void);

	string getName(void);
	const char* getOgPath(void);

	void draw(void);

private:
	bool selected;
	string name;
	const char* originalPath;
	ALLEGRO_BITMAP* image;
	position pos;
};

list<Tile>* generateTileList(list<path>& pathList);
list<Tile>* generateTileList(list<path>& pathList, const char* defaultImg);