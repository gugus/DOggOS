
#ifndef GDT_H
#define GDT_H

#define GDTBASE    0x0		/* addr. physique ou doit resider la gdt */
#define GDTSIZE    0xFF		/* nombre max. de descripteurs dans la table */

class gdt_loader {

	private:
	//  Descripteur de segment 
	struct gdtdesc {
    		u16 lim0_15;    
    		u16 base0_15;
    		u8 base16_23;
    		u8 acces;
    		u8 lim16_19 : 4;
    		u8 other : 4;
    		u8 base24_31;
	} __attribute__ ((packed));
	// Initie un descripteur de segment
	static void init_gdt_desc(u32, u32, u8, u8, struct gdtdesc *);

	public:
	// Registre GDT
	struct gdtr {
    		u16 limite ;
    		u32 base ;
	} __attribute__ ((packed));

	// Initie la GDT
	void init_gdt(void);

	private:
	struct gdtdesc kgdt[GDTSIZE];
	struct gdtr kgdtr;		

};

#endif
