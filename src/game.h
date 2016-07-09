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
	posicion posMapa;			//Posicion estatica de las tareas.
	posicion pos;				//Posicion dinamica de las tareas.
	tipoTarea type;				//"Dueño de la tarea"
	tipoTarea viruseada;		//Infectada por....
	unsigned short gdtEntry;	//Indice de la TSS ligada a la tarea
	unsigned char vivo; 		//Para decir si esta viva o no
	unsigned int cr3;			//Direccion del Page Directory asociado a la tarea
	unsigned int estadoReloj;	//Clock de la tarea
	unsigned int posEnArreglo;
} tarea;

typedef struct str_jugador {
	posicion pos; 					//Posición actual de cursor
	unsigned int vida; 				//Vidas restantes	
	unsigned int puntos;			//Puntaje actual
	unsigned short tareaActual;		//Tarea actual corriendo.
	unsigned short cantidadVivas;	
 	tarea task[5];
} jugador;

typedef struct str_system {
	tarea* taskActual; 				//Tarea que está siendo actualmente ejecutada. Una forma de acceder a la siguiente tarea
	jugador jugadores[2];			//[jugadorA,jugadorB]
	unsigned int jugadorActual;		// 0 == H; 1 == A; 2 == B
	unsigned int itH;				// iterador al arreglo de tareas H. 
	tarea Htask[15];
	unsigned short idle;

	unsigned short debugMode;
} system;

extern system MainSystem;

extern unsigned char debugFlag;

void game_lanzar(unsigned int jugador);

void game_soy(unsigned int soy);

void game_donde(short* pos);

void game_mover_cursor(int jugador, direccion dir);

void game_init();

tarea tareaNueva(unsigned int* codigo, tipoTarea tipo, posicion pos, unsigned int posEnArreglo);

void debugMode(int gs, int fs, int es, int ds, int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int errorCode, int eip, int cs, int eflags, int espTss, int ss);

void matarTarea();

unsigned int contarInfectados(tipoTarea j);

unsigned int newrand(unsigned int *val);

void sumarPuntos();

// unsigned int noHayNadaMapeadoAca(posicion posAux, tipoTarea j);

#endif  /* !__GAME_H__ */









// tipoTarea siguienteTarea(tipoTarea actual) {
// 	switch (actual) {
// 		case A:
// 			//if (MainSystem.jugadores[1].cantidadVivas > 0) return B;
// 			//else return H;
// 			return B;
// 		case B:
// 			return H;
// 		case H:
// 			//if (MainSystem.jugadores[0].cantidadVivas > 0) return A;
// 			//else return B;
// 		return A;
// 	}
// 	return 0;
// }



// unsigned char tieneVivos(tipoTarea type){
// 	unsigned char tiene = 0;
// 	int i = 0;
// 	int k;
// 	if(type != H){
// 		if(type == A) k = 0;
// 		else k = 1;
// 		int actual = (MainSystem.jugadores[k].tareaActual + 1) % 5;		

// 		while( tiene == 0 || i < 5){
// 			tiene = MainSystem.jugadores[k].task[(actual + i) % 5].vivo; 
// 			i++;
// 		}
// 	} else {
// 		int actual = (MainSystem.itH + 1) % 15;

// 		while( tiene == 0 || i < 15){
// 			tiene = MainSystem.Htask[(actual + i) % 15].vivo; 
// 			i++;
// 		}
// 	}

// 	return tiene;

// }

 
// unsigned short sched_proximo_indice() {
// 	#define TAREAS_JUG_SIGUIENTE MainSystem.jugadores[k]
	
// 	tipoTarea typeSiguiente = siguienteTarea(MainSystem.taskActual->type);


// 	if(tieneVivos(typeSiguiente)){
// 		if (typeSiguiente != H){
// 			int i;
// 			int k;
// 			if (typeSiguiente == A) k = 0; //[jugadorA, jugadorB]
// 			else k = 1;

