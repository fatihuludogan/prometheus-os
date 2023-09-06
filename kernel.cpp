// This file contains the entry point and main functionality of the kernel.

#include "types.hpp"

// Function to print a string to the screen
void printf(const char* str){
    static uint16_t* video_memory = reinterpret_cast<uint16_t*>(0xb8000);

    for(int i = 0; str[i] != '\0'; ++i)
      video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
}

// Define a constructor function to call global constructors
using constructor = void(*)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

// Function to call global constructors
extern "C" void CallConstructors(){
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
      (*i)();
}

// Kernel entry point
extern "C" void KernelMain(void* multiboot_structure, uint32_t metric_number) {
    printf("Hello World!"); 

    while(true);
}

