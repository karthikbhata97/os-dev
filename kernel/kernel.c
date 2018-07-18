#include "../drivers/vga.h"

void main() {
	kprint("an0ne was here!\n");
	kprint("an0ne was here!\n");
	kprint("an0ne was here!\n");
	kprint("Time to rock!");
	kprint_at("Wavin' flag!", 0, 0);
	kprint_at("an0ne is here!", 12, 23);
	scroll(1);
	kprint("Hello");
	scroll(1);
	// kprint_at("Scrolling works!", MAX_ROWS-1, 0);
	return;
}
