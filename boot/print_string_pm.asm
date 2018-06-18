[bits 32]
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY
	
print_string_pm_loop:
	mov ah, WHITE_ON_BLACK
	mov al, [ebx]
	cmp al, 0
	je print_string_pm_done

	mov [edx], ax
	add edx, 2
	add ebx, 1
	jmp print_string_pm_loop

print_string_pm_done:
	popa
	ret
