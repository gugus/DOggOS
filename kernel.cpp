
#include "types.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "pic.h"

int main(void);

// Point d' entrée du noyau
extern "C" void kmain(void) {
	
	screen::print((char*) "kernel : kernel is speaking !\n");

	idt_loader lidt;
	lidt.init_idt();
	screen::print((char*) "kernel : idt loaded\n");

	init_pic();
	screen::print((char*) "kernel : pic configured\n");

        screen::print((char*) "kernel : loading new gdt...\n");
	gdt_loader lgdt;
	lgdt.init_gdt();
	screen::print((char*)"kernel : gdt loaded\n");

        asm("   movw $0x18, %ax \n \
                movw %ax, %ss \n \
                movl $0x20000, %esp");
	
	main();

}

int main(void) {

	sti;
	screen::print((char*) "kernel : allowing interrupt\n");
        screen::print((char*) "kernel : kernel is ready !\n\n\n");
	screen::set_attr(0X09);
	screen::print((char*) "doggos > ");
	screen::show_cursor();
	while (1);
}

