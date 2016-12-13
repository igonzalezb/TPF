
//////////////////////////////////// RPI_SETUP ////////////////////////////////////

// ADEMAS TENER EN CUENTA QUE SI SE COMPILA DESDE VENTANA DE COMANDO:

// gcc ....c -o ... -lwiringPi

#include "rpi_setup.h"
#include "simon.h"
#include "rpi_input.h"
#include "main.h"
//TODO ESTO ES GLOBAL, EN EL ARCHIVO HARWARE.C  HICE UN EXTERN DE pinsT leds y pinsT buttons

//pthread_t tid_simon, tid_input;

//CIRCULAR_BUFFER buffer_buttons; //creo aca


pinsT leds[] = {{"RED",7,OUTPUT,LOW}, //VERRRR los "OFF" //ver LED_RED ( nombres) si quedan en enum o no
                {"GREEN",1,OUTPUT,LOW},
                {"BLUE",5,OUTPUT,LOW},
                {"YELLOW",2,OUTPUT,LOW}};
        
pinsT buttons[] = {{"RED",0,INPUT,LOW},
                   {"GREEN",4,INPUT,LOW},
                   {"BLUE",6,INPUT,LOW},
                   {"YELLOW",3,INPUT,LOW}};

////////////////////// configuration_start //////////////////////

int configuration_start () //poner que devuelva indicacion de exito o error.
{
        wiringPiSetup();
        
        pin_out_or_in ();
    
        set_pin_zero_or_one ();
        // printf("wDigital RED: %d\n", digitalRead(buttons[RED].pin ));
        // printf("wDigital blue: %d\n", digitalRead(buttons[BLUE].pin ));
        // printf("wDigital green: %d\n", digitalRead(buttons[GREEN].pin ));
        // printf("wDigital yellow: %d\n", digitalRead(buttons[YELLOW].pin ));
        // // create_buffer(&buffer_buttons, TAMANO_BUFFER);
    
        // pthread_create (&tid_simon ,NULL ,thread_simon ,NULL);
    
        // pthread_create (&tid_input ,NULL ,thread_input ,NULL);
        simon_main ();
            
        return 0;
}


////////////////////// configuration_end //////////////////////
// ver si devolver indicacion de error o no

void configuration_end () //ver como lograr acceder a la estructura leds y buttons. haciendo que el prototipo de la funcion sirva para las dos plataformas.
{
        //end_buffer(&buffer_buttons);
        //pthread_join(tid_input,NULL); //poner que devuelva indicacion de exito o error. identificar si hubo error
        //ptread_join(tid_simon,NULL);
    
        //return 0;
}


////////////////////// pin_out_or_in //////////////////////

void pin_out_or_in()
{
    int i;
    for (i=0;i<=CANT_COLORS;i++)
    {
            pinMode (leds[i].pin, leds[i].direction);
            pinMode (buttons[i].pin, buttons[i].direction);
    }
}


////////////////////// set_pin_zero_or_one //////////////////////

void set_pin_zero_or_one()
{
    int i;
    for (i=0;i<=CANT_COLORS;i++)
    {
            digitalWrite (leds[i].pin, leds[i].value);
            //digitalWrite (buttons[i].pin, buttons[i].value);
    }
}

