/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "game.h"

tipoTarea siguienteTarea(tipoTarea actual) {
	switch (actual) {
		case A:
			return B;
		case B:
			return H;
		case H:
			return A;
	}
	return 0;
}

unsigned short sched_proximo_indice() {
	#define TAREAS_JUG_SIGUIENTE MainSystem.jugadores[typeSiguiente]

	tipoTarea typeSiguiente = siguienteTarea(MainSystem.taskActual->type);

	if (typeSiguiente != H) {
		int i;
		for (i = TAREAS_JUG_SIGUIENTE.tareaActual + 1; i < TAREAS_JUG_SIGUIENTE.tareaActual && !TAREAS_JUG_SIGUIENTE.task[i].vivo; i++){
			if (i == 5) i = 0;
		}
		if (i != TAREAS_JUG_SIGUIENTE.tareaActual) {
			TAREAS_JUG_SIGUIENTE.tareaActual = i;
			MainSystem.taskActual = &(TAREAS_JUG_SIGUIENTE.task[i]);
			return MainSystem.taskActual->gdtEntry;
		}
	}
	breakpoint();
	int i;
	for (i = MainSystem.itH + 1; i < MainSystem.itH && !MainSystem.Htask[i].vivo; i++) {
		if (i == 15) i = 0;
	}

	if (i != MainSystem.itH) {
		MainSystem.itH = i;
		MainSystem.taskActual = &(MainSystem.Htask[i]);
		return MainSystem.taskActual->gdtEntry;	
	}
	return 0;
}
