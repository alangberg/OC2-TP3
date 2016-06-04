/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

#define POS_IGUALES(a, b) a.x == b.x && a.y == b.y

pos p1_pos;
pos p2_pos;

void game_mover_cursor(int jugador, direccion dir) {
	if (jugador == 1)
	{
		if (POS_IGUALES(p1_pos, p2_pos)) print("*", p1_pos.x, p1_pos.y, (1 << 4) | (15 & 0x0F));
		else print(" ", p1_pos.x, p1_pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (p1_pos.y > 1) p1_pos.y -= 1;
				else p1_pos.y = 44;
				break;
			case ABA:
				if (p1_pos.y < 44) p1_pos.y += 1;
				else p1_pos.y = 1;
				break;
			case DER:
				 if (p1_pos.x < 79) p1_pos.x += 1;
				 else p1_pos.x = 0;
				break;
			case IZQ:
				 if (p1_pos.x > 0) p1_pos.x -= 1;
				 else p1_pos.x = 79;
				break;
		}
		print("*", p1_pos.x, p1_pos.y, (4 << 4) | (15 & 0x0F));
	} else {
		if (POS_IGUALES(p1_pos, p2_pos)) print("*", p2_pos.x, p2_pos.y, (4 << 4) | (15 & 0x0F));
		else print(" ", p2_pos.x, p2_pos.y, (7 << 4));

		switch (dir) {
			case ARB:
				if (p2_pos.y > 1) p2_pos.y -= 1;
				else p2_pos.y = 44;
				break;
			case ABA:
				if (p2_pos.y < 44) p2_pos.y += 1;
				else p2_pos.y = 1;
				break;
			case DER:
				 if (p2_pos.x < 79) p2_pos.x += 1;
				 else p2_pos.x = 0;
				break;
			case IZQ:
				 if (p2_pos.x > 0) p2_pos.x -= 1;
				 else p2_pos.x = 79;
				break;
		}
		print("*", p2_pos.x, p2_pos.y, (1 << 4) | (15 & 0x0F));
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