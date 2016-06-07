/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"
#include "mmu.h"

tss tss_inicial;
tss tss_idle;


void tss_inicializar_idle() { //CONSULTAR TODAS LAS LINEAS, ES UNA FRUTA TREMENDA ESTO.
    tss_idle.cr3 = 0x2700;
    tss_idle.eip = 0x0;      //¿?.
    /*La pila se alojará en la misma dirección que la pila del kernel y será mapeada con identity mapping.
    Esta tarea ocupa 1 pagina de 4KB.*/
    tss_idle.esp0 = mmu_proxima_pagina_fisica_libre();	
    tss_idle.esp = pila;    
    tss_idle.ebp = tss_idle.esp;
    tss_idle.eflags = 0x202; //diapo pagina 24
    tss_idle.es = 
    tss_idle.cs =
    tss_idle.ss =
    tss_idle.fs =
    tss_idle.gs =
}
	
gdt[9] = {
        (unsigned short)    sizeof(tss)-1,         			/* limit[0:15]  */ 
        (unsigned short)    &tss_inicial, 					/*aca hay q ponerle (bien) &tss_inicial*/,         /* base[0:15]   */
        (unsigned char)     &tss_inicial >> 16,           	/* base[23:16]  */
        (unsigned char)     0x00,           				/* type         */
        (unsigned char)     0x00,           				/* s            */
        (unsigned char)     0x00,           				/* dpl          */  //listo
        (unsigned char)     0x01,           				/* p            */
        (unsigned char)     (sizeof(tss)-1) >> 16,           /* limit[16:19] */
        (unsigned char)     0x00,           				/* avl          */
        (unsigned char)     0x00,           				/* l            */
        (unsigned char)     0x00,           				/* db           */
        (unsigned char)     0x00,           				/* g            */
        (unsigned char)     &tss_inicial >> 24,           	/* base[31:24]  */
	} // tss inicial
gdt[10] = {
        (unsigned short)    sizeof(tss)-1,         			/* limit[0:15]  */ 
        (unsigned short)    &tss_idle, 						/*aca hay q ponerle (bien) &tss_inicial*/,         /* base[0:15]   */
        (unsigned char)     &tss_idle >> 16,         		/* base[23:16]  */
        (unsigned char)     0x00,           				/* type         */
        (unsigned char)     0x00,           				/* s            */
        (unsigned char)     0x00,           				/* dpl          */  //listo
        (unsigned char)     0x01,           				/* p            */
        (unsigned char)     (sizeof(tss)-1) >> 16,          /* limit[16:19] */
        (unsigned char)     0x00,           				/* avl          */
        (unsigned char)     0x00,           				/* l            */
        (unsigned char)     0x00,           				/* db           */
        (unsigned char)     0x00,           				/* g            */
        (unsigned char)     &tss_idle >> 24,                /* base[31:24]  */
	} // tss idle

// typedef struct str_tss {
//     unsigned short  ptl;
//     unsigned short  unused0;
//     unsigned int    esp0;       //Prox pagina fisica libre
//     unsigned short  ss0;        //SS que use en la gdt
//     unsigned short  unused1;
//     unsigned int    esp1;
//     unsigned short  ss1;
//     unsigned short  unused2;
//     unsigned int    esp2;
//     unsigned short  ss2;
//     unsigned short  unused3;
//     unsigned int    cr3;        //LISTO
//     unsigned int    eip;
//     unsigned int    eflags;
//     unsigned int    eax;
//     unsigned int    ecx;
//     unsigned int    edx;
//     unsigned int    ebx;
//     unsigned int    esp;
//     unsigned int    ebp;
//     unsigned int    esi;
//     unsigned int    edi;
//     unsigned short  es;
//     unsigned short  unused4;
//     unsigned short  cs;
//     unsigned short  unused5;
//     unsigned short  ss;
//     unsigned short  unused6;
//     unsigned short  ds;
//     unsigned short  unused7;
//     unsigned short  fs;
//     unsigned short  unused8;
//     unsigned short  gs;
//     unsigned short  unused9;
//     unsigned short  ldt;
//     unsigned short  unused10;
//     unsigned short  dtrap;
//     unsigned short  iomap;
// } __attribute__((__packed__, aligned (8))) tss;









