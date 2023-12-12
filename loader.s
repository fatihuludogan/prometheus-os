# Assembly code for kernel loading and initialization

# Multiboot header values
.set METRIC_NUM, 0x1badb002     # metric number for bootloader to recognize kernel as a actually kernel
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(METRIC_NUM + FLAGS)

# Define the .multiboot section with Multiboot header
.section .multiboot
    .long METRIC_NUM
    .long FLAGS
    .long CHECKSUM

# Define the .text section
.section .text
.extern kernel_main
.extern call_constructors
.global loader

# Entry point for the kernel loader
loader:
    mov $kernel_stack, %esp
    call call_constructors
    push %eax
    push %ebx
    call kernel_main

# Halt the CPU
stop:
    cli
    hlt

# Define the .bss section for kernel stack
.section .bss
.space 2*1024*1024  # Reserve 2 MiB of space for the kernel stack
kernel_stack:

