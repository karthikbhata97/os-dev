void main() {
	int i;
	char * video_mem = (char *) 0xb8000;
	*video_mem = 'X';

	unsigned short pos = 0;
	port_byte_out(0x3d4, 14);
	pos = port_byte_in(0x3d5) << 8;
	port_byte_out(0x3d4, 14);
	pos |= port_byte_in(0x3d5);
	
	int vga_offset = pos * 2;
	// *(video_mem+vga_offset) = 'Y';
	// *(video_mem+vga_offset+1) = 0x0f;
	char *hw = "HelloWorld!";
	i = 0; 
	while(*(hw+i)) {
		video_mem[vga_offset] = *(hw+i);
		video_mem[vga_offset+1] = 0x0f;
		i +=  1;
		vga_offset += 2;
	}
	return;
}
