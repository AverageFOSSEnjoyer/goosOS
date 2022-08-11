enum colors {
    black,
    blue,
    green,
    cyan,
    red,
    purple,
    brown,
    gray,
    dark_gray,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_purple,
    yellow,
    white
};

typedef struct __attribute__((packed, aligned(8))) gdt_t {
    uint8_t null_descriptor[8];
    uint8_t code_descriptor[8];
    uint8_t data_descriptor[8];
} gdt_t;

typedef struct __attribute__((packed, aligned(8))) idt_t {
    uint8_t keyboard[8];
} idt_t;