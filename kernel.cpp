#include "types.h"

void println(char* str) {
    /* vga output pointer */
    static uint16_t* video_ptr = (uint16_t*) 0xb8000;

    /* print by iteration */
    for (int i = 0; str[i] != '\0'; i++) {                          
        video_ptr[i] = (video_ptr[i] & 0xFF00) | str[i];
    }

    /* next line */
    video_ptr = video_ptr + 0x000a0;
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernel_main(void* multiboot_structure, unsigned int magic_number) {
    println("average GoosOS enjoyer");
    while(1);
}