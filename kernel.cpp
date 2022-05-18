#include "types.h"
#include "gdt.h"

void prints(char* str) {
    /* vga output pointer */
    static uint16_t* video_ptr = (uint16_t*) 0xb8000;

    /* row and column declaration, 80 * 25 */
    static uint8_t r = 0, c = 0;

    /* print by iteration */
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            c = 0;
            r++;
            continue;
        }                          
        video_ptr[80 * r + c] = (video_ptr[i] & 0xFF00) | str[i];
        c++;
        if (c == 80) {
            c = 0;
            r++;
        }
    }
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
    prints("average goosOS enjoyer\nB)");

    global_descriptor_table gdt;

    while(1);
}