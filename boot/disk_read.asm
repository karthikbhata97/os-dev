[bits 16]

disk_load:
	
	push bx
	mov bx, MSG_DISK_LOAD
	call print_string
	pop bx

	push dx
	mov ah, 0x02
	mov al, dh
	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02
	int 0x13

	jc disk_error
	pop dx

	cmp dh, al
	jne disk_error_new
	ret

disk_error_new:
	add al, 0x30
	mov ah, 0x0e
	int 0x10
	mov bx, DISK_ERR_MSG_NEW
	call print_string
	jmp $

disk_error:
	mov bx, DISK_ERR_MSG
	call print_string
	jmp $

DISK_ERR_MSG: db "Disk read error!", 0
DISK_ERR_MSG_NEW: db "Couldn't read all sectors!", 0
MSG_DISK_LOAD: db "Started disk operation", 0