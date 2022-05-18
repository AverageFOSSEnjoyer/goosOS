#include "types.h"
#include "gdt.h"
// #include "port.h"
#include "interrupt.h"

void term_scroll() {
    /* vga output pointer */
    static uint16_t* video_ptr = (uint16_t*) 0xb8000;

    /* move everything up one row */
    for (int r = 1; r <= 25; r++) {
        for (int c = 0; c <= 80; c++) {
            video_ptr[80 * (r - 1) + c] = video_ptr[80 * r + c];
        }
    }    
}

void prints(char* str) {
    /* vga output pointer */
    static uint16_t* video_ptr = (uint16_t*) 0xb8000;

    /* row and column declaration, 80 * 25 */
    static uint8_t r = 0, c = 0;

    /* print by iteration */
    for (int i = 0; str[i] != '\0'; i++) {
        /* new line */
        if (str[i] == '\n') {
            c = 0;
            if (r != 25) r++;
            else term_scroll();
            continue;
        }                          
        video_ptr[80 * r + c] = (video_ptr[i] & 0xFF00) | str[i];
        c++;
        /* end of line */
        if (c == 80) {
            c = 0;
            if (r != 25) r++;
            else term_scroll();
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
    prints("average goosOS enjoyer\nB)\n");

    global_descriptor_table gdt;

    interrupt_manager interrupt(&gdt);

    interrupt.activate();
    
    while(1);
}