#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupt.h"
#include "port.h"

class keyboard_driver : public interrupt_handler {
    port_8bit data_port;
    port_8bit command_port;

    public:
        keyboard_driver(interrupt_manager* manager);
        ~keyboard_driver();
        virtual uint32_t handle_interrupt(uint32_t esp);
        virtual uint8_t keymap(uint8_t key);
};

#endif