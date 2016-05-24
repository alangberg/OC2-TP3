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
    [GDT_IDX_NULL_DESC1] = (gdt_entry) { //TABLA NULL(la primera)
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    [GDT_IDX_NULL_DESC2] = (gdt_entry) { //TABLA NULL(la primera)
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    [GDT_IDX_NULL_DESC3] = (gdt_entry) { //TABLA NULL(la primera)
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_CODE_0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */  //CONSULTAR (0x36DFF) 
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */  //CAPAZ ES B VERDURITA
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_DATA_0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */  //CONSULTAR (0x36DFF) 
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */  //CAPAZ ES 3 VERDURITA
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  //listo
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_CODE_3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */  //CONSULTAR (0x36DFF) 
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */  //CAPAZ ES B VERDURITA
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
        [GDT_IDX_DATA_3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */  //CONSULTAR (0x36DFF) 
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */ //CAPAZ ES 3 VERDURITA
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */  //Listo
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [GDT_IDX_VIDEO_3] = (gdt_entry) {
        (unsigned short)    0xffff,         /* limit[0:15]  */  //Verdurita
        (unsigned short)    0x8000,         /* base[0:15]   */  
        (unsigned char)     0x0b,           /* base[23:16]  */
        (unsigned char)     0x03,           /* type         */ //CAPAZ ES OTRO VERDURITA (ACCESED?)
        (unsigned char)     0x001,           /* s            */
        (unsigned char)     0x03,           /* dpl          */  //Que privilegio tiene el video
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x0b,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
 
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};



