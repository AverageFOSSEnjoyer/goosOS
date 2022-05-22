#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupt.h"
#include "port.h"

class mouse_driver : public interrupt_handler {
    port_8bit data_port;
    port_8bit command_port;

    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;

    public:
        mouse_driver(interrupt_manager* manager);
        ~mouse_driver();
        virtual uint32_t handle_interrupt(uint32_t esp);
};

#endif