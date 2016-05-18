/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) { //TABLA NULL(la primera)
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
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
    },
        [GDT_IDX_CODE0_DESC] = (gdt_entry) {
        (unsigned short)    0xB799,         /* limit[0:15]  */  //CONSULTAR (DB799)
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x0D,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_DATA0_DESC] = (gdt_entry) {
        (unsigned short)    0xB799,         /* limit[0:15]  */  //CONSULTAR (DB799)
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x0D,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_CODE1_DESC] = (gdt_entry) {
        (unsigned short)    0xB799,         /* limit[0:15]  */  //CONSULTAR (DB799)
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x0D,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_DATA1_DESC] = (gdt_entry) {
        (unsigned short)    0xB799,         /* limit[0:15]  */  //CONSULTAR (DB799)
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */  //Listo
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x0D,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};


