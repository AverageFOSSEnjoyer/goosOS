#include "types.h"
#include "helper.h"

/*  Gate Descriptor Layout
    |------------------| 63
    | 7 |              |
    |---|    Offset    |
    | 6 |              |
    |------------------| 47/48
    | 5 |   P/DPL/0    |
    |---|              | 
    |   |   Gate Type  |
    |------------------| 39/40
    | 4 |   Reserved   |
    |---|--------------| 31/32
    | 3 | Code Segment |
    |---|   Selector   |
    | 2 |              |
    |------------------| 15/16
    | 1 |              |
    |---|    Offset    |
    | 0 |              |
    |------------------| 0
*/


void load_idt(gdt_t* gdt, idt_t* idt) {
    idt[0] = 
}