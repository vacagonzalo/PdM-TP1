/*=============================================================================
 * Author: Gonzalo Nahuel Vaca <vacagonzalo@gmail.com>
 * Date: 2021/06/30
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP1.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

bool_t  encenderLed(gpioMap_t led);
bool_t  apagarLeds(gpioMap_t *leds, int8_t len);
bool_t leerTecla (gpioMap_t tecla);
void activarSecuencia(gpioMap_t *psecuencia, int8_t len);

int main( void )
{
	gpioMap_t leds[] = {LEDB, LED1, LED2, LED3};
	int8_t lenLeds = sizeof(leds)/sizeof(gpioMap_t);
   // ----- Setup -----------------------------------
   boardInit();

   // ----- Repeat for ever -------------------------
   while( true ) {
      activarSecuencia(leds, lenLeds);
      delay(500);
      apagarLeds(leds, lenLeds);
      delay(500);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}

bool_t  encenderLed(gpioMap_t led){
	gpioWrite(led, ON);
	return gpioRead(led);
}

bool_t  apagarLeds(gpioMap_t *leds, int8_t len){
	bool_t state = TRUE;
	for (int i = 0; i < len; ++i){
		if (!gpioWrite(leds[i], OFF)){
			state = FALSE;
		}
	}
	return state;
}

bool_t leerTecla (gpioMap_t tecla){
	bool_t state = gpioRead(tecla);
	return !state;
}

/* Esta funcion enciende el siguiente led de la secuencia*/
void activarSecuencia(gpioMap_t *psecuencia, int8_t len){
	static int8_t pos = 0;
	int8_t ultimo = len - 1;
	encenderLed(psecuencia[pos]);
	if (pos < ultimo){
		++pos;
	} else {
		pos = 0;
	}
}
