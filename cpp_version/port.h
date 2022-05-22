#ifndef __PORT_H
#define __PORT_H
#include "types.h"

class port {
    protected:
        uint16_t port_number;
        port(uint16_t port_number);
        ~port();
};

class port_8bit : public port {
    public:
        port_8bit(uint16_t port_number);
        ~port_8bit();
        virtual void write(uint8_t data);
        virtual uint8_t read();
};

class port_8bit_slow : public port_8bit {
    public:
        port_8bit_slow(uint16_t port_number);
        ~port_8bit_slow();
        virtual void write(uint8_t data);
};

class port_16bit : public port {
    public:
        port_16bit(uint16_t port_number);
        ~port_16bit();
        virtual void write(uint16_t data);
        virtual uint16_t read();
};

class port_32bit : public port {
    public:
        port_32bit(uint16_t port_number);
        ~port_32bit();
        virtual void write(uint32_t data);
        virtual uint32_t read();
};

#endif