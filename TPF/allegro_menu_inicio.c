//#include "allegro_display.h"
#include "main.h"
//#include "allegro_teclado.h"
#include "simon.h"
extern ALLEGRO_DISPLAY * display;
extern bool exit_simon;
extern bool player_lost;
#define PLAY_BUTTON_X	(al_get_display_width(display) / 2)
#define PLAY_BUTTON_Y	((al_get_display_height(display) / 4) * 3)

#define INFO_BUTTON_X	(al_get_display_width(display) / 10)
#define INFO_BUTTON_Y	((al_get_display_height(display) / 16) * 15)

extern ALLEGRO_EVENT_QUEUE *event_queue;

int allegro_menu_inicio()
{
	ALLEGRO_BITMAP *menu_simon = NULL;

	ALLEGRO_BITMAP *menu_simon_play = NULL;

	ALLEGRO_SAMPLE *sample_menu = NULL;

	ALLEGRO_FONT * font_menu = NULL;
	
	bool do_exit1 = false;

	bool play = false;

	bool redraw1 = false;

	//=======FALTA CADA DESTROY ANTES DE ERROR==============================================================================================================================================================
	menu_simon = al_load_bitmap("resources/menu_simon.png");
	if (!menu_simon) {
		fprintf(stderr, "Failed to create menu_simon!\n");
		return ERROR;
	}

	menu_simon_play = al_load_bitmap("resources/menu_simon_play.png");
	if (!menu_simon_play) {
		fprintf(stderr, "Failed to create menu_simon_play!\n");
		return ERROR;
	}

	

	font_menu = al_load_ttf_font("resources/phreak.ttf", 54, 0);

	if (!font_menu) {
		fprintf(stderr, "Could not load 'atari.ttf'.\n");
		return ERROR;
	}


	sample_menu = al_load_sample("resources/sounds/menu_inicio.wav");

	if (!sample_menu) {
		printf("Audio clip sample not loaded!\n");
		return -1;
	}



	//=======================================================================================================================================================================	
	
	allegro_draw_bitmap_scaled(menu_simon);
	al_draw_text(font_menu, al_color_name("white"), PLAY_BUTTON_X, PLAY_BUTTON_Y, ALLEGRO_ALIGN_CENTER, ": : PLAY : :");
	//al_draw_text(font2, al_color_name("white"), INFO_BUTTON_X, INFO_BUTTON_Y, ALLEGRO_ALIGN_CENTER, "INFO");
	
	al_flip_display();
	printf("CP2\n");
	al_play_sample(sample_menu, 1.0, 0.0,1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	int x1, x2, y1, y2, w, h;
	int mx, my;
	
	//al_start_timer(timer1);

	while (!do_exit1)
	{
		ALLEGRO_EVENT ev1;

		al_wait_for_event(event_queue, &ev1);
		
		//printf("CP3\n");

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			//QUIT
			do_exit1 = true;
		else if (ev1.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
		{
			if (!al_acknowledge_resize(ev1.display.source))
			{
				fprintf(stderr, "Failed to create event_queue!\n");
				//DESTROY
				return ERROR;
			}
			redraw1 = true;
		}

		else if (ev1.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			al_get_text_dimensions(font_menu, ": : PLAY : :", &x1, &y1, &w, &h);
			printf("x1: %X", x1);
			x1 = PLAY_BUTTON_X - w / 2;
			y1 = y1 + PLAY_BUTTON_Y;
			x2 = w + x1;
			y2 = h + y1;
			
			mx = ev1.mouse.x;
			my = ev1.mouse.y;
			printf("mx %X, my %X\n", mx, my);
			
			if (((x1 <= mx) && (mx <= x2))  && ((my >= y1) && (my <= y2)))
			{
				allegro_draw_bitmap_scaled(menu_simon_play);
				al_draw_text(font_menu, al_color_name("green"), PLAY_BUTTON_X, PLAY_BUTTON_Y, ALLEGRO_ALIGN_CENTER, ": : PLAY : :");
				al_flip_display();
			}
			
		}
		//PODRIA AGREGAR QUE CUANDO PASE POR ARRRIBA DEL BOTON CAMBIE DE COLOR
		else if (ev1.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (((mx >= x1) && (mx <= x2)) && ((my >= y1) && (my <= y2)))
			{
				redraw1 = true;
				play = true;
			}
			

		}


		else if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev1.keyboard.keycode == ALLEGRO_KEY_SPACE)
			{
				allegro_draw_bitmap_scaled(menu_simon_play);
				al_draw_text(font_menu, al_color_name("green"), PLAY_BUTTON_X, PLAY_BUTTON_Y, ALLEGRO_ALIGN_CENTER, ": : PLAY : :");
				al_flip_display();
				printf("SPACE\n");
				
			}
		}

		else if (ev1.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev1.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				redraw1 = true;
				play = true;
				break;


			case ALLEGRO_KEY_ESCAPE:
				//QUIT
				do_exit1 = true;
				break;
			}
		}

		

		if (play && al_is_event_queue_empty(event_queue))
		{
			al_stop_samples();
		//==========================ESTO SE PUDE SACAR=======================================
			al_clear_to_color(al_color_name("black"));
			al_draw_text(font_menu, al_color_name("white"), (CENTER_W), (CENTER_H), ALLEGRO_ALIGN_CENTER, "LOADING...");
			al_flip_display();
			al_rest(1.5);
		//====================================================================================
			//VOY AL JUEG0
			//if (allegro_teclado_main())
			//{
			//	fprintf(stderr, "Failed allegro_teclado_main!\n");
			//	//DISTROY
			//	return ERROR;
			//}
			
			if(simon_main())
				return ERROR;

			al_flush_event_queue(event_queue);
			exit_simon = false;
			player_lost = false;
			//VUELVO AL MENU PRINCIPAL
			al_play_sample(sample_menu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
			play = false;
			redraw1 = true;
			al_flush_event_queue(event_queue);
			printf("CP5\n");
		}

		if (redraw1 && al_is_event_queue_empty(event_queue))
		{
			al_clear_to_color(al_color_name("black"));
			allegro_draw_bitmap_scaled(menu_simon);
			al_draw_text(font_menu, al_color_name("white"), PLAY_BUTTON_X, PLAY_BUTTON_Y, ALLEGRO_ALIGN_CENTER, ": : PLAY : :");
			//al_draw_text(font2, al_color_name("white"), INFO_BUTTON_X, INFO_BUTTON_Y, ALLEGRO_ALIGN_CENTER, "INFO");

			al_flip_display();
			redraw1 = false;
			play = false;
			printf("CP4\n");


		}
		

	}

	//DISTROY de esta funcion
	//
	return 0;
}


void allegro_draw_button_center(ALLEGRO_BITMAP * bitmap)
{
	//al_draw_bitmap(bitmap, (al_get_display_width(display) - al_get_bitmap_width(bitmap)) / 2, (al_get_display_height(display) - al_get_bitmap_height(bitmap)) / 2, 0);

	al_draw_scaled_bitmap(bitmap,
		0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), //TAMA�O DE IMAGEN
		PLAY_BUTTON_X, PLAY_BUTTON_Y, al_get_display_width(display)/4, al_get_display_height(display)/6, // TE LO DIBUJA DEL TAMA�O DEL DISPLAY ACTUAL
		0);
}

