#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

#include "Allegro.h"


Allegro::Allegro(unsigned int w,unsigned int h)
{
	display_w = w;
	display_h = h;
	if (!al_init()) { //Primera funcion a llamar antes de empezar a usar allegro.
		fprintf(stderr, "failed to initialize allegro!\n");
		init_ok = false;
		return;
	}

	if (!al_install_mouse()) {//initialize mouse.
		fprintf(stderr, "failed to initialize the mouse!\n");
		init_ok = false;
		return;
	}

	if (!al_install_keyboard()) {//initialize keyboard.
		fprintf(stderr, "failed to initialize the keyboard!\n");
		init_ok = false;
		return;
	}

	event_queue = al_create_event_queue();//create event queue.
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		init_ok = false;
		return;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0); //HAY CREAR UN FONT PARA CADA TAMA�O DE LETRA :( 
	if (!font) {
		fprintf(stderr, "Could not load text font.\n");
		al_destroy_event_queue(event_queue);
		return;
	}

	display = al_create_display(w, h); // Intenta crear display de fallar devuelve NULL

	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_event_queue(event_queue);
		init_ok = false;
		return;
	}
	al_init_image_addon();

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)

	//Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola a medida que vayan sucediendo
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO
	al_register_event_source(event_queue, al_get_mouse_event_source()); //REGISTRAMOS EL MOUSE
	init_ok = true;
	return;
}

Allegro::~Allegro()
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}

bool Allegro::initAllegro_ok()
{
	return init_ok;
}

void Allegro::setDisplayColor(unsigned char r, unsigned char g, unsigned char b)
{
	al_clear_to_color(al_map_rgb(r, g, b));
}

void Allegro::updateDisplay(void)
{
	al_flip_display();
}

//falta validar a posicion del mouse
enum al_event Allegro::getNextEvent(void)
{
	ALLEGRO_EVENT ev;
	al_get_next_event(event_queue, &ev);
	switch (ev.type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		return ev_quit;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_1: case ALLEGRO_KEY_PAD_1:
			return ev_tile1;
			break;
		case ALLEGRO_KEY_2: case ALLEGRO_KEY_PAD_2:
			return ev_tile2;
			break;
		case ALLEGRO_KEY_3: case ALLEGRO_KEY_PAD_3:
			return ev_tile3;
			break;
		case ALLEGRO_KEY_4: case ALLEGRO_KEY_PAD_4:
			return ev_tile4;
			break;
		case ALLEGRO_KEY_5: case ALLEGRO_KEY_PAD_5:
			return ev_tile5;
			break;
		case ALLEGRO_KEY_6: case ALLEGRO_KEY_PAD_6:
			return ev_tile6;
			break;
		case ALLEGRO_KEY_7: case ALLEGRO_KEY_PAD_7:
			return ev_tile7;
			break;
		case ALLEGRO_KEY_8: case ALLEGRO_KEY_PAD_8:
			return ev_tile8;
			break;
		case ALLEGRO_KEY_9: case ALLEGRO_KEY_PAD_9:
			return ev_tile9;
			break;
		case ALLEGRO_KEY_A:
			return ev_all;
			break;
		case ALLEGRO_KEY_N:
			return ev_none;
			break;
		case ALLEGRO_KEY_M:
			return ev_menu;
			break;
		case ALLEGRO_KEY_Q:
			return ev_quit;
			break;
		case ALLEGRO_KEY_ENTER:
			return ev_enter;
			break;
		case ALLEGRO_KEY_RIGHT:
			return ev_right;
			break;
		case ALLEGRO_KEY_LEFT:
			return ev_left;
			break;
		}
		return ev_null;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		pos.x = ev.mouse.x;
		pos.y = ev.mouse.y;
		return ev_mouse;
		break;
	}
	return ev_null;
}

void Allegro::printText(const char* text, int x, int y, enum align al, ALLEGRO_FONT *al_font)
{
	int flag;
	switch (al)
	{
	case center: flag = ALLEGRO_ALIGN_CENTER; break;
	case right: flag = ALLEGRO_ALIGN_RIGHT; break;
	case left: flag = ALLEGRO_ALIGN_LEFT; break;
	default:std::cout << "ERROR: not valid flag in printText." << std::endl;
	}
	if (!al_font)
		al_font = font;
	al_draw_text(al_font, al_map_rgb(255, 0, 0), x, y, flag, text);
}

unsigned int Allegro::GetDisplayW()
{
	return display_w;
}

unsigned int Allegro::GetDisplayH()
{
	return display_h;
}

void Allegro::drawImage(ALLEGRO_BITMAP* image, int x, int y, int width = 0, int height = 0)
{
	if ((width <= 0) || (height <= 0))
	{
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, al_get_bitmap_width(image), al_get_bitmap_height(image), 0);
	}
	else
	{
		al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, width, height, 0);
	}
}

display_pos Allegro::GetMousePos()
{
	return pos;
}
