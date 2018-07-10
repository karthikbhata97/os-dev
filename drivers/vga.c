#include "vga.h"
#include "ports.h"

int get_cursor_pos();
void set_cursor_offset(int);

int get_cursor_pos() {
	int position = 0;
	
	/* Ask for upper byte */
	port_byte_out(REG_SCREEN_CTRL, 14);
	position = port_byte_in(REG_SCREEN_DATA) << 8;

	/* Ask for upper byte */
	port_byte_out(REG_SCREEN_CTRL, 15);
	position |= port_byte_in(REG_SCREEN_DATA);

	return position * 2;
}


void kprint(char *message) {
	int iter=0, offset=0;
	unsigned char * vide_mem = (unsigned char *) VIDEO_ADDRESS;
	int pos = get_cursor_pos();
	// pos *= 2;
	for (iter=0, offset=pos; message[iter]; iter++, offset+=2) {
		vide_mem[offset] = message[iter];
		vide_mem[offset+1] = BLACK_ON_WHITE;
	}

	set_cursor_offset(offset);

	return;
}

void set_cursor_offset(int offset) {
	/* Send upper byte */
	offset = offset / 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));

	/* Send lower byte */
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)offset);

	return;
}

void kprint_at(char *message, int row, int column) {

	if (row==-1 && column==-1) {
		kprint(message);
		return;
	}

	int offset = row * MAX_ROWS + column;

	set_cursor_offset(offset * 2);

	kprint(message);

	return;
}

/*
int print_char(char c, int r, int col, int attr) {
	unsigned char *video_mem = (unsigned char *) VIDEO_ADDRESS;

	if(!attr) attr = BLACK_ON_WHITE;

	int offset = get_offset(row, col);

	video_mem[offset] = c;
	video_mem[offset+1] = attr;
	offset += 2;

	return offset;
}


int get_offset(int row, int col) {
	return (row*MAX_ROWS + col) * 2;
}

int get_offset_row(int offset) {
	return ((offset/2)/MAX_COLUMNS);
}

int get_offset_column(int offset) {
	return ((offset/2)-(get_offset_row(offset)*MAX_COLUMNS));
}
*/
