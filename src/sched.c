/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "game.h"
#include "screen.h"

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
	#define TAREAS_JUG_SIGUIENTE MainSystem.jugadores[k]
	
	tipoTarea typeSiguiente = siguienteTarea(MainSystem.taskActual->type);
	if (typeSiguiente != H) {
		int i;
		int k;
		if (typeSiguiente == A) k = 0;
		else k = 1;

		if (TAREAS_JUG_SIGUIENTE.tareaActual < 4) i = TAREAS_JUG_SIGUIENTE.tareaActual + 1;
		else i = 0;

		while (i != TAREAS_JUG_SIGUIENTE.tareaActual && !TAREAS_JUG_SIGUIENTE.task[i].vivo){
			i++;
			if (i > 4) i = 0;
		}
		
		if (i != TAREAS_JUG_SIGUIENTE.tareaActual || TAREAS_JUG_SIGUIENTE.task[i].vivo) {
			relojJug(k, i);
			TAREAS_JUG_SIGUIENTE.tareaActual = i;
			MainSystem.taskActual = &(TAREAS_JUG_SIGUIENTE.task[i]);
			//breakpoint();
			return MainSystem.taskActual->gdtEntry;
		}
	}
	
	int j;
	if (MainSystem.itH < 14) j = MainSystem.itH + 1;
	else j = 0;

	while (j != MainSystem.itH && !MainSystem.Htask[j].vivo) {
		j++;
		if (j > 14) j = 0;
	}
	if (j != MainSystem.itH || MainSystem.Htask[j].vivo) {
		relojH(j);
		MainSystem.itH = j;
		MainSystem.taskActual = &(MainSystem.Htask[j]);
		// breakpoint();
		return MainSystem.taskActual->gdtEntry;
	}
	return 0;
}

//動作するように準備をします