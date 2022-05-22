CFLAGS = -m32 -std=gnu99 -Wall -Wextra -Werror -fno-stack-protector
AFLAGS = --32
BFLAGS = -m32 -ffreestanding -O2 -nostdlib -lgcc
OBJ = kernel.o boot.o gdt.o

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

%.o: %.s
	as $< -o $@ $(AFLAGS)

goosOS.bin: $(OBJ)
	gcc -T linker.ld -o $@ $(BFLAGS) $(OBJ) 

goosOS.iso:
	mkdir -p ./iso/boot/grub
	echo 'menuentry "goosOS" {			' >> ./iso/boot/grub/grub.cfg
	echo '	multiboot /boot/goosOS.bin	' >> ./iso/boot/grub/grub.cfg
	echo '}								' >> ./iso/boot/grub/grub.cfg
	mv ./goosOS.bin ./iso/boot/goosOS.bin
	grub-mkrescue -o goosOS.iso ./iso
	rm -rf ./iso

all:
	make $(OBJ)
	make goosOS.bin
	make goosOS.iso

run:
	qemu-system-i386 -cdrom ./goosOS.iso &

clean:
	-rm *.o *.iso