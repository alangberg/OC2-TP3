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
    [GDT_IDX_NULL_KERNEL] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */ 
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    //DESCRIPTOR NULL
    [GDT_IDX_NULL_DESC1] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    //DESCRIPTOR NULL
    [GDT_IDX_NULL_DESC2] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    //DESCRIPTOR NULL
    [GDT_IDX_NULL_DESC3] = (gdt_entry) { 
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    //DESCRIPTOR DE CODIGO 0
        [GDT_0_CODE_KERNEL] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */  
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */  //CAPAZ ES B VERDURITA
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    //DESCRIPTOR DE DATOS 0
        [GDT_0_DATA_KERNEL] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */  //CONSULTAR (0x36DFF) 
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */  //CAPAZ ES 3 VERDURITA
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */  
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    //DESCRIPTOR DE CODIGO 1
        [GDT_1_CODE_USER] = (gdt_entry) {
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
    //DESCRIPTOR DE DATOS 1
        [GDT_1_DATA_USER] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */ //CONSULTAR (0x36DFF) 
        (unsigned short)    0x0000,         /* base[0:15]   */  
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */ //CAPAZ ES 3 VERDURITA
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
    //DESCRIPTOR DE VIDEO
    [GDT_2_VIDEO_USER] = (gdt_entry) {
        (unsigned short)    0xffff,         /* limit[0:15]  */  //Verdurita
        (unsigned short)    0x8000,         /* base[0:15]   */  
        (unsigned char)     0x0b,           /* base[23:16]  */
        (unsigned char)     0x03,           /* type         */ //CAPAZ ES OTRO VERDURITA (ACCESED?)
        (unsigned char)     0x001,          /* s            */
        (unsigned char)     0x00,           /* dpl          */  //Que privilegio tiene el video
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x0b,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    }
    // 8.[GDT_TSS_INICIAL]
    // 9.[GDT_TSS_IDLE]

};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};



