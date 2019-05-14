#include "Tile.h"

Tile::Tile(string name, const char* imagePath, position pos)
{
	selected = false;
	this->name = name;
	originalPath = imagePath;
	this->pos = pos;
	image = al_load_bitmap(imagePath);
	if (!image)
		cout << "Failed to load drawable bitmap!" << endl;
}

void Tile::select(void)
{
	selected = true;
}

void Tile::unSelect(void)
{
	selected = false;
}

bool Tile::isSelected(void)
{
	return selected;
}

string Tile::getName(void)
{
	return name;
}

const char* Tile::getOgPath(void)
{
	return originalPath;
}

void Tile::draw(Allegro* pAllegro, ALLEGRO_BITMAP* image = NULL)
{
	int scale_x = pAllegro->GetDisplayW() / DISPLAY_W;
	int scale_y = pAllegro->GetDisplayH() / DISPLAY_H;
	int x;
	int y;
	switch (pos.posx)
	{
	case 0:
		x = 150;
		break;
	case 1:
		x = 500;
		break;
	case 2:
		x = 850;
		break;
	default:
		std::cout << "Error: x>2" << std::endl;
	}
	switch (pos.posy)
	{
	case 0:
		y = 350;
		break;
	case 1:
		y = 700;
		break;
	case 2:
		y = 1050;
		break;
	default:
		std::cout << "Error: y>2" << std::endl;
	}
	if (image != NULL)
	{
		pAllegro->drawImage(image, x*scale_x, y*scale_y, 300 * scale_x, 250 * scale_y);
	}
	else
	{
		pAllegro->drawImage(this->image, x*scale_x, y*scale_y, 300 * scale_x, 250 * scale_y);

	}

}

position Tile::GetPos(void)
{
	return pos;
}


//************************************************************ FUNCIONES AUXILIARES ******************
list<Tile>* generateTileList(list<path>& pathList)	// para tiles de .png
{
	list<Tile>* tempTileList = new list<Tile>;
	list<path>::iterator pathItr = pathList.begin();

	for (int i = 0; i < pathList.size(); i++, pathItr++)
	{
		string tempName = pathItr->filename().string();
		const char* tempImgPath = pathItr->string().c_str();
		position tempPos;
		tempPos.posx = i % 3;
		tempPos.posz = i / 9;
		tempPos.posy = (i / 3) - 3 * tempPos.posz;

		Tile tempTile(tempName, tempImgPath, tempPos);

		tempTileList->push_back(tempTile);
	}
	return tempTileList;
}

list<Tile>* generateTileList(list<path>& pathList, const char* defaultImg) // para tiles de .eda
{
	list<Tile>* tempTileList = new list<Tile>;
	list<path>::iterator pathItr = pathList.begin();

	for (int i = 0; i < pathList.size(); i++, pathItr++)
	{
		string tempName = pathItr->filename().string();
		position tempPos;
		tempPos.posx = i % 3;
		tempPos.posz = i / 9;
		tempPos.posy = (i / 3) - 3 * tempPos.posz;

		Tile tempTile(tempName, defaultImg, tempPos);

		tempTileList->push_back(tempTile);
	}
	return tempTileList;
}