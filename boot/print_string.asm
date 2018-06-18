[bits 16]

print_string:
	mov ah, 0x0e
	again:
		mov al, [bx]
		int 0x10
		inc bx
		cmp al, 0x0
		jne again
	mov al, 10
	int 0x10
	mov al, 13
	int 0x10
	ret
