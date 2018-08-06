#include "../drivers/vga.h"
#include "../cpu/isr.h"

void main() {
	kprint("an0ne was here!\n");
	kprint("an0ne was here!\n");
	kprint("an0ne was here!\n");
	kprint("Time to rock!");
	kprint_at("Wavin' flag!", 0, 0);
	kprint_at("an0ne is here!", 12, 23);
	scroll(1);
	kprint("Hello. This is a really really long string. Let it print in the next line! Oh should work.");
	
	install_isr();

	__asm__ __volatile__ ("int $2");
	__asm__ __volatile__ ("int $3");

	return;
}
