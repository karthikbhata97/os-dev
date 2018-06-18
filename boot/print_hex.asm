puts:
	mov ah, 0xe
	repeat:
		mov al, [bx]
		int 0x10
		add bx, 1
		cmp al, 0
		jne repeat
	mov al, 10
	int 0x10
	mov al, 13
	int 0x10
	ret


print_hex:
	; convert num to str
	mov di, HEX_STR
	mov cl, 16
	looper:
		sub cl, 4
		mov ax, bx
		shr ax, cl
		and al, 0xf
		add al, 0x30
		cmp al, '9'
		jle next
		add al, 7
		next:
		mov [di], al
		add di, 1
		cmp cl, 0
		jne looper

	mov bx, HEX_STR
	call puts
	ret

HEX_STR:
	db '0000', 0
