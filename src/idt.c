/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"

#include "tss.h"

idt_entry idt[255] = { 

};

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/


#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x00;                                                                  \
    idt[numero].attr = (unsigned short) 0x0000;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);



void idt_inicializar() {
	IDT_ENTRY(0)
    // Excepciones
}

char* msjInt(unsigned char* i) {
	switch(*i) {
		case 0
			return "ERROR! No sabes que no podes divir por cero?";
		case 1
			return "ERROR! RESERVED";
		case 2
			return "ERROR! NMI Interrupt";
		case 3
			return "ERROR! Breakpoint";
		case 4
			return "ERROR! Overflow";
		case 5
			return "ERROR! BOUND Range Exceeded";
		case 6
			return "ERROR! Invalid Opcode (Undefined Opcode)";
		case 7
			return "ERROR! Double Fault";
		case 8
			return "ERROR! Coprocessor Segment Overrun (reserved)";
		case 9
			return "ERROR! Invalid TSS";
		case 10
			return "ERROR! Segment Not Present";
		case 11
			return "ERROR! Stack-Segment Fault";
		case 12
			return "ERROR! General Protection";
		case 13
			return "ERROR! Page Fault";
		case 14
			return "ERROR! (Intel reserved. Do not use.)";
		case 15
			return "ERROR! BOUND Range Exceeded";
		case 16
			return "ERROR! Invalid Opcode (Undefined Opcode)";
		case 17
			return "ERROR! Double Fault";
		case 18
			return "ERROR! Coprocessor Segment Overrun (reserved)";
		case 19
			return "ERROR! Invalid TSS";
	}
}