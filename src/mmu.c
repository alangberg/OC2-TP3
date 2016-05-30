/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

//Macros
#define PDE_INDEX(virtual) virtual >> 22
#define PTE_INDEX(virtual) (virtual >> 12) & 0x3FF
#define ALIGN(dir)
#define PG_READ_WRITE 0x00000002
#define PG_USER 0x00000004
#define PG_PRESENT 0x00000001

void mmu_inicializar_dir_kernel(){
	int* page_directory = (int*) PAGE_DIRECTORY_KERNEL;
	page_directory[0] = PAGE_TABLE_KERNEL + 0x3;
	int i;
	for (i = 1; i < 1024; ++i) {
		page_directory[i]= 0x0;
	}

	int* page_table = (int*) PAGE_TABLE_KERNEL;
	for (i = 0; i < 1024; ++i) {
		page_table[i] = ((i << 12) | 3) ;
	}
}


unsigned int proxima_pagina_libre;
void mmu_inicializar() {
	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}


unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	return pagina_libre;
}

/*Mapea la pagina fisica a la marco de pagina virtual en el esquema
de paginacion cr3.*/
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica){
	// Agarro los 1ros 20bits de la CR3 que corresponden a la direccion base del directorio de paginas
	int* page_directory = (int*) (cr3 & 0xFFFFF000);

	page_directory = (int*)((*page_directory) + (PDE_INDEX(virtual))*4);

	// si PRESENT es 0
	if (!((*page_directory) & PG_PRESENT)) {
		// pongo la dir en 0
		*page_directory &= 0x00000FFF;
		// la igualo con el resultado de la funcion (me da un numero de 32bits lo corro 12 lugares)
		*page_directory |= mmu_proxima_pagina_fisica_libre() << 12;
		// le pongo en 1 el PRESENT
		*page_directory |= PG_PRESENT;
	}

	int* table_directory = (int*) (*page_directory & 0xFFFFF000) + (PTE_INDEX(virtual)*4);

	*table_directory &= 0x00000FFF;
	*table_directory |= fisica << 12;
	*table_directory |= PG_PRESENT;
}

/*Desmapea la pagina fisica en el esquema de paginacion cr3.*/
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){}

/*

#include "mmu.h"
#define PDE_INDEX(virtu) virtu >> 22
#define PTE_INDEX(virtu) (virtu << 10) >> 22
//#define ALIGN(dir)         
#define PG_READ_WRITE	0x00000002
#define PG_USER			0x00000004
#define PG_PRESENT		0x00000001

#define PAGE_SIZE		0x00001000

page_entries_set* PDE = (page_entries_set*) PAGE_DIRECTORY_BASE;
page_entries_set* PTE = (page_entries_set*) PAGE_TABLE_BASE;
unsigned int proxima_pagina_libre = INICIO_PAGINAS_LIBRES;

void mmu_inicializar() {
	unsigned int i = 0;
	unsigned int wr_p = PG_READ_WRITE | PG_PRESENT;
	while (i < 1024){ 
		PDE->page_entries[i].attr = 0;
		PTE->page_entries[i].attr = wr_p;
		PTE->page_entries[i].base_page_addr = i;
		i++;
	}

	PDE->page_entries[0].attr = wr_p;
	PDE->page_entries[0].base_page_addr = PAGE_TABLE_BASE >> 12;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	
	return pagina_libre;
}

void mmu_mapear_pagina(unsigned int virtu, unsigned int cr3, unsigned int fisica){
	page_entries_set* pd = (page_entries_set*) (cr3 & 0xFFFFF000);

	unsigned int pd_ind = PDE_INDEX(virtu);
	//LO MAS DECLARATIVO QUE EXISTE
	if(!(pd->page_entries[pd_ind].attr & PG_PRESENT)){
		pd->page_entries[pd_ind].attr |= PG_PRESENT;
		pd->page_entries[pd_ind].base_page_addr = mmu_proxima_pagina_fisica_libre() >> 12;
	}

	page_entries_set* pt = (page_entries_set*) (pd->page_entries[pd_ind].base_page_addr << 12);
	unsigned int pt_ind = PTE_INDEX(virtu);
	pt->page_entries[pt_ind].attr |= PG_PRESENT;
	pt->page_entries[pt_ind].base_page_addr = fisica >> 12;
}

void mmu_inicializar_dir_tarea(){

}

*/

