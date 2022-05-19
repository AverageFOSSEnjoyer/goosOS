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

    

    if (key < 0x80) {

        prints(keymap(key));
        // char* msg = "KEYBOARD 0x00\n";
        // char* hex = "0123456789ABCDEF";
        // msg[11] = hex[(key >> 4) & 0x0F];
        // msg[12] = hex[key & 0x0F];
        // prints(msg);
    }

    return esp;
}

char* keyboard_driver::keymap(uint8_t key) {
    char* button = " \0";
    if (0x02 <= key && key <= 0x0A) {

        button[0] = (key & 0xF) + 47;
        return button;
    }
    switch (key) {
        case 0x0B:
            return "0";
        case 0x0E:
            button[0] = 0x08;
            return button;    // backspace
        case 0x10:
            return "q";
        case 0x11:
            return "w";
        case 0x12:
            return "e";
        case 0x13:
            return "r";
        case 0x14:
            return "t";
        case 0x15:
            return "y";
        case 0x16:
            return "u";
        case 0x17:
            return "i";
        case 0x18:
            return "o";
        case 0x19:
            return "p";
        case 0x1A:
            return "[";
        case 0x1B:
            return "]";
        case 0x1C:
            return "\n";
        case 0x1E:
            return "a";
        case 0x1F:
            return "s";
        case 0x20:
            return "d";
        case 0x21:
            return "f";
        case 0x22:
            return "g";
        case 0x23:
            return "h";
        case 0x24:
            return "j";
        case 0x25:
            return "k";
        case 0x26:
            return "l";
        case 0x27:
            return ";";
        case 0x28:
            return "'";
        case 0x29:
            return "`";
        case 0x2B:
            return "\\";
        case 0x2C:
            return "z";
        case 0x2D:
            return "x";
        case 0x2E:
            return "c";
        case 0x2F:
            return "v";
        case 0x30:
            return "b";
        case 0x31:
            return "n";
        case 0x32:
            return "m";
        case 0x33:
            return ",";
        case 0x34:
            return ".";
        case 0x35:
            return "/";
        case 0x39:
            return " ";
    }
}