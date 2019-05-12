#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#define MAX_DISPLAY_H	2160
#define MAX_DISPLAY_W	3840
#define TEXTFONT "textfont.ttf"
#define TEXTSIZE 50

enum event {ev_null, ev_quit, ev_tile1, ev_tile2, ev_tile3, ev_tile4,ev_tile5, ev_tile6, ev_tile7, ev_tile8, ev_tile9,ev_enter,ev_mode_comp, ev_mode_decomp};

class Allegro
{
public:
	//constructores
	Allegro(unsigned int w=(MAX_DISPLAY_W*0.5),unsigned int h=(MAX_DISPLAY_H*0.5));
	~Allegro();
	bool initAllegro_ok();

	//metodos especiales
	void setDisplayColor(unsigned char r, unsigned char g, unsigned char b);
	void updateDisplay(void);
	enum event getNextEvent(void);

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_FONT* font;
	bool init_ok;
	unsigned int display_h;
	unsigned int display_w;
};