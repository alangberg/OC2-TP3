/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"

tss tss_inicial;
tss tss_idle;



void tss_inicializar() {
	tss_idle = {
		// aca hay q ponerle los datos que dice la diapo
	}

	tss_inicial = {
		// aca hay q ponerle los datos que dice la diapo
	}

	gdt[9] = {
        (unsigned short)    0x0000,         /* limit[0:15]  */ 
        (unsigned short)    /*aca hay q ponerle (bien) &tss_inicial*/,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
	} // tss inicial
}
