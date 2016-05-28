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
#define PG_READ_WRITE
#define PG_USER
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
	
	


}
/*Desmapea la pagina fisica en el esquema de paginacion cr3.*/
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){}
