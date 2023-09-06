# Makefile for building the prometheus-os project.

# Compiler and linker parameters
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

# List of object files to be generated
objects = loader.o kernel.o

# Rule to compile C++ source files into object files
%.o: %.cpp
	g++ $(GPPPARAMS) -c -o $@ $<

# Rule to assemble assembly source files into object files
%.o: %.s
	as $(ASPARAMS) -o $@ $<

# Rule to link object files into the final kernel binary
pro-kernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

# Rule to install the kernel binary to the /boot directory
install: pro-kernel.bin
	sudo cp $< /boot/pro-kernel.bin

