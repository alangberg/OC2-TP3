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
	int* PDE = (int*) (cr3 & 0xFFFFF000);

	PDE = (int*)((*PDE) + (PDE_INDEX(virtual))*4);

	// si PRESENT es 0
	if (!((*PDE) & PG_PRESENT)) {
		// pongo la dir en 0
		*PDE &= 0x00000FFF;
		// la igualo con el resultado de la funcion (me da un numero de 32bits donde los primeros 12 son 0s asi que esta todo re piolanga)
		*PDE |= mmu_proxima_pagina_fisica_libre();
		// le pongo en 1 el PRESENT y el RW como dice la diapo
		*PDE |= (PG_PRESENT | PG_READ_WRITE);

		// dejo el resto de la tabla en 0
		int i;
		int* it = PDE + 0x8000;
		for (i = 1; i < 1024; i++) {
			*it = 0x00000000;
			it = it + 0x8000;
		}
	}

	int* PTE = (int*) (*PDE & 0xFFFFF000) + (PTE_INDEX(virtual)*4);

	*PTE &= 0x00000FFF;
	*PTE |= fisica;
	*PTE |= (PG_PRESENT | PG_READ_WRITE);
}

/*Desmapea la pagina fisica en el esquema de paginacion cr3.*/
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3) {
	int* PDE = (int*) (cr3 & 0xFFFFF000);
	PDE = (int*)((*PDE) + (PDE_INDEX(virtual))*4);

	// aca no se si poner 0xFFFFFFFE para no perder todo el resto de los datos pero creo q si PRESENT esta en 0 ya no importan.
	*PDE &= 0x00000000;
}
