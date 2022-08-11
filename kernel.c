#include "types.h"
#include "helper.h"
#include <stdio.h>

void load_gdt(gdt_t* gdt);

void load_idt(gdt_t* gdt, idt_t* idt);

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

void prints(uint8_t fg_color, uint8_t bg_color, const char* str) {
    /* video pointer in protected mode*/
    uint16_t* video_ptr = (uint16_t*) 0xB8000;

    /* row and column declaration, 25 * 80 */
    static uint8_t r = 0, c = 0;

    /* print until eos */
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n' || c >= 80) {
            c = 0;
            if (r != 25) r++;
            else term_scroll();
            if (str[i] == '\n') continue;
        }
        video_ptr[80 * r + c] = (fg_color << 8) | (bg_color << 12) | (uint16_t)str[i];
        c++;
    }
}


void kernel_main() {
    enum colors fg_color = yellow;
    enum colors bg_color = black;

    // uint8_t gdt[3 * 8];

    gdt_t gdt[1];

    load_gdt(gdt);

    idt_t idt[1];

    load_idt(idt, gdt);


    prints(fg_color, bg_color, "average goosOS enjoyer!\nB)");
    while(1);
}