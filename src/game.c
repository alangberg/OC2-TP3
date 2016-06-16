/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"
#include "mmu.h"

#define POS_IGUALES(a, b) a.x == b.x && a.y == b.y

system MainSystem;
unsigned char debugFlag;

void game_mover_cursor(int jugador, direccion dir) {
	if (jugador == 1)
	{
		if (POS_IGUALES(MainSystem.jugadores[0].pos, MainSystem.jugadores[1].pos)) print("*", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (1 << 4) | (15 & 0x0F));
		else print(" ", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (MainSystem.jugadores[0].pos.y > 1) MainSystem.jugadores[0].pos.y -= 1;
				break;
			case ABA:
				if (MainSystem.jugadores[0].pos.y < 44) MainSystem.jugadores[0].pos.y += 1;
				break;
			case DER:
				 if (MainSystem.jugadores[0].pos.x < 79) MainSystem.jugadores[0].pos.x += 1;
				break;
			case IZQ:
				 if (MainSystem.jugadores[0].pos.x > 0) MainSystem.jugadores[0].pos.x -= 1;
				break;
		}
		print("*", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (4 << 4) | (15 & 0x0F));
	} else {
		if (POS_IGUALES(MainSystem.jugadores[0].pos, MainSystem.jugadores[1].pos)) print("*", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (4 << 4) | (15 & 0x0F));
		else print(" ", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (MainSystem.jugadores[1].pos.y > 1) MainSystem.jugadores[1].pos.y -= 1;
				break;
			case ABA:
				if (MainSystem.jugadores[1].pos.y < 44) MainSystem.jugadores[1].pos.y += 1;
				break;
			case DER:
				 if (MainSystem.jugadores[1].pos.x < 79) MainSystem.jugadores[1].pos.x += 1;
				break;
			case IZQ:
				 if (MainSystem.jugadores[1].pos.x > 0) MainSystem.jugadores[1].pos.x -= 1;
				break;
		}
		print("*", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (1 << 4) | (15 & 0x0F));
	}
}

void game_lanzar(unsigned int jugador) {
	#define JUGADOR MainSystem.jugadores[jugador]
	if (JUGADOR.cantidadVivas < 5) {
		int i;
		for (i = 0; i < 5 && JUGADOR.task[i].vivo; i++)
		{}
		if (jugador == 0) {
			posicion posAux = (posicion) {JUGADOR.pos.x + 1, JUGADOR.pos.y};
			if (noHayNadaMapeadoAca(posAux, A)) {
				JUGADOR.task[i] = tareaNueva((unsigned int*) 0x11000, A, posAux, i);
				JUGADOR.cantidadVivas++;
			}
		} else {
			posicion posAux = (posicion) {JUGADOR.pos.x - 1, JUGADOR.pos.y};
			if (noHayNadaMapeadoAca(posAux, B)) {
				JUGADOR.task[i] = tareaNueva((unsigned int*) 0x12000, B, posAux, i);
				JUGADOR.cantidadVivas++;
			}
		}
	}
	imprimirDataJugadores();
}

unsigned int noHayNadaMapeadoAca(posicion posAux, tipoTarea j) {
	int k;
	if (j == A) k = 0;
	else k = 1;

	int i;
	for(i = 0; i < 5 && MainSystem.jugadores[k].task[i].pos.x != posAux.x && MainSystem.jugadores[k].task[i].pos.y != posAux.y; i++) {
	}

	return (i == 5);
}

void sumarPuntos(){
	MainSystem.jugadores[0].puntos = contarInfectados(A);
	MainSystem.jugadores[1].puntos = contarInfectados(B);
}

unsigned int contarInfectados(tipoTarea jug) {
	int i;
	unsigned int res = 0;
	for (i = 0; i < 15; i++) {
		if (MainSystem.Htask[i].viruseada == jug) res++; //sumo las tareas H infectadas por jug
	}
	int k;
		for (k = 0; k < 5; k++) {
			if(jug == A){
				res = res + (MainSystem.jugadores[1].task[k].viruseada == jug);
			} else {
				res = res + (MainSystem.jugadores[0].task[k].viruseada == jug);
			}
		}
	return res;
}

void game_soy(unsigned int yoSoy) {
	if (yoSoy == 0x841){ //A
		MainSystem.taskActual->viruseada = A;
	}
	if (yoSoy == 0x325) { //B
		MainSystem.taskActual->viruseada = B;
	}
}

void game_donde(unsigned int* pos) {
	pos[0] = MainSystem.taskActual->pos.x;
	pos[1] = MainSystem.taskActual->pos.y;
}

void game_mapear(int y, int x) {
	posicion posAux;
	posAux.x = x;
	posAux.y = y;
	
	unsigned int  fisicaPosicion = game_dame_fisica_de_posicion(posAux);
	mmu_mapear_pagina(PAGINA_MAPEADA, MainSystem.taskActual->cr3, fisicaPosicion, 1);

	print(" ", MainSystem.taskActual->pos.x, MainSystem.taskActual->pos.y, (7 << 4));
	MainSystem.taskActual->pos = posAux;
}

void game_init() {

	debugFlag = 0;

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
		MainSystem.jugadores[0].task[i].estadoReloj = 0;
		MainSystem.jugadores[1].task[i].estadoReloj = 0;
	}

	MainSystem.jugadorActual = A;
	MainSystem.itH = 0;

	for (i = 0; i < 15; i++) {
		unsigned int val;
	 	posicion p = {((newrand(&val) % 79) + 1), ((newrand(&val) % 43) + 1)};
	 	MainSystem.Htask[i] = tareaNueva((unsigned int*) 0x13000, H, p, i);
	}
}

unsigned int newrand(unsigned int *val) {
	#define RAND_a 11037981245
	#define RAND_c 13378
	#define RAND_m 2147483648LL

    unsigned int rr = RAND_a * ((unsigned int)*val) + RAND_c;
    *val = (unsigned int) ( rr % RAND_m);
    return *val;
}

tarea tareaNueva(unsigned int* codigo, tipoTarea tipo, posicion pos, unsigned int posEnArreglo) {
	//breakpoint();
	tarea tNueva;
	unsigned short gdtEntry;
	unsigned int cr3;
	tss_nueva_tarea(codigo, pos, &gdtEntry, &cr3);
	tNueva.pos = pos;
	tNueva.type = tipo;
	tNueva.viruseada = tipo;
	tNueva.vivo = 1;
	tNueva.gdtEntry = gdtEntry;
	tNueva.cr3 = cr3;
	tNueva.estadoReloj = 0;
	tNueva.posEnArreglo = posEnArreglo;
	return tNueva;
}

void debugMode() {
	if (MainSystem.debugMode) {
		imprimirError(0);
		debugFlag = 1;
	}
}

void matarTarea() {
	int j;

	if(MainSystem.taskActual->type != H){
		
		if (MainSystem.taskActual->type == A) j = 0;
		else j = 1;
		
		MainSystem.taskActual->vivo = 0;
		gdt[MainSystem.taskActual->gdtEntry].p = 0;
		
		if(MainSystem.jugadores[j].vida != 0) {
			MainSystem.jugadores[j].vida--;
		}

		relojJug(MainSystem.taskActual->type, MainSystem.taskActual->posEnArreglo);

		MainSystem.jugadores[j].cantidadVivas--;
	}
	if (MainSystem.taskActual->viruseada == A) j = 0;
	else j = 1;
	
	if (MainSystem.jugadores[j].puntos > 0) MainSystem.jugadores[j].puntos--;
	print(" ", MainSystem.taskActual->pos.x, MainSystem.taskActual->pos.y, (7 << 4));
}