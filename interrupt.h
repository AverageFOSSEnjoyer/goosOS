#include "types.h"
#include "port.h"
#include "gdt.h"

#ifndef __INTERRUPT_H
#define __INTERRUPT_H

class interrupt_manager {
    protected:
        struct gate_descriptor {
            uint16_t handler_address_low;
            uint16_t gdt_code_segment_selector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handler_address_high;
        } __attribute__((packed));

        static gate_descriptor interrupt_descriptor_table[256];

        struct interrupt_descriptor_table_pointer {
            uint16_t size;
            uint32_t base;
        } __attribute__((packed));

        static void set_interrupt_descriptor_table_entry(
            uint8_t interrupt_number, 
            uint16_t code_segment_selector_offset,
            void (*handler)(),
            uint8_t descriptor_privilege_level,
            uint8_t descriptor_type
        );

        port_8bit_slow pic_master_command;
        port_8bit_slow pic_master_data;
        port_8bit_slow pic_slave_command;
        port_8bit_slow pic_slave_data;

    public:
        interrupt_manager(global_descriptor_table* gdt);
        ~interrupt_manager();

        static uint32_t handle_interrupt(uint8_t interrupt_number, uint32_t esp);
        static void ignore_interrupt_request();
        static void handle_interrupt_request0x00();
        static void handle_interrupt_request0x01();
        static void activate();
};

#endif