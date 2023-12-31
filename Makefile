# Makefile for building the prometheus-os project.

# Compiler and linker parameters
CXX = g++
AS = as 
LD = ld

CXXFLAGS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASFLAGS = --32
LDFLAGS = -melf_i386

# List of object files to be generated
objects = loader.o gdt.o port.o kernel.o

# Rule to compile C++ source files into object files
%.o: %.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

# Rule to assemble assembly source files into object files
%.o: %.s
	${AS} $(ASFLAGS) -o $@ $<

# Rule to link object files into the final kernel binary
pro-kernel.bin: linker.ld $(objects)
	${LD} $(LDFLAGS) -T $< -o $@ $(objects)

# Rule to install the CD image of prometheus-os
pro-kernel.iso: pro-kernel.bin
	mkdir -p iso/boot/grub
	cp pro-kernel.bin iso/boot/pro-kernel.bin
	echo 'set timeout=0' 						 					 > iso/boot/grub/grub.cfg
	echo 'set default=0' 											>> iso/boot/grub/grub.cfg
	echo '' 																	>> iso/boot/grub/grub.cfg
	echo 'menuentry "prometheus-os" {' 				>> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/pro-kernel.bin' 	>> iso/boot/grub/grub.cfg
	echo '  boot'															>> iso/boot/grub/grub.cfg
	echo '}' 																	>> iso/boot/grub/grub.cfg
	grub-mkrescue --output=pro-kernel.iso iso
	rm -rf iso

# Rule to run kernel on Oracle VM VirtualBox
run: pro-kernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "prometheus-os" &

# Rule to install the kernel binary to the /boot directory
install: pro-kernel.bin
	sudo cp $< /boot/pro-kernel.bin

.PHONY: clean
clean:
	rm -f $(objects) pro-kernel.bin pro-kernel.iso
