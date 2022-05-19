#include "keyboard.h"

void prints(char* str);

keyboard_driver::keyboard_driver(interrupt_manager* manager) :
    interrupt_handler(0x21, manager),
    data_port(0x60),
    command_port(0x64) 
{
    while(command_port.read() & 0x1) {
        data_port.read();
    }
    command_port.write(0xAE);   // activate interrupts
    command_port.write(0x20);   // get current state
    uint8_t status = (data_port.read() | 1) & ~0x10;
    command_port.write(0x60);   //set state
    data_port.write(status);

    data_port.write(0xF4);      // activate keyboard
}

keyboard_driver::~keyboard_driver() {}

uint32_t keyboard_driver::handle_interrupt(uint32_t esp) {
    uint8_t key = data_port.read();

    

    // if (key < 0x80) {
        char* out = " \0";
        out[0] = keymap(key);
        prints(out);
        // char* msg = "0x00\n";
        // char* hex = "0123456789ABCDEF";
        // msg[2] = hex[(key >> 4) & 0x0F];
        // msg[3] = hex[key & 0x0F];
        // prints(msg);
    // }

    return esp;
}

uint8_t keyboard_driver::keymap(uint8_t key) {
    static uint8_t caps = 0;
    static uint8_t shift_left = 0;
    static uint8_t shift_right = 0;
    static uint8_t shift = 0;

    /* caps lock pressed */
    if (key == 0x3A) {
        caps = !caps;
        return 0x00;    // \0
    }

    /* upper lower independent */
    switch (key) {
        case 0x2A:
            shift_left = 1;
            return 0x00;    // \0
        case 0x36:
            shift_right = 1;
            return 0x00;    // \0   
        case 0xAA:
            shift_left = 0;
            return 0x00;    // \0
        case 0xB6:
            shift_right = 0;
            return 0x00;    // \0
        case 0x1C:
            return 0x0A;    // \n
        case 0x0E:
            return 0x08;    // backspace
        case 0x39:
            return 0x20;    // space
        case 0x37:
            return 0x2A;    // *
        case 0x4A:
            return 0x2D;    // -
        case 0x4E:
            return 0x2B;    // +
        case 0x47:
            return 0x37;    // 7
        case 0x48:
            return 0x38;    // 8
        case 0x49:
            return 0x39;    // 9
        case 0x4B:
            return 0x34;    // 4
        case 0x4C:
            return 0x35;    // 5
        case 0x4D:
            return 0x36;    // 6
        case 0x4F:
            return 0x31;    // 1
        case 0x50:
            return 0x32;    // 2
        case 0x51:
            return 0x33;    // 3
        case 0x52:
            return 0x30;    // 0
        case 0x53:
            return 0x2E;    // .
    }

    shift = shift_left || shift_right;

    /* lowercase */
    if (caps == 0  && shift == 0) {
        /* numbers 1-9 */
        if (0x02 <= key && key <= 0x0A) {
            return (key & 0xF) + 47;
        }
        switch (key) {
            case 0x0B:
                return 0x30;    // 0
            case 0x0C:
                return 0x2D;    // -
            case 0x0D:
                return 0x3D;    // =
            case 0x10:
                return 0x71;    // q
            case 0x11:
                return 0x77;    // w
            case 0x12:
                return 0x65;    // e
            case 0x13:
                return 0x72;    // r
            case 0x14:
                return 0x74;    // t
            case 0x15:
                return 0x79;    // y
            case 0x16:
                return 0x75;    // u
            case 0x17:
                return 0x69;    // i
            case 0x18:
                return 0x6F;    // o
            case 0x19:
                return 0x70;    // p
            case 0x1A:
                return 0x5B;    // [
            case 0x1B:
                return 0x5D;    // ]
            case 0x1E:
                return 0x61;    // a
            case 0x1F:
                return 0x73;    // s
            case 0x20:
                return 0x64;    // d
            case 0x21:
                return 0x66;    // f
            case 0x22:
                return 0x67;    // g
            case 0x23:
                return 0x68;    // h
            case 0x24:
                return 0x6A;    // j
            case 0x25:
                return 0x6B;    // k
            case 0x26:
                return 0x6C;    // l
            case 0x27:
                return 0x3B;    // ;
            case 0x28:
                return 0x27;    // '
            case 0x29:
                return 0x60;    // `
            case 0x2B:
                return 0x5C;    // "\"
            case 0x2C:
                return 0x7A;    // z
            case 0x2D:
                return 0x78;    // x
            case 0x2E:
                return 0x63;    // c
            case 0x2F:
                return 0x76;    // v
            case 0x30:
                return 0x62;    // b
            case 0x31:
                return 0x6E;    // n
            case 0x32:
                return 0x6D;    // m
            case 0x33:
                return 0x2C;    // ,
            case 0x34:
                return 0x2E;    // .
            case 0x35:
                return 0x2F;    // /
        }
    }

    if (caps == 1 || shift == 1) {
        switch (key) {
            case 0x10:
                return 0x51;    // Q
            case 0x11:
                return 0x57;    // W
            case 0x12:
                return 0x45;    // E
            case 0x13:
                return 0x52;    // R
            case 0x14:
                return 0x54;    // T
            case 0x15:
                return 0x59;    // Y
            case 0x16:
                return 0x55;    // U
            case 0x17:
                return 0x49;    // I
            case 0x18:
                return 0x4F;    // O
            case 0x19:
                return 0x50;    // P
            case 0x1E:
                return 0x41;    // A
            case 0x1F:
                return 0x53;    // S
            case 0x20:
                return 0x44;    // D
            case 0x21:
                return 0x46;    // F
            case 0x22:
                return 0x47;    // G
            case 0x23:
                return 0x48;    // H
            case 0x24:
                return 0x4A;    // J
            case 0x25:
                return 0x4B;    // K
            case 0x26:
                return 0x4C;    // L
            case 0x2C:
                return 0x5A;    // Z
            case 0x2D:
                return 0x58;    // X
            case 0x2E:
                return 0x43;    // C
            case 0x2F:
                return 0x56;    // V
            case 0x30:
                return 0x42;    // B
            case 0x31:
                return 0x4E;    // N
            case 0x32:
                return 0x4D;    // M
        }
    } 

    if (caps == 1) {
        /* numbers 1-9 */
        if (0x02 <= key && key <= 0x0A) {
            return (key & 0xF) + 47;
        }
        switch (key) {
            case 0x0B:
                return 0x30;    // 0
            case 0x0C:
                return 0x2D;    // -
            case 0x0D:
                return 0x3D;    // =
            case 0x1A:
                return 0x5B;    // [
            case 0x1B:
                return 0x5D;    // ]
            case 0x27:
                return 0x3B;    // ;
            case 0x28:
                return 0x27;    // '
            case 0x29:
                return 0x60;    // `
            case 0x2B:
                return 0x5C;    // "\"
            case 0x33:
                return 0x2C;    // ,
            case 0x34:
                return 0x2E;    // .
            case 0x35:
                return 0x2F;    // /
        }
    }

    if (shift == 1) {
        switch (key) {
            case 0x29:
                return 0x7E;    // ~
            case 0x02:
                return 0x21;    // !
            case 0x03:
                return 0x40;    // @
            case 0x04:
                return 0x23;    // #
            case 0x05:
                return 0x24;    // $
            case 0x06:
                return 0x25;    // %
            case 0x07:
                return 0x5E;    // ^
            case 0x08:
                return 0x26;    // &
            case 0x09:
                return 0x2A;    // *
            case 0x0A:
                return 0x28;    // (
            case 0x0B:
                return 0x29;    // )
            case 0x0C:
                return 0x5F;    // _
            case 0x0D:
                return 0x2B;    // +
            case 0x1A:
                return 0x7B;    // {
            case 0x1B:
                return 0x7D;    // }
            case 0x2B:
                return 0x7C;    // |
            case 0x27:
                return 0x3A;    // :
            case 0x28:
                return 0x22;    // "
            case 0x33:
                return 0x3C;    // <
            case 0x34:
                return 0x3E;    // >
            case 0x35:
                return 0x3F;    // ?
        }
    }
    return 0x00;
}