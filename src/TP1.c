/*=============================================================================
 * Author1: Gonzalo Nahuel Vaca <vacagonzalo@gmail.com>
 * Author2: Ismael Minchala Avila <ismael.minchala@gmail.com>
 * Date: 2021/07/02
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP1.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

enum sentido{ascendente, descendente};
bool_t  encenderLed(gpioMap_t led);
bool_t  apagarLeds(gpioMap_t *leds, int8_t len);
bool_t  leerTecla (gpioMap_t tecla);
bool_t  verificarTiempo(tick_t tiempo);
void activarSecuencia(gpioMap_t *psecuencia, int8_t len, enum sentido dir);
const tick_t RAPIDO = 150;
const tick_t LENTO = 750;
const tick_t BASE_TIEMPO = 10;

int main( void )
{
	gpioMap_t leds[] = {LEDB, LED1, LED2, LED3};
	int8_t lenLeds = sizeof(leds)/sizeof(gpioMap_t);
	enum sentido dir = ascendente;
	tick_t tiempo = RAPIDO;
	bool_t finTiempo = true;

   // ----- Setup -----------------------------------
   boardInit();

   // ----- Repeat for ever -------------------------
   while( true ) {
	   if (leerTecla(TEC1)){
		   dir = descendente;
	   }
	   if (leerTecla(TEC4)){
		   dir = ascendente;
	   }
	   if (leerTecla(TEC2)){
		   tiempo = RAPIDO;
	   }
	   if (leerTecla(TEC3)){
		   tiempo = LENTO;
	   }
	   if (finTiempo){
		   activarSecuencia(leds, lenLeds, dir);
		   finTiempo = false;
	   }
	   finTiempo = verificarTiempo(tiempo);
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
void activarSecuencia(gpioMap_t *psecuencia, int8_t len, enum sentido dir){
	static int8_t pos = 0;
	int8_t ultimo = len - 1;
	apagarLeds(psecuencia, len);
	encenderLed(psecuencia[pos]);
	if (dir == ascendente){
		if (pos < ultimo){
			++pos;
		} else {
			pos = 0;
		}
	} else{
		if (pos > 0){
			--pos;
		} else{
			pos = ultimo;
		}
	}
}

bool_t verificarTiempo(tick_t tiempo){
	static tick_t contador = 0;
	tick_t numBase = tiempo / BASE_TIEMPO;
	delay(BASE_TIEMPO);
	if (contador > numBase){
		contador = 0;
		return true;
	} else{
		contador += BASE_TIEMPO;
		return false;
	}
}
