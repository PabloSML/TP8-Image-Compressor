#ifndef ALLEGROAUX_H
#define ALLEGROAUX_H

//*************************************************INCLUDES*************************************************
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>

using namespace std;

//*************************************************DEFINES*************************************************
#define SUCCESS 1
#define FAILURE 0
#define FPS 50.0	//valor para que se realizen timer events cada 20ms
#define W_DIS 1366	//Si se cambia la resolucion se debe modificar POS_X_RATIO_AJUST y POS_Y_RATIO_AJUST en Worm.h
#define H_DIS 768	// y POS_Y_RATIO_AJUST en Worm.h, siguiendo los valores de la tabla******
//******* TABLA RESOLUCION/POS_X_RATIO_AJUST - POS_Y_RATIO_AJUST *******
/*
Resolucion  |  POS_X_RATIO_AJUST  |  POS_Y_RATIO_AJUST
1920x1080	|		 1			  |		1.5660919
1920x696	|		 1			  |			1
1366x768	|	  0.7114583		  |		1.1034483
1024x720	|	  0.5333334		  |		1.0344827
800x600		|	  0.4166667		  |		0.8620690
*/
#define OST_FILE "coda.wav"	//pista de audio

//*************************************************FUNCIONES*************************************************
// funciones de inicializacion y destruccion de allegro
bool initAll(ALLEGRO_DISPLAY*& display, ALLEGRO_TIMER*& timer,\
			 ALLEGRO_EVENT_QUEUE*& event_queue, ALLEGRO_SAMPLE*& sickBeats);
void deinitAll(ALLEGRO_DISPLAY*& display, ALLEGRO_TIMER*& timer, \
			   ALLEGRO_EVENT_QUEUE*& event_queue, ALLEGRO_SAMPLE*& sickBeats);

#endif