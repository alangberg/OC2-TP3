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
gdt_entry gdt[GDT_COUNT];

void tss_inicializar(){

}

void tss_inicializar_idle() { //CONSULTAR TODAS LAS LINEAS, ES UNA FRUTA TREMENDA ESTO.
   // typedef struct str_tss {
//     unsigned short  ptl;
//     unsigned short  unused0;
       tss_idle.esp0 = mmu_proxima_pagina_fisica_libre();       //Prox pagina fisica libre
       tss_idle.ss0 = 0x28;        //SS que use en la gdt
//     unsigned short  unused1;
//     unsigned int    esp1;
 //      tss_idle.ss1 = 0x38;
//     unsigned short  unused2;
//     unsigned int    esp2;
//     unsigned short  ss2;
//     unsigned short  unused3;
       tss_idle.cr3 = 0x27000;
       tss_idle.eip = 0x10000; //QUE INSTR POINTER USO?
       tss_idle.eflags = 0x202; //diapo pagina 24
//     unsigned int    eax;   /LOS DEJO
//     unsigned int    ecx;	  |A TODOS
//     unsigned int    edx;	  |COMO
//     unsigned int    ebx;	  \ESTAN
       tss_idle.esp = 0x27000;
       tss_idle.ebp = tss_idle.esp;
//     unsigned int    esi;  ID
//     unsigned int    edi;  EM
       tss_idle.es = 0x28;
//     unsigned short  unused4;
       tss_idle.cs = 0x20;
//     unsigned short  unused5;
       tss_idle.ss = 0x28;
//     unsigned short  unused6;
       tss_idle.ds = 0x28;
//     unsigned short  unused7;
       tss_idle.fs = 0x28;
//     unsigned short  unused8;
       tss_idle.gs = 0x28;
//     unsigned short  unused9;
//     unsigned short  ldt;
//     unsigned short  unused10;
//     unsigned short  dtrap; 0
       tss_idle.iomap = 0xFFFF;


	
	gdt[9] = (gdt_entry) {
        (unsigned short)    sizeof(tss)-1,         			/* limit[0:15]  */ 
        (unsigned short)    (unsigned int) &tss_inicial, 					/*aca hay q ponerle (bien) &tss_inicial*/         /* base[0:15]   */
        (unsigned char)     (unsigned int) &tss_inicial >> 16,           	/* base[23:16]  */
        (unsigned char)     0x09,           				/* type         */
        (unsigned char)     0x00,           				/* s            */
        (unsigned char)     0x00,           				/* dpl          */  //listo
        (unsigned char)     0x01,           				/* p            */
        (unsigned char)     (sizeof(tss)-1) >> 16,           /* limit[16:19] */
        (unsigned char)     0x00,           				/* avl          */
        (unsigned char)     0x00,           				/* l            */
        (unsigned char)     0x00,           				/* db           */
        (unsigned char)     0x00,           				/* g            */
        (unsigned char)     (unsigned int) &tss_inicial >> 24,           	/* base[31:24]  */
	}; // tss inicial
	gdt[10] = (gdt_entry) {
        (unsigned short)    sizeof(tss)-1,         			/* limit[0:15]  */ 
        (unsigned short)    (unsigned int) &tss_idle, 						/*aca hay q ponerle (bien) &tss_inicial*/         /* base[0:15]   */
        (unsigned char)     (unsigned int) &tss_idle >> 16,         		/* base[23:16]  */
        (unsigned char)     0x09,           				/* type         */
        (unsigned char)     0x00,           				/* s            */
        (unsigned char)     0x00,           				/* dpl          */  //listo
        (unsigned char)     0x01,           				/* p            */
        (unsigned char)     (sizeof(tss)-1) >> 16,          /* limit[16:19] */
        (unsigned char)     0x00,           				/* avl          */
        (unsigned char)     0x00,           				/* l            */
        (unsigned char)     0x00,           				/* db           */
        (unsigned char)     0x00,           				/* g            */
        (unsigned char)     (unsigned int) &tss_idle >> 24,                /* base[31:24]  */
	}; // tss idleL

}