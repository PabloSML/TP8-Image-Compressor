#include "Pages.h"


Pages::Pages(list<Tile>* ptile, enum page_mode mode, Allegro* pallegro)
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
	font = al_load_ttf_font(TEXTFONT, PAGETEXTSIZE, 0);
	//ALLEGRO_BITMAP* done;
	arrow[0] = al_load_bitmap(IMG_LEFT);
	arrow[1] = al_load_bitmap(IMG_RIGHT);
	select[0] = al_load_bitmap(IMG_S_ALL);
	select[1] = al_load_bitmap(IMG_UN_ALL);
	selected = al_load_bitmap(IMG_SELECTED);
	back2menu = al_load_bitmap(IMG_MENU);
	done = al_load_bitmap(IMG_DONE);
	edafile = al_load_bitmap(IMG_EDA_FILE);
}

Pages::~Pages()
{

}

/*return true if success, false if quit*/
enum pages_result Pages::SelectImages()
{
	enum pages_result return_;
	pagenum = 0;
	UpdatePage();
	bool done = false;
	al_event ev;

	while (!done)
	{
		ev = pAllegro->getNextEvent();
		if (ev >= ev_tile1 && ev <= ev_tile9)
		{
			selectTile((int)(ev - ev_tile1));
			UpdatePage();
		}
		else
		{
			switch (ev)
			{
			case ev_quit:
				return_ = r_quit;
				done = true;
				break;
			case ev_menu:
				return_ = r_menu;
				done = true;
				break;
			case ev_all:
				std::cout << "all" << std::endl;
				SelectAll();
				UpdatePage();
				break;
			case ev_none:
				DeselectAll();
				UpdatePage();
				break;
			case ev_right:
				NextPage();
				UpdatePage();
				break;
			case ev_left:
				PrevPage();
				UpdatePage();
				break;
			case ev_enter:
				return_ = r_sucess;
				done = true;
				break;
			case ev_mouse:
				enum pages_result r = mouse_handler(pAllegro->GetMousePos());
				if (r != r_null)
				{
					return_ = r;
					done = true;
				}
				break;
			}
		}
	}
	return return_;
}

void Pages::selectTile(int pos_)
{
	if (pos_ >= 9)
	{
		std::cout << "Error: pos>=9" << std::endl;
		return;
	}
	int z = pagenum;
	int x = 0;
	int y = 0;
	for (int counter = pos_; counter > 0; counter--)
	{
		if (x > 2)
		{
			x = 0;
			y++;
		}
		else
		{
			x++;
		}
	}
	std::list<Tile>::iterator it;
	for (it = pTile->begin(); it != pTile->end(); ++it)
	{
		position pos = it->GetPos();
		if ((pos.posz == z) && (pos.posx == x) && (pos.posy == y))
		{
			if (it->isSelected())
				it->unSelect();
			else
				it->select();
		}
	}
}


enum pages_result Pages::mouse_handler(display_pos pos)
{
	int scale_x = pAllegro->GetDisplayW() / DISPLAY_W;
	int scale_y = pAllegro->GetDisplayH() / DISPLAY_H;

