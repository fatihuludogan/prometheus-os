// This file contains the entry point and main functionality of the kernel.

// Function to print a string to the screen
void printf(char* str){
  static unsigned short* video_memory = (unsigned short*)0xb8000;

  // Loop through the string and write characters to video memory
  for(int i = 0; str[i] != '\0'; ++i)
    video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
}

// Define a constructor function to call global constructors
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

// Function to call global constructors
extern "C" void CallConstructors(){
  for(constructor* i = &start_ctors; i != &end_ctors; i++)
    (*i)();
}

// Kernel entry point
extern "C" void KernelMain(void* multiboot_structure, unsigned int metric_number) {
  // Print a "Hello World!" message to the screen to test our kernel
    printf("Hello World!"); 

  // Enter an infinite loop to keep the kernel running
    while(1);
}

