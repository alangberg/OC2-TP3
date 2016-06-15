/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"
#include "tss.h"

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ARB = 0xA33, ABA = 0x883  } direccion;

typedef struct str_tarea {
	// Posición de cada tarea dentro del mapa, separada entre jugadores y sanas
	posicion pos;
	tipoTarea type;
	tipoTarea viruseada;
	unsigned short gdtEntry;
	unsigned char vivo; 		//Para decir si esta viva o no
	unsigned int cr3;			// Posición de cada pagina mapeada por tarea dentro del mapa
	unsigned int estadoReloj;

} tarea;

typedef struct str_jugador {
	posicion pos; 				// Posición actual de cursor એન્ડી અશ્લીલ
	unsigned int vida; 
	unsigned int puntos;
	unsigned short tareaActual;
	unsigned short cantidadVivas;
 	tarea task[5];
} jugador;

typedef struct str_system {
	tarea* taskActual; 			// Tarea que está siendo actualmente ejecutada // Una forma de acceder a la siguiente tarea
	jugador jugadores[2];		//[jugadorA,jugadorB]
	unsigned int jugadorActual;
	unsigned int itH;
	tarea Htask[15];

	unsigned short debugMode;
} system;

extern system MainSystem;

void game_lanzar(unsigned int jugador);

void game_soy(unsigned int soy);

void game_donde(unsigned int* pos);

void game_mover_cursor(int jugador, direccion dir);

void game_init();

tarea tareaNueva(unsigned int* codigo, tipoTarea tipo, posicion pos);

void debugMode();


#endif  /* !__GAME_H__ */
