PdM - Práctica clase 1
======================
Universidad de Buenos Aires
---
Falcultad de Ingeniería
---
Especialización en sistemas embebidos
---

Luis Ismael Minchala Avila (ismael.minchala@ucuenca.edu.ec)

Gonzalo Nahuel Vaca (vacagonzalo@gmail.com)

# Objetivos

## Resumen

Prender secuencialmente los leds de la placa LED1, LED2, LED3 y LEDA.

## Condiciones de funcionamiento

* Una vez que se pasa al siguiente led los demás deberán apagarse.
* Utilizar solamente el LED azul del grupo de leds RGB.
* Controlar el sentido de la secuencia con los botones TEC1 y TEC4.
* Al presionar TEC2 cada led queda encendido 150 ms.
* Al presionar TEC3 cada led queda encendido 750 ms.

## Condiciones adicionales

### Utilizar funciones que encapsulen el código y hagan el programa más legible, como por ejemplo:

```c
bool_t  encenderLed(gpioMap_t led); /* encender un led en particular */

bool_t  apagarLeds(); /* apagar todos los leds */

bool_t leerTecla (gpioMap_t tecla); /* leer el estado de una tecla.  Devuelve por valor el estado de la tecla pulsada (verdadero) o liberada (falso)*/

void activarSecuencia(gpioMap_t * psecuencia); /* psecuencia apunta a una secuencia de leds o arreglo de gpioMap_t */
```
Las funciones deben devolver verdadero o falso en función de si pudieron realizar su tarea correctamente o no o si la tecla está presionada o no, según corresponda.

### Incorporar conceptos de programación defensiva al código:

Limitar la visibilidad de la información al mínimo:
 
* Uso de variables locales en lugar de globales, preferentemente.
* Uso de modificador static donde corresponda.

Verificar los valores de retorno de las funciones.

Verificar los parámetros/argumentos antes de utilizarlos.

### [OPCIONAL] Utilizar arreglos para hacer la implementación reutilizable y escalable, por ejemplo:

```c
bool_t flagsControl[] = {FALSE, FALSE, FALSE, FALSE};

const gpioMap_t secuencia[] = {LEDB, LED1, LED2, LED3};

const uint8_t ultimoLed = sizeof(secuencia)/sizeof(gpioMap_t);
```
### [OPCIONAL] Utilizar estructuras y punteros para hacer la implementación más genérica y definir dos secuencias de leds distintas y que puedan funcionar en simultáneo, una con el led RGB y otra con los leds LED1, LED2 y LED3.

```c
typedef struct {
    const gpioMAP_t * ptrLed;
    const gpioMap_t const* ptrPrimerLed;
    const unit8_t const* ptrUltimoLed;
} controlSecuencia_t;
```

# Requisitos

* EDU-CIAA
* Cable USB