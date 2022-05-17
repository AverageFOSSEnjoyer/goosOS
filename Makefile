CFLAGS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
SFLAGS = --32
LFLAGS = -melf_i386
OBJ = loader.o kernel.o

%.o: %.cpp
	g++ $(CFLAGS) -o $@ -c $<

%.o: %.s
	as $(SFLAGS) -o $@ $<

mykernel.bin: linker.ld $(OBJ)
	ld $(LFLAGS) -T $< -o $@ $(OBJ)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=1						' >> iso/boot/grub/grub.cfg
	echo 'set default=0						' >> iso/boot/grub/grub.cfg
	echo '									' >> iso/boot/grub/grub.cfg
	echo 'menuentry "GoosOS" {				' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin	' >> iso/boot/grub/grub.cfg
	echo '	boot							' >> iso/boot/grub/grub.cfg
	echo '}									' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

all: kernel.cpp loader.s linker.ld
	make kernel.o
	make loader.s
	make mykernel.bin
	make mykernel.iso

run:
	-killall qemu-system-i386
	sleep 1
	qemu-system-i386 -cdrom ./mykernel.iso &

clean:
	-rm *.o;
	-rm *.bin;
	-rm *.iso;
	-rm -rf ./iso;