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
			if (noHayNadaMapeadoAca(posAux, A)) JUGADOR.task[i] = tareaNueva((unsigned int*) 0x11000, A, posAux);
			//tarea* tsk = &JUGADOR.task[i];
			//matarTarea(tsk);
		} else {
			posicion posAux = (posicion) {JUGADOR.pos.x - 1, JUGADOR.pos.y};
			if (noHayNadaMapeadoAca(posAux, B)) JUGADOR.task[i] = tareaNueva((unsigned int*) 0x12000, B, posAux);
		}
		JUGADOR.cantidadVivas++;
	}
}

unsigned int noHayNadaMapeadoAca(posicion pos, tipoTarea t) {
	int i;
	int j;
	switch (t) {
		case A:
			j = 5;
			for (i = 0; i < j && (MainSystem.jugadores[0].task[i].pos.x != pos.x || MainSystem.jugadores[0].task[i].pos.y != pos.y || !MainSystem.jugadores[0].task[i].vivo); i++)
			{};
			break;
		case B:
			j = 5;
			for (i = 0; i < j && (MainSystem.jugadores[1].task[i].pos.x != pos.x || MainSystem.jugadores[1].task[i].pos.y != pos.y || !MainSystem.jugadores[1].task[i].vivo); i++)
			{};
			break;
		case H:
			j = 15;
			for (i = 0; i < j && (MainSystem.Htask[i].pos.x != pos.x || MainSystem.Htask[i].pos.y != pos.y || !MainSystem.Htask[i].vivo); i++)
			{};
			break;
	}
	return (i == j);
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
	pos[1] = MainSystem.taskActual->pos.x + 1;
	pos[0] = MainSystem.taskActual->pos.y;
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
	tNueva.vivo = 1;
	tNueva.gdtEntry = gdtEntry;
	tNueva.cr3 = cr3;
	tNueva.estadoReloj = 0;
	return tNueva;
}

void debugMode() {
	if (MainSystem.debugMode) imprimirError();
}

void matarTarea() {
	if(MainSystem.taskActual->type != H){
		int j;
		if (MainSystem.taskActual->type == A) j = 0;
		else j = 1;
		jugador player = MainSystem.jugadores[j];    	//A o B
		MainSystem.taskActual->vivo = 0;
		gdt[MainSystem.taskActual->gdtEntry].p = 0;
		if(player.vida != 0) {
			player.vida--;
		}
		player.cantidadVivas--;
	}
	MainSystem.jugadores[MainSystem.taskActual->viruseada].puntos--;
}