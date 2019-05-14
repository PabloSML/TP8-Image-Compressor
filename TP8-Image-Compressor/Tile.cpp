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

void Tile::draw(void)
{

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