	if ((pos.y>=50*scale_y)&&(pos.y<=150*scale_y))
	{
		if ((pos.x >= 150 * scale_x) && (pos.x <= 350 * scale_x))
			return r_menu;
		else if ((pos.x >= 550 * scale_x) && (pos.x <= 750 * scale_x))
		{
			SelectAll();
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 950 * scale_x) && (pos.x <= 1150 * scale_x))
		{
			DeselectAll();
			UpdatePage();
			return r_null;
		}
		else
			return r_null;
		
	}
	else if ((pos.y >= 350 * scale_y) && (pos.y <= 600 * scale_y))
	{
		if ((pos.x >= 150 * scale_x) && (pos.x <= 450 * scale_x))
		{
			selectTile(0);
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 500 * scale_x) && (pos.x <= 800 * scale_x))
		{
			selectTile(1);
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 850 * scale_x) && (pos.x <= 1150 * scale_x))
		{
			selectTile(2);
			UpdatePage();
			return r_null;
		}
		else
			return r_null;
	}
	else if ((pos.y >= 700 * scale_y) && (pos.y <= 950 * scale_y))
	{
		if ((pos.x >= 150 * scale_x) && (pos.x <= 450 * scale_x))
		{
			selectTile(3);
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 500 * scale_x) && (pos.x <= 800 * scale_x))
		{
			selectTile(4);
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 850 * scale_x) && (pos.x <= 1150 * scale_x))
		{
			selectTile(5);
			UpdatePage();
			return r_null;
		}
		else
			return r_null;
	}
	else if ((pos.y >= 1050 * scale_y) && (pos.y <= 1300 * scale_y))
	{
		if ((pos.x >= 150 * scale_x) && (pos.x <= 450 * scale_x))
		{
			selectTile(6);
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 500 * scale_x) && (pos.x <= 800 * scale_x))
		{
			selectTile(7);
			UpdatePage();
			return r_null;
		}
		else if ((pos.x >= 850 * scale_x) && (pos.x <= 1150 * scale_x))
		{
			selectTile(8);
			UpdatePage();
			return r_null;
		}
		else
			return r_null;
	}
	else if ((pos.y >= 1450 * scale_y) && (pos.y <= 1550 * scale_y))
	{
		if ((pos.x >= 150 * scale_x) && (pos.x <= 350 * scale_x))
		{
			PrevPage();
			UpdatePage();
			return r_null;

		}
		else if ((pos.x >= 550 * scale_x) && (pos.x <= 750 * scale_x))
		{
			return r_sucess;
		}
		else if ((pos.x >= 950 * scale_x) && (pos.x <= 1150 * scale_x))
		{
			NextPage();
			UpdatePage();
			return r_null;
		}
		else
			return r_null;
	}
	else
	return r_null;
}


void Pages::UpdatePage()
{
	pAllegro->setDisplayColor(0, 0, 0);
	int scale_x = pAllegro->GetDisplayW() / DISPLAY_W;
	int scale_y = pAllegro->GetDisplayH() / DISPLAY_H;
	pAllegro->drawImage(back2menu, 150 * scale_x, 50 * scale_y, 200 * scale_x, 100 * scale_y);
	pAllegro->drawImage(select[0], 550 * scale_x, 50 * scale_y, 200 * scale_x, 100 * scale_y);
	pAllegro->drawImage(select[1], 950 * scale_x, 50 * scale_y, 200 * scale_x, 100 * scale_y);
	if(pagenum!=0)
		pAllegro->drawImage(arrow[0], 150 * scale_x, 1450 * scale_y, 200 * scale_x, 100 * scale_y);
	pAllegro->drawImage(done, 550 * scale_x, 1450 * scale_y, 200 * scale_x, 100 * scale_y);
	if(pagenum!=totalpages)
		pAllegro->drawImage(arrow[1], 950 * scale_x, 1450 * scale_y, 200 * scale_x, 100 * scale_y);

	if (mode == p_comp)
	{
		pAllegro->printText("Select image to compress:", 650 * scale_x, 250 * scale_y, center, font);
		std::list<Tile>::iterator it;
		for (it = pTile->begin(); it != pTile->end(); ++it)
		{
			position pos = it->GetPos();
			if (pos.posz == pagenum)
			{
				it->draw(pAllegro,selected);
				
					
			}
		}
	}
	else if(mode == p_decomp)
	{
		pAllegro->printText("Select image to decompress:", 650 * scale_x, 250 * scale_y, center, font);
		std::list<Tile>::iterator it;
		for (it = pTile->begin(); it != pTile->end(); ++it)
		{
			position pos = it->GetPos();
			if (pos.posz == pagenum)
				it->draw(pAllegro, selected, edafile);
		}
	}
	pAllegro->updateDisplay();

}

void Pages::NextPage()
{
	if (pagenum < totalpages)
		pagenum ++;
	UpdatePage();
}

void Pages::PrevPage()
{
	if (pagenum > 0)
		pagenum--;
	UpdatePage();

}

void Pages::SelectAll()
{
	std::list<Tile>::iterator it;

	for (it = pTile->begin(); it != pTile->end(); ++it)
	{
		position pos = it->GetPos();
		if (pos.posz == pagenum)
			it->select();
	}
}

void Pages::DeselectAll()
{
	std::list<Tile>::iterator it;

	for (it = pTile->begin(); it != pTile->end(); ++it)
	{
		position pos = it->GetPos();
		if (pos.posz == pagenum)
			it->unSelect();
	}
}
