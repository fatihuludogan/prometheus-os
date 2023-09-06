# Linker script for kernel compilation.

# Entry point for kernel.
ENTRY(loader)

# Output format and architecture
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

# Define memory sections for the kernel
SECTIONS
{
  . = 0x0100000;

  .text :
  {
    *(.multiboot)
    *(.text*)
    *(.rodata)
  }

  .data :
  {
    start_ctors = .;
    KEEP(*( .init_array ));
    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
    end_ctors = .;

    *(.data)
  }

  .bss :
  {
    *(.bss)
  }
  
  # Discard unnecessary sections
  /DISCARD/ : { *(.fini_array*) *(.comment) }
}

