/* datatype length failsafe */
#include "types.h"
#ifndef __GDT_H
#define __GDT_H                               
    class global_descriptor_table {
    public:
        class segment_descriptor {
            private:
                uint16_t limit_low;
                uint16_t ptr_low;
                uint8_t ptr_mid;
                uint8_t access;
                uint8_t flags;
                uint8_t ptr_high;
            public:
                segment_descriptor(uint32_t ptr, uint32_t limit, uint8_t access);
                uint32_t ptr();
                uint32_t limit();
        }   __attribute__((packed));

        segment_descriptor null_segment_selector;
        segment_descriptor unused_segment_selector;
        segment_descriptor code_segment_selector;
        segment_descriptor data_segement_selector;

    public:
        global_descriptor_table();
        ~global_descriptor_table();

        uint16_t _code_segment_selector();
        uint16_t _data_segement_selector();
    };
#endif