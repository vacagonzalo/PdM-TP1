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
typedef struct {
    const gpioMap_t * ptrLed;
    const int8_t tamano;
    enum sentido direccion;
} controlSecuencia_t;
bool_t  encenderLed(gpioMap_t led);
bool_t  apagarLeds(controlSecuencia_t *controlador);
bool_t  leerTecla (gpioMap_t tecla);
bool_t  verificarTiempo(tick_t tiempo);
void activarSecuencia(controlSecuencia_t *controlador);
const tick_t RAPIDO = 150;
const tick_t LENTO = 750;
const tick_t BASE_TIEMPO = 10;


int main( void )
{
	const gpioMap_t leds[] = {LEDB, LED1, LED2, LED3};
	const int8_t lenLeds = sizeof(leds)/sizeof(gpioMap_t);
	tick_t tiempo = RAPIDO;
	bool_t finTiempo = true;
	controlSecuencia_t controlLeds = {leds, lenLeds, ascendente};

   // ----- Setup -----------------------------------
   boardInit();

   // ----- Repeat for ever -------------------------
   while( true ) {
	   if (leerTecla(TEC1)){
		   controlLeds.direccion = descendente;
	   }
	   if (leerTecla(TEC4)){
		   controlLeds.direccion = ascendente;
	   }
	   if (leerTecla(TEC2)){
		   tiempo = RAPIDO;
	   }
	   if (leerTecla(TEC3)){
		   tiempo = LENTO;
	   }
	   if (finTiempo){
		   activarSecuencia(&controlLeds);
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

bool_t  apagarLeds(controlSecuencia_t *controlador){
	bool_t state = true;
	for (int i = 0; i < controlador->tamano; ++i){
		if (!gpioWrite(controlador->ptrLed[i], OFF)){
			state = false;
		}
	}
	return state;
}

bool_t leerTecla (gpioMap_t tecla){
	bool_t state = gpioRead(tecla);
	return !state;
}

/* Esta funcion enciende el siguiente led de la secuencia*/
void activarSecuencia(controlSecuencia_t *controlador){
	static int8_t pos = 0;
	int8_t ultimo = controlador->tamano - 1;
	if(!apagarLeds(controlador)) {
		printf("Error: no se apagaron todos los LEDs\n\r");
	}
	if(!encenderLed(controlador->ptrLed[pos])) {
		printf("Error: el miembro %d de la secuencia no se pudo encender\n\r", pos);
	}
	if (controlador->direccion == ascendente){
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
