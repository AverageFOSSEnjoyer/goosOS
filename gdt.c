#include "types.h"
#include "helper.h"

/*  Segment Descriptor Layout
    |------------------| 63
    | 7 |   base_high  |
    |------------------| 55/56
    | 6 |    flags     |
    |------------------| 51/52
    |   |  limit_high  |
    |------------------| 47/48
    | 5 |    access    |
    |------------------| 39/40
    | 4 |              |
    |---|              |
    | 3 |   base_low   |
    |---|              |
    | 2 |              |
    |------------------| 15/16
    | 1 |              |
    |---|  limit_low   |
    | 0 |              |
    |------------------| 0
*/
uint32_t __stack_chk_fail_local(){
    return 0;
}

void create_descriptor(uint8_t* ptr, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    ptr[0] = limit & 0xFF;

    ptr[1] = (limit >> 8) & 0xFF;
    
    ptr[2] = base & 0xFF;
    ptr[3] = (base >> 8) & 0xFF;
    ptr[4] = (base >> 16) & 0xFF;

    ptr[5] = access;

    ptr[6] = ((limit >> 16) & 0x0F) | (flags << 4);

    ptr[7] = (base >> 24) & 0xFF;
}

void load_gdt(gdt_t* gdt) {
    /* null descriptor */
    create_descriptor(gdt->null_descriptor, 0, 0x00000, 0x00, 0x0);
    
    /* code descriptor */
    create_descriptor(gdt->code_descriptor, 0, 0xFFFFF, 0x9A, 0xC);

    /* data descriptor */
    create_descriptor(gdt->data_descriptor, 0, 0xFFFFF, 0x92, 0xC);

    uint32_t i[2];
    i[1] = (uint32_t)gdt;
    i[0] = sizeof(gdt_t) - 1;

    __asm__ volatile(
        "lgdt (%0)"
        :

        :
        "p" (((uint8_t*)i) + 2)
    );
}