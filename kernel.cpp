// This file contains the entry point and main functionality of the kernel.

#include "types.hpp"
#include "gdt.hpp"

// Function to print a string to the screen
void printf(const char* str){
    static auto* video_memory = reinterpret_cast<uint16_t*>(0xb8000);

    static uint8_t x = 0, y = 0;

    for(int i = 0; str[i] != '\0'; ++i) {
        switch(str[i]) {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                video_memory[80*y+x] = (video_memory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if (x >= 30) {
            x = 0;
            y++;
        }

        if (y >= 25) {
            for (y = 0; y < 25; y++)
                for (x = 0; x < 80; x++)
                    video_memory[80*y+x] = (video_memory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

// Define a constructor function to call global constructors
using constructor = void(*)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

// Function to call global constructors
extern "C" void call_constructors(){
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
      (*i)();
}

// Kernel entry point
extern "C" void kernel_main(void* multiboot_structure, uint32_t metric_number) {
    printf("Hello World!"); 

    GlobalDescriptorTable gdt;

    while(true);
}

