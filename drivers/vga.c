#include "vga.h"
#include "ports.h"
#include "../kernel/utils.h"


#define get_offset(row, col) (row*MAX_COLUMNS + col) * 2

#define get_offset_row(offset) ((offset/2)/MAX_COLUMNS)

#define get_offset_column(offset) ((offset/2)-(get_offset_row(offset)*MAX_COLUMNS))



int get_cursor_offset();
void set_cursor_offset(int);
int print_char(char, int, int, int);

void copy_lines(int, int);
void clear_line(int);

int get_cursor_offset() {
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

	return kprint_at(message, -1, -1);

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

	int iter=0, offset=0;

	for (iter=0; message[iter]; iter++) {
		offset = print_char(message[iter], row, column, 0);
		row = get_offset_row(offset);
		column = get_offset_column(offset);
	}

	return;
}


int print_char(char c, int row, int col, int attr) {
	unsigned char *video_mem = (unsigned char *) VIDEO_ADDRESS;

	if(!attr) attr = BLACK_ON_WHITE;
	int offset;

	if(row<0 && col<0) {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_column(offset);
	}

	if (col>=MAX_COLUMNS && row>=MAX_ROWS) {
		offset = get_offset(MAX_ROWS-1, MAX_COLUMNS-1);
		video_mem[offset] = 'E';
		video_mem[offset+1] = RED_ON_WHITE;
		return get_offset(row, col);
	}

	if (c=='\n') {
		offset = get_offset(row, MAX_COLUMNS-1);
	}
	else {
		offset = get_offset(row, col);
		video_mem[offset] = c;
		video_mem[offset+1] = attr;
	}
	offset += 2;

	row = get_offset_row(offset);
	col = get_offset_column(offset);

	if (row==MAX_ROWS && col==0) {
		offset = scroll(1);
	}

	set_cursor_offset(offset);
	return offset;
}


void copy_lines(int source_r, int dest_r) {
	int source_off = get_offset(source_r, 0);
	int dest_off = get_offset(dest_r, 0);

	int column_end = MAX_COLUMNS;
	char *video_mem = (char *)VIDEO_ADDRESS;
	int i;

	memory_copy(source_off+video_mem, dest_off+video_mem, MAX_COLUMNS*2);
	
}

void clear_line(int row) {
	int offset = get_offset(row, 0);
	int i;
	char * video_mem = (char *)VIDEO_ADDRESS;
	for (i=0;i<MAX_COLUMNS;i++) {
		video_mem[offset] = 0;
		video_mem[offset+1] = 0;
		offset += 2;
	}
}

int scroll(int nlines) {
	int i;
	int offset = get_offset((MAX_ROWS-nlines), 0);

	for (i=nlines;i<MAX_ROWS;i++) {
		copy_lines(i, i-nlines);
	}

	for (i=MAX_ROWS-nlines;i<MAX_ROWS;i++) {
		clear_line(i);
	}

	set_cursor_offset(offset);
	return offset;
}