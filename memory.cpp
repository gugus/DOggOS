
#include "memory.h"
#include "types.h"

#define PAGING_FLAG     0x80000000      // CR0 - bit 31

#define PD0_ADDR 0x20000        // addr. du répertoire de pages
#define PT0_ADDR 0x21000        // addr. de table[0]

// cree un mapping tel que vaddr = paddr sur 4Mo
void memory::init(void) {

        u32 *pd0;       // répertoire de pages du noyau
        u32 *pt0;       // table de pages du noyau
        u32 page_addr;
        int i;

        // Creation du répertoire de pages
        pd0 = (u32 *) PD0_ADDR;
        pd0[0] = PT0_ADDR; // La première entrée du répertoire pointe sur la première table de page
        pd0[0] |= 3; //Les deux premiers bits sont mis à 1 pour indiquer que les pages / tables pointées sont présentes en mémoire et qu'elles sont accessibles en lecture et en écriture
       
	// Les autres entrées du répertoire sont mises à zéro : on n'utilise qu'une seule table de pages
	 for (i = 1; i < 1024; i++)
                pd0[i] = 0;


        // Creation de la page table[0]
        pt0 = (u32 *) PT0_ADDR;
        page_addr = 0;
	// Chacune des entrées pointe sur une page mémoire successive
        for (i = 0; i < 1024; i++) {
                pt0[i] = page_addr;
                pt0[i] |= 3;
                page_addr += 4096;
        }

	// On active la pagination
        asm("   mov %0, %%eax    \n \
                mov %%eax, %%cr3 \n \
                mov %%cr0, %%eax \n \
                or %1, %%eax     \n \
                mov %%eax, %%cr0" :: "i"(PD0_ADDR), "i"(PAGING_FLAG));
}
