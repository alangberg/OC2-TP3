/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_H                 	15
#define CANT                    5
#define SIZE_W                  80
#define SIZE_H                  44
#define PAGE_DIRECTORY_KERNEL   0x27000
#define PAGE_TABLE_KERNEL		0x28000
#define PAGE_SIZE				0x1000
#define INICIO_PAGINAS_LIBRES	0x100000


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 9

#define GDT_IDX_NULL_KERNEL          0
#define GDT_IDX_NULL_DESC1           1
#define GDT_IDX_NULL_DESC2           2
#define GDT_IDX_NULL_DESC3           3

#define GDT_0_CODE_KERNEL      	   	 4
#define GDT_0_DATA_KERNEL  	   	     5
#define GDT_1_CODE_USER	 	         6
#define GDT_1_DATA_USER	             7
#define GDT_2_VIDEO_USER	         8
#define GDT_TSS_INICIAL	        	 9
#define GDT_TSS_IDLE	        	 10




/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO_SCREEN            0x000B8000 /* direccion fisica del buffer de video */

#endif  /* !__DEFINES_H__ */
