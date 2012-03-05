#!/bin/bash

g++ -c -m32 -nostdinc -fno-exceptions -fno-rtti -fno-stack-protector -fno-builtin lsv.cpp interrupt.cpp pic.cpp idt.cpp lib.cpp gdt.cpp screen.cpp kernel.cpp
nasm -f elf32 -o int.o int.asm
nasm -f  elf32 -o header.o header.asm 
ld -melf_i386 -Ttext=100000 --entry=_start -nostartfiles -nodefaultlibs -nostdlib header.o lib.o kernel.o screen.o gdt.o idt.o pic.o interrupt.o int.o -o kernel
mount -o loop -t ext2 floppyA /mnt/loop
cp kernel /mnt/loop
umount /mnt/loop 