// 			i = (TAREAS_JUG_SIGUIENTE.tareaActual + 1) % 5;

// 			while (!TAREAS_JUG_SIGUIENTE.task[i].vivo){
// 					i = (i + 1) % 5;
// 			}

// 			relojJug(k, i);
// 			MainSystem.jugadorActual = typeSiguiente;
// 			TAREAS_JUG_SIGUIENTE.tareaActual = i;
// 			MainSystem.taskActual = &(TAREAS_JUG_SIGUIENTE.task[i]);
// 			return MainSystem.taskActual->gdtEntry;
// 		}

// 		int j;
// 		j = (MainSystem.itH + 1) % 15;
	
// 		// if (MainSystem.itH < 14) j = MainSystem.itH + 1;
// 		// else j = 0;

// 		while (!MainSystem.Htask[j].vivo) {
// 			j = (j + 1) % 15;
// 			//if (j > 14) j = 0;
// 		}
			

// 		MainSystem.jugadorActual = H;
// 		relojH(j);
// 		MainSystem.itH = j;
// 		MainSystem.taskActual = &(MainSystem.Htask[j]);
// 		return MainSystem.taskActual->gdtEntry;
// 	}

// 	tipoTarea typeSigSig = siguienteTarea(MainSystem.taskActual->type);

// 	if(tieneVivos(typeSigSig)){
// 		if (typeSigSig != H){
// 			int i;
// 			int k;
// 			if (typeSigSig == A) k = 0; //[jugadorA, jugadorB]
// 			else k = 1;

// 			i = (TAREAS_JUG_SIGUIENTE.tareaActual + 1) % 5;

// 			while (!TAREAS_JUG_SIGUIENTE.task[i].vivo){
// 					i = (i + 1) % 5;
// 			}

// 			relojJug(k, i);
// 			MainSystem.jugadorActual = typeSigSig;
// 			TAREAS_JUG_SIGUIENTE.tareaActual = i;
// 			MainSystem.taskActual = &(TAREAS_JUG_SIGUIENTE.task[i]);
// 			return MainSystem.taskActual->gdtEntry;
// 		}

// 		int j;
// 		j = (MainSystem.itH + 1) % 15;

// 		while (!MainSystem.Htask[j].vivo) {
// 			j = (j + 1) % 15;
// 		}
			
// 		MainSystem.jugadorActual = H;
// 		relojH(j);
// 		MainSystem.itH = j;
// 		MainSystem.taskActual = &(MainSystem.Htask[j]);
// 		return MainSystem.taskActual->gdtEntry;
// 	}

// 	tipoTarea actual = MainSystem.taskActual->type;

// 	if(tieneVivos(actual)){
// 		if (actual != H){
// 			int i;
// 			int k;
// 			if (actual == A) k = 0; //[jugadorA, jugadorB]
// 			else k = 1;

// 			i = (TAREAS_JUG_SIGUIENTE.tareaActual + 1) % 5;

// 			while (!TAREAS_JUG_SIGUIENTE.task[i].vivo){
// 					i = (i + 1) % 5;
// 			}

// 			relojJug(k, i);
// 			MainSystem.jugadorActual = actual;
// 			TAREAS_JUG_SIGUIENTE.tareaActual = i;
// 			MainSystem.taskActual = &(TAREAS_JUG_SIGUIENTE.task[i]);
// 			return MainSystem.taskActual->gdtEntry;
// 		}

// 		int j;
// 		j = (MainSystem.itH + 1) % 15;

// 		while (!MainSystem.Htask[j].vivo) {
// 			j = (j + 1) % 15;
// 		}
			
// 		MainSystem.jugadorActual = H;
// 		relojH(j);
// 		MainSystem.itH = j;
// 		MainSystem.taskActual = &(MainSystem.Htask[j]);
// 		return MainSystem.taskActual->gdtEntry;
// 	}

// 		return 0x50;
// }