/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ARB = 0xA33, ABA = 0x883  } direccion;

void game_lanzar(unsigned int jugador);

void game_soy(unsigned int soy);

void game_donde(unsigned int* pos);

void game_mover_cursor(int jugador, direccion dir);


typedef struct str_pos
{
	unsigned char x;
	unsigned char y;
} posicion;

typedef struct str_jugador
{
	posicion pos;
	unsigned int vida;
	unsigned int puntos;
	unsigned int tareasRestantes;
} jugador;



extern jugador jR;
extern jugador jA;

#endif  /* !__GAME_H__ */
