#include "Pages.h"


Pages::Pages(list<Tile>* ptile, int mode, Allegro* pallegro)
{
	pTile = ptile;
	pagenum = 0;
	this->mode = mode;
	pAllegro = pallegro;
	totalpages = 0;
	std::list<Tile>::iterator it;
	for (it = pTile->begin(); it != pTile->end(); ++it) 
	{
		position pos = it->GetPos();
		if (pos.posz>totalpages)
			totalpages = pos.posz;
	}

}

Pages::~Pages()
{

}

void Pages::SelectImages()
{

}

void Pages::UpdatePage()
{
	pAllegro->setDisplayColor(0, 0, 0);
	int scale_x = pAllegro->GetDisplayW() / DISPLAY_W;
	int scale_y = pAllegro->GetDisplayH() / DISPLAY_H;


}

void Pages::NextPage()
{

}

void Pages::PrevPage()
{

}

int Pages::GetPageNum()
{

}
