#include "mouse.h"

void prints(char* str);

mouse_driver::mouse_driver(interrupt_manager* manager) :
    interrupt_handler(0x2C, manager),
    data_port(0x60),
    command_port(0x64) 
{
    offset = 0;
    buttons = 0;

    static uint16_t* video_ptr = (uint16_t*) 0xb8000;

    video_ptr[80 * 12 + 40] = ((video_ptr[80 * 12 + 40] & 0xF000) >> 4)
                          | ((video_ptr[80 * 12 + 40] & 0x0F00) << 4)
                          | ((video_ptr[80 * 12 + 40] & 0x00FF));

    command_port.write(0xA8);   // activate interrupts
    command_port.write(0x20);   // get current state
    uint8_t status = data_port.read() | 2;
    command_port.write(0x60);   //set state
    data_port.write(status);

    command_port.write(0xD4);
    data_port.write(0xF4);      // activate mouse
    data_port.read();
}

mouse_driver::~mouse_driver() {}

uint32_t mouse_driver::handle_interrupt(uint32_t esp) {
    uint8_t status = command_port.read();
    if (!(status & 0x20)) {
        return esp;
    }

    static int8_t r = 12, c = 40;

    buffer[offset] = data_port.read();
    offset = (offset + 1) % 3;

    if (offset == 0) {
        static uint16_t* video_ptr = (uint16_t*) 0xb8000;

        video_ptr[80 * r + c] = ((video_ptr[80 * r + c] & 0xF000) >> 4)
                              | ((video_ptr[80 * r + c] & 0x0F00) << 4)
                              | ((video_ptr[80 * r + c] & 0x00FF));

        r -= buffer[2];
        c += buffer[1];

        if (r < 0) c = 0;
        if (r > 24) r = 24;

        if (c < 0) c = 0;
        if (c > 79) c = 79;

        video_ptr[80 * r + c] = ((video_ptr[80 * r + c] & 0xF000) >> 4)
                              | ((video_ptr[80 * r + c] & 0x0F00) << 4)
                              | ((video_ptr[80 * r + c] & 0x00FF));

        for (uint8_t i = 0; i < 3; i++) {
            if ((buffer[0] & (0x01 << i)) != (buttons & (0x01 << i))) {
                video_ptr[80 * r + c] = ((video_ptr[80 * r + c] & 0xF000) >> 4)
                                      | ((video_ptr[80 * r + c] & 0x0F00) << 4)
                                      | ((video_ptr[80 * r + c] & 0x00FF));
            }
        }
    }



    return esp;
}