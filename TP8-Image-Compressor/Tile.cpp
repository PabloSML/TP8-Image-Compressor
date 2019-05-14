#include "Tile.h"

Tile::Tile(string name, path orgPath ,string imagePath, position pos)
{
	selected = false;
	this->name = name;
	this->orgPath = orgPath;
	this->pos = pos;
	image = al_load_bitmap(imagePath.c_str());
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

void Tile::draw(Allegro* pAllegro, ALLEGRO_BITMAP* selected, ALLEGRO_BITMAP* image)
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
	if (this->isSelected())
	{
		pAllegro->drawImage(selected, (x - 10)*scale_x, (y - 10)*scale_y, 320 * scale_x, 270 * scale_y);
	}
	pAllegro->printText(name.c_str(), x*scale_x, (y + 250 + 10)*scale_y, align::left);

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
		path tempPath(pathItr->string());
		string tempImgPath = pathItr->string();
		position tempPos;
		tempPos.posx = i % 3;
		tempPos.posz = i / 9;
		tempPos.posy = (i / 3) - 3 * tempPos.posz;

		Tile tempTile(tempName, tempPath,tempImgPath, tempPos);

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
		path tempPath(pathItr->string());
		position tempPos;
		tempPos.posx = i % 3;
		tempPos.posz = i / 9;
		tempPos.posy = (i / 3) - 3 * tempPos.posz;

		Tile tempTile(tempName, tempPath, string(defaultImg), tempPos);

		tempTileList->push_back(tempTile);
	}
	return tempTileList;
}