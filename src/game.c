/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "mmu.h"

#define POS_IGUALES(a, b) a.x == b.x && a.y == b.y

system MainSystem;

void game_mover_cursor(int jugador, direccion dir) {
	if (jugador == 1)
	{
		if (POS_IGUALES(MainSystem.jugadores[0].pos, MainSystem.jugadores[1].pos)) print("*", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (1 << 4) | (15 & 0x0F));
		else print(" ", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (MainSystem.jugadores[0].pos.y > 1) MainSystem.jugadores[0].pos.y -= 1;
				else MainSystem.jugadores[0].pos.y = 44;
				break;
			case ABA:
				if (MainSystem.jugadores[0].pos.y < 44) MainSystem.jugadores[0].pos.y += 1;
				else MainSystem.jugadores[0].pos.y = 1;
				break;
			case DER:
				 if (MainSystem.jugadores[0].pos.x < 79) MainSystem.jugadores[0].pos.x += 1;
				 else MainSystem.jugadores[0].pos.x = 0;
				break;
			case IZQ:
				 if (MainSystem.jugadores[0].pos.x > 0) MainSystem.jugadores[0].pos.x -= 1;
				 else MainSystem.jugadores[0].pos.x = 79;
				break;
		}
		print("*", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (4 << 4) | (15 & 0x0F));
	} else {
		if (POS_IGUALES(MainSystem.jugadores[0].pos, MainSystem.jugadores[1].pos)) print("*", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (4 << 4) | (15 & 0x0F));
		else print(" ", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (MainSystem.jugadores[1].pos.y > 1) MainSystem.jugadores[1].pos.y -= 1;
				else MainSystem.jugadores[1].pos.y = 44;
				break;
			case ABA:
				if (MainSystem.jugadores[1].pos.y < 44) MainSystem.jugadores[1].pos.y += 1;
				else MainSystem.jugadores[1].pos.y = 1;
				break;
			case DER:
				 if (MainSystem.jugadores[1].pos.x < 79) MainSystem.jugadores[1].pos.x += 1;
				 else MainSystem.jugadores[1].pos.x = 0;
				break;
			case IZQ:
				 if (MainSystem.jugadores[1].pos.x > 0) MainSystem.jugadores[1].pos.x -= 1;
				 else MainSystem.jugadores[1].pos.x = 79;
				break;
		}
		print("*", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (1 << 4) | (15 & 0x0F));
	}
}

void game_lanzar(unsigned int jugador) {
	//void tss_nueva_tarea(unsigned int* code, posicion pos, unsigned short* gdtEntry, unsigned int* cr3) {
	// posicion pos;
	// unsigned int* code;
	// unsigned short* gdtE;
	// unsigned int* cr3;
	// if (jugador == 1) {
	// 	pos = MainSystem.jugadores[0].pos;
	// 	code = (unsigned int*) 0x11000;
	// } else {
	// 	pos = MainSystem.jugadores[1].pos;
	// 	code = (unsigned int*) 0x12000;
	// }

	// tss_nueva_tarea(code, pos, gdtE, cr3);
}


	// if(j == A){
	// 	codigo = (unsigned int*)CODIGO_TAREA_B;
	// }else{
	// 	codigo = (unsigned int*)CODIGO_TAREA_A;
	// }

	// int i = 0;
	// while(i < CANT_TAREAS_J && GAME.js[j].tareas[i].vivo){
	// 	i++;
	// }
	
	// if(i != CANT_TAREAS_J){
	// 	GAME.js[j].tareas[i] = nueva_tarea(codigo,x,y,j);
	// 	GAME.js[j].vidas --;
	// }



// #define CODIGO_TAREA_B			0x11000
// #define CODIGO_TAREA_H			0x13000
// typedef struct str_tarea {
// 	// Posición de cada tarea dentro del mapa, separada entre jugadores y sanas
// 	posicion pos;
// 	tipoTarea type;
// 	tipoTarea viruseada;
// 	unsigned short gdtEntry;
// 	unsigned char vivo; //Para decir si esta viva o no
// 	unsigned int cr3;	// Posición de cada pagina mapeada por tarea dentro del mapa

// } tarea;

// typedef struct str_jugador {
// 	posicion pos; // Posición actual de cursor એન્ડી અશ્લીલ
// 	unsigned int vida; 
// 	unsigned int puntos;
// 	unsigned short tareaActual;  
//  tarea task[5];
// } jugador;

// typedef struct str_system {
// 	tarea* taskActual; // Tarea que está siendo actualmente ejecutada // Una forma de acceder a la siguiente tarea
// 	jugador jugadores[2];		//[jugadorA,jugadorB] એન્ડી અશ્લીલ
// 	unsigned int jugadorActual;
// 	unsigned int itH;
// 	tarea Htask[15];

// 	unsigned short debugMode;
// } system;








void game_soy(unsigned int yoSoy) {
	if (yoSoy == 0x325){ //Jugador A. A
		MainSystem.taskActual->viruseada = A;
	}
	if (yoSoy == 0x841) { //B
		MainSystem.taskActual->viruseada = B;
	}
}

void game_donde(unsigned int* pos) {
	pos[0] = MainSystem.taskActual->pos.x;
	pos[1] = MainSystem.taskActual->pos.y - 1 ;
}

void game_mapear(int x, int y) {
	posicion posAux;
	posAux.x = x;
	posAux.y = y;
	unsigned int  fisicaPosicion = game_dame_fisica_de_posicion(posAux);
	mmu_mapear_pagina(PAGINA_MAPEADA, MainSystem.taskActual->cr3, fisicaPosicion);
}

void game_init() {
	jugador jA;
	jA.pos.x = 20;
	jA.pos.y = 20;
	jA.vida = 20;
	jA.puntos = 0;
	jA.tareaActual = 0;

	jugador jB;
	jB.pos.x = 50;
	jB.pos.y = 20;
	jB.vida = 20;
	jB.puntos = 0;
	jB.tareaActual = 0;

	MainSystem.jugadores[0] = jA;
	MainSystem.jugadores[1] = jB;
	int i;
	for (i = 0; i < 5; i++) {
		MainSystem.jugadores[0].task[i].vivo = 0;
		MainSystem.jugadores[1].task[i].vivo = 0;
	}

	MainSystem.jugadorActual = A;
	MainSystem.itH = 0;

	for (i = 0; i < 15; i++) {
	 	posicion p = {i + 1, i + 1};
	 	MainSystem.Htask[i] = tareaNueva((unsigned int*) 0x13000, H, p );
	}
}

tarea tareaNueva(unsigned int* codigo, tipoTarea tipo, posicion pos) {
	tarea tNueva;
	unsigned short gdtEntry;
	unsigned int cr3;
	tss_nueva_tarea(codigo, pos, &gdtEntry, &cr3);
	tNueva.pos = pos;
	tNueva.type = tipo;
	tNueva.viruseada = tipo;
	tNueva.gdtEntry = gdtEntry;
	tNueva.vivo = 1;
	tNueva.cr3 = cr3;

	return tNueva;
}

void debugMode() {
	if (MainSystem.debugMode) imprimirError();
}



