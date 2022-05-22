#include "types.h"

/*  Segment Descriptor Layout
    |------------------|
    | 7 |   base_high  |
    |------------------|
    | 6 |    flags     |
    |------------------|
    |   |  limit_high  |
    |------------------|
    | 5 |    access    |
    |------------------|
    | 4 |   base_mid   |
    |------------------|
    | 3 |   base_low   |
    |---|              |
    | 2 |              |
    |------------------|
    | 1 |    limit     |
    |---|              |
    | 0 |              |
    |------------------|
*/

#ifndef __GDT_H
#define __GDT_H                               
    class global_descriptor_table {
    public:
        class segment_descriptor {
            private:
                uint16_t limit_low;
                uint16_t base_low;
                uint8_t base_mid;
                uint8_t access;
                uint8_t flags;
                uint8_t base_high;
            public:
                segment_descriptor(uint32_t base, uint32_t limit, uint8_t access);
                uint32_t base();
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