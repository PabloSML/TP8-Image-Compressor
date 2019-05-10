#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
using namespace std;

struct position {
	int posx;
	int posy;
};

class Tile
{
public:
	Tile() {
		selected = false;
		name = string("");
		image = nullptr;
		pos.posx = pos.posy = NULL;
	}

	Tile(string name, ALLEGRO_BITMAP* image, position pos);

	void select(void);
	void unSelect(void);
	bool isSelected(void);

	string getName(void);

	void draw(void);

private:
	bool selected;
	string name;
	ALLEGRO_BITMAP* image;
	position pos;
};