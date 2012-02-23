#include "types.h"
#include "lib.h"

#include "gdt.h"


// 'init_desc' initialise un descripteur de segment situe en gdt ou en ldt.
// 'desc' est l'adresse lineaire du descripteur a initialiser.

void gdt_loader::init_gdt_desc(u32 base, u32 limite, u8 acces, u8 other,
                   struct gdtdesc *desc)
{
        desc->lim0_15 = (limite & 0xffff);
        desc->base0_15 = (base & 0xffff);
        desc->base16_23 = (base & 0xff0000) >> 16;
        desc->acces = acces;
        desc->lim16_19 = (limite & 0xf0000) >> 16;
        desc->other = (other & 0xf);
        desc->base24_31 = (base & 0xff000000) >> 24;
        return;
}


// Cette fonction initialise la GDT apres que le kernel soit charge
// en memoire. Une GDT est deja operationnelle, mais c'est celle qui
// a ete initialisee par le secteur de boot et qui ne correspond
// pas forcement a celle que l'on souhaite.


// On a besoin d'une variable globale liée en C pour transmettre le
// registre GDT au code assembleur
extern "C" {
	
	struct gdt_loader::gdtr ext_kgdtr;
}

void gdt_loader::init_gdt(void)
{

        // initialisation des descripteurs de segment
        init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
        init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);      /* code */
        init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);      /* data */
        init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);          /* stack */

        // initialisation de la structure pour GDTR 
        kgdtr.limite = GDTSIZE * 8;
        kgdtr.base = GDTBASE;

        // recopie de la GDT a son adresse
        memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);
	
	// Chargement du registre GDT
	ext_kgdtr = kgdtr;
        asm("lgdtl (ext_kgdtr)");

	// Initialisation des segments
        asm("   movw $0x10, %ax \n \
            movw %ax, %ds       \n \
            movw %ax, %es       \n \
            movw %ax, %fs       \n \
            movw %ax, %gs       \n \
            ljmp $0x08, $next   \n \
            next:               \n");
}

