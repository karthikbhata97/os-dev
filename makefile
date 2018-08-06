# $^ all dependencies
# $< first dependencies
# $@ target file
C_SOUCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.c)

OBJ = ${C_SOUCES:.c=.o cpu/interrupt.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
CFLAGS = -g

# Default, create os-image and run
all: os-image

run: all
	bochs

debug: os-image kernel.elf
	echo 6 | bochs & 
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"


# Create os image from 16bit-32bit switch code from asm and kernel C code
os-image: boot/boot_sect.bin kernel.bin
	cat $^ > $@

# Link C kernel code along with kernel_entry code
kernel.elf: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

# Link C kernel code along with kernel_entry code
kernel.bin: kernel/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 --oformat binary $^

# assemble kernel_entry code
%.o : %.asm
	nasm $< -f elf -o $@

# Compile kernel code
%.o : %.c
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

# Main code for initiating the kernel
%.bin: %.asm
	nasm $< -f bin -o $@ -I 'boot/'

# cleanup
clean:
	rm -fr *.bin *.o os-image *.dis
	rm -fr kernel/*.o boot/*.bin drivers/*.o

# kernel disassembly if required for debugging
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@
