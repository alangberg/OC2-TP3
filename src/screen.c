/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "game.h"

void imprimirTeclado(char codigo) {
    switch (codigo) {
        case 0x11:
            print("W", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(1, 0xA33);
            break;
        case 0x1e:
            print("A", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(1, 0xAAA);
            break;
        case 0x1f:
            print("S", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(1, 0x883);
            break;
        case 0x20:
            print("D", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(1, 0x441);
            break;
        case 0x2a:
            print("LShift", 74, 0, (0 << 4) | (15 & 0x0F));
            break;
        case 0x17:
            print("I", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(2, 0xA33);
            break;
        case 0x24:
            print("J", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(2, 0xAAA);
            break;
        case 0x25:
            print("K", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(2, 0x883);
            break;
        case 0x26:
            print("L", 79, 0, (0 << 4) | (15 & 0x0F));
            game_mover_cursor(2, 0x441);
            break;
        case 0x36:
            print("RShift", 74, 0, (0 << 4) | (15 & 0x0F));
            break;
        case 0x15:
            MainSystem.debugMode = !MainSystem.debugMode;
            break;
        default:
            print("      ", 74, 0, (0 << 4));
            break;
    }
}

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

// attr = (backcolour << 4) | (forecolour & 0x0F)
void imprimirJuego(unsigned int vidaP1, unsigned int vidaP2, unsigned int ptosP1, unsigned int ptosP2) {
    int x;
    for (x = 0; x < 160; x++) print(" ", x, 0, 0);

    int y = 1;
    x = 0;
    while (y < 45) { // se podria poner en una linea sola llamando a print    
        print(" ", x, y, (7 << 4) | (0 & 0x0F));
        
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }

    while (y < 50) {
        if (x > 47 && x < 55) {
            print(" ", x, y, (4 << 4) | (0 & 0x0F)); // aca pinto todo de rojo para el P1
        } else if (x > 54 && x < 62) {
            print(" ", x, y, (1 << 4) | (0 & 0x0F)); // aca pinto todo de azul para el P2
        } else {
            print(" ", x, y, 0); // si no va todo en negro
        }

        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }

    print("vidas", 41, 46, (0 << 4) | (15 & 0x0F));
    print("vidas", 64, 46, (0 << 4) | (15 & 0x0F));

    print_int(MainSystem.jugadores[0].vida, 43, 48, (0 << 4) | (15 & 0x0F));
    print_int(MainSystem.jugadores[1].vida, 66, 48, (0 << 4) | (15 & 0x0F));

    print_int(MainSystem.jugadores[0].puntos, 51, 47, (4 << 4) | (15 & 0x0F));
    print_int(MainSystem.jugadores[1].puntos, 58, 47, (1 << 4) | (15 & 0x0F));

    print("<A", 12, 46, (0 << 4) | (15 & 0x0F));
    print("B>", 19, 46, (0 << 4) | (15 & 0x0F));

    print("*", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (4 << 4) | (15 & 0x0F));
    print("*", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (1 << 4) | (15 & 0x0F));
}

void imprimirError() {
    //ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;

    int y = 7;
    int x = 24;
    while (y < 42) {
        if (y == 7 || y == 41 || x == 24 || x == 53) print(" ", y, x, 0);
        else {
            if (y == 8){
                if (MainSystem.jugadorActual == A) {
                    print(" ", y, x, (4 << 4));
                    print("virus A", 8, 25, (4 << 4) | (15 & 0x0F));
                } else {
                    print(" ", y, x, (1 << 4));
                    print("virus B", 8, 25, (1 << 4) | (15 & 0x0F));
                }
            } else {
                print(" ", y, x, (7 << 4));
            }
        }

        if (x == 54) {
            y++;
            x = 24;
        } else x++;
    }
/*
    print("eax", 10, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 8, 10, 30, (7 << 4) | (15 & 0x0F))
    print("ebx", 12, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 12, 30, (7 << 4) | (0 & 0x0F));
    print("ecx", 14, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 14, 30, (7 << 4) | (0 & 0x0F));
    print("edx", 16, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 16, 30, (7 << 4) | (0 & 0x0F));
    print("esi", 18, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 18, 30, (7 << 4) | (0 & 0x0F));
    print("edi", 20, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 20, 30, (7 << 4) | (0 & 0x0F));
    print("ebp", 22, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 22, 30, (7 << 4) | (0 & 0x0F));
    print("esp", 24, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 24, 30, (7 << 4) | (0 & 0x0F));
    print("eip", 26, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 26, 30, (7 << 4) | (0 & 0x0F));
    print(" cs", 28, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 28, 30, (7 << 4) | (0 & 0x0F));
    print(" ds", 30, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 30, 30, (7 << 4) | (0 & 0x0F));
    print(" es", 32, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 32, 30, (7 << 4) | (0 & 0x0F));
    print(" fs", 34, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 34, 30, (7 << 4) | (0 & 0x0F));
    print(" gs", 36, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 36, 30, (7 << 4) | (0 & 0x0F));
    print(" ss", 38, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 38, 30, (7 << 4) | (0 & 0x0F));
    print(" eflags", 40, 26, (7 << 4) | (0 & 0x0F));
    print_hex(, 40, 43, (7 << 4) | (0 & 0x0F));


    print("cr0", 10, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 10, 44, (7 << 4) | (0 & 0x0F));
    print("cr1", 12, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 12, 44, (7 << 4) | (0 & 0x0F));
    print("cr2", 14, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 14, 44, (7 << 4) | (0 & 0x0F));
    print("cr3", 16, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 16, 44, (7 << 4) | (0 & 0x0F));

    print("stack", 26, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 29, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 30, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 31, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 32, 40, (7 << 4) | (0 & 0x0F));
    print_hex(, 33, 40, (7 << 4) | (0 & 0x0F));
*/

}