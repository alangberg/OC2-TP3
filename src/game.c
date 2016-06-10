/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

#define POS_IGUALES(a, b) a.x == b.x && a.y == b.y

jugador jR;
jugador jA;

void game_mover_cursor(int jugador, direccion dir) {
	if (jugador == 1)
	{
		if (POS_IGUALES(jR.pos, jA.pos)) print("*", jR.pos.x, jR.pos.y, (1 << 4) | (15 & 0x0F));
		else print(" ", jR.pos.x, jR.pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (jR.pos.y > 1) jR.pos.y -= 1;
				else jR.pos.y = 44;
				break;
			case ABA:
				if (jR.pos.y < 44) jR.pos.y += 1;
				else jR.pos.y = 1;
				break;
			case DER:
				 if (jR.pos.x < 79) jR.pos.x += 1;
				 else jR.pos.x = 0;
				break;
			case IZQ:
				 if (jR.pos.x > 0) jR.pos.x -= 1;
				 else jR.pos.x = 79;
				break;
		}
		print("*", jR.pos.x, jR.pos.y, (4 << 4) | (15 & 0x0F));
	} else {
		if (POS_IGUALES(jR.pos, jA.pos)) print("*", jA.pos.x, jA.pos.y, (4 << 4) | (15 & 0x0F));
		else print(" ", jA.pos.x, jA.pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (jA.pos.y > 1) jA.pos.y -= 1;
				else jA.pos.y = 44;
				break;
			case ABA:
				if (jA.pos.y < 44) jA.pos.y += 1;
				else jA.pos.y = 1;
				break;
			case DER:
				 if (jA.pos.x < 79) jA.pos.x += 1;
				 else jA.pos.x = 0;
				break;
			case IZQ:
				 if (jA.pos.x > 0) jA.pos.x -= 1;
				 else jA.pos.x = 79;
				break;
		}
		print("*", jA.pos.x, jA.pos.y, (1 << 4) | (15 & 0x0F));
	}
}

void game_lanzar(unsigned int jugador) {
}

void game_soy(unsigned int yoSoy) {
}

void game_donde(unsigned int* pos) {
}

void game_mapear(int x, int y) {
}