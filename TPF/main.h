#define _ALLEGRO_PC_

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



enum platform { RASPBERRYPI, ALLEGRO };
enum colores { RED, GREEN, BLUE, YELLOW };

#define ON      1
#define OFF     0


#define MAX_LEVEL 100

#define ERROR -1

enum leds { LED_RED, LED_GREEN, LED_BLUE, LED_YELLOW, LED_ON_OFF};

enum buttons { BUTTON_RED, BUTTON_GREEN, BUTTON_BLUE, BUTTON_YELLOW, BUTTON_UP };


#endif // MAIN_H

#ifdef _RASPBERRY_PI_
#include <stdbool.h>
#include <unistd.h>
#include "rpi_setup.h"
#include "rpi_output.h"
#include "rpi_input.h"
#define BASE_TIME 500000
#define MIN_TIME 10000
#define WAIT_T	usleep
#endif


#ifdef _ALLEGRO_PC_	
#include "allegro_display.h"
#include "allegro_teclado.h"
#include "allegro_menu_inicio.h"
#include "allegro_setup.h"
#define BASE_TIME 0.5
#define MIN_TIME 0.01
#define WAIT_T al_rest
#endif

