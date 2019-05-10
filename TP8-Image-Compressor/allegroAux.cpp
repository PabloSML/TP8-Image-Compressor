#include "allegroAux.h"

bool
initAll(ALLEGRO_DISPLAY*& display, ALLEGRO_TIMER*& timer,ALLEGRO_EVENT_QUEUE*& event_queue,\
	    ALLEGRO_SAMPLE*& sickBeats)
{
	// Instalamos Allegro
	if (!al_init())
	{
		cout << "Failed to initialize Allegro" << endl;
		return FAILURE;
	}
	//TIMER
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		cout << "Failed to create timer!" << endl;
		return FAILURE;
	}
	//EVENT QUEUE
	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		cout << "Failed to create event_queue!" << endl;
		al_destroy_timer(timer);
		return FAILURE;
	}
	//KEYBOARD
	if (!al_install_keyboard())
	{
		cout << "Failed to initialize the keyboard" << endl;
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return FAILURE;
	}
	//IMAGE ADDON
	if (!al_init_image_addon())
	{
		cout << "Failed to initialize the image addon" << endl;
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_uninstall_keyboard();
		return FAILURE;
	}
	// AUDIO SUBSYSTEM
	if (!al_install_audio())
	{
		cout << "Failed to initialize the audio subsystem" << endl;
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		return FAILURE;
	}
	// AUDIO CODECS
	if (!al_init_acodec_addon())
	{
		cout << "Failed to initialize the audio codecs" << endl;
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		al_uninstall_audio();
		return FAILURE;
	}
	// RESERVE SAMPLES
	if (!al_reserve_samples(1))
	{
		cout << "Failed to initialize the audio codecs" << endl;
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		al_uninstall_audio();
		return FAILURE;
	}
	// Inicializo el display
	display = al_create_display(W_DIS, H_DIS);
	if (display == NULL)
	{
		cout << "Failed to create display!" << endl;
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		al_uninstall_audio();
		return FAILURE;
	}
	al_set_window_title(display, "Worms Armageddon 5: The Armageddoning");
	//Cargo el soundtrack
	sickBeats = al_load_sample(OST_FILE);
	if (!sickBeats)
	{
		cout << "Audio clip sample not loaded!" << endl;
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		al_uninstall_keyboard();
		al_shutdown_image_addon();
		al_uninstall_audio();
		return FAILURE;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));	//Registro al display como generador de eventos
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	//Registro al timer como generador de eventos
	al_register_event_source(event_queue, al_get_keyboard_event_source());	//Registro al teclado como generador de eventos

	al_play_sample(sickBeats, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);	//Comienza la cancion

	return SUCCESS;
}


void
deinitAll(ALLEGRO_DISPLAY*& display, ALLEGRO_TIMER*& timer, ALLEGRO_EVENT_QUEUE*& event_queue,\
		  ALLEGRO_SAMPLE*& sickBeats)
{
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_sample(sickBeats);
	al_uninstall_keyboard();
	al_shutdown_image_addon();
	al_uninstall_audio();
	timer = NULL;
	display = NULL;
	event_queue = NULL;
	sickBeats = NULL;
}