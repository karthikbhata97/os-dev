# $^ all dependencies
# $< first dependencies
# $@ target file
C_SOUCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOUCES:.c=.o}

# Default, create os-image and run
all: os-image

run: all
	bochs

# Create os image from 16bit-32bit switch code from asm and kernel C code
os-image: boot/boot_sect.bin kernel.bin
	cat $^ > $@

# Link C kernel code along with kernel_entry code
kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 --oformat binary -m elf_i386 $^

# assemble kernel_entry code
%.o : %.asm
	nasm $< -f elf -o $@

# Compile kernel code
%.o : %.c
	gcc -ffreestanding -c $< -o $@ -m32 -fno-pie

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
