#include "port.h"

port::port(uint16_t port_number) {
    this->port_number = port_number;
}

port::~port() {}

port_8bit::port_8bit(uint16_t port_number) : port(port_number) {}

port_8bit::~port_8bit() {}

void port_8bit::write(uint8_t data) {
    __asm__ volatile (
        "outb %0, %1" 
        : // outputs
        
        : // inputs
        "a" (data), "Nd" (port_number)
    );
}

uint8_t port_8bit::read() {
    uint8_t result;
    __asm__ volatile (
        "inb %1, %0" 
        : // outputs
        "=a" (result) 
        : //inputs
        "Nd" (port_number)
    );
    return result;
}

port_8bit_slow::port_8bit_slow(uint16_t port_number) : port_8bit(port_number) {}

port_8bit_slow::~port_8bit_slow() {}

void port_8bit_slow::write(uint8_t data) {
    __asm__ volatile (
        "outb %0, %1\n"
        "jmp 1f\n"
        "1: jmp 1f\n"
        "1:\n" 
        : // outputs
        
        : // inputs
        "a" (data), "Nd" (port_number)
    );
}

port_16bit::port_16bit(uint16_t port_number) : port(port_number) {}

port_16bit::~port_16bit() {}

void port_16bit::write(uint16_t data) {
    __asm__ volatile (
        "outw %0, %1" 
        : // outputs
        
        : // inputs
        "a" (data), "Nd" (port_number)
    );
}

uint16_t port_16bit::read() {
    uint16_t result;
    __asm__ volatile (
        "inw %1, %0" 
        : // outputs
        "=a" (result) 
        : //inputs
        "Nd" (port_number)
    );
    return result;
}

port_32bit::port_32bit(uint16_t port_number) : port(port_number) {}

port_32bit::~port_32bit() {}

void port_32bit::write(uint32_t data) {
    __asm__ volatile (
        "outl %0, %1" 
        : // outputs
        
        : // inputs
        "a" (data), "Nd" (port_number)
    );
}

uint32_t port_32bit::read() {
    uint32_t result;
    __asm__ volatile (
        "inl %1, %0" 
        : // outputs
        "=a" (result) 
        : //inputs
        "Nd" (port_number)
    );
    return result;
}