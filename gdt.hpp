#ifndef GDT_HPP
#define GDT_HPP

#include "types.hpp"

class GlobalDescriptorTable
{    
    public:
        class SegmentDescriptor
        {
            private:
                uint16_t limit_lo;
                uint16_t base_lo;
                uint8_t base_hi;
                uint8_t type;
                uint8_t limit_hi;
                uint8_t base_vhi;

            public:
                SegmentDescriptor(uintptr_t base, uintptr_t limit, uint8_t type);
                uintptr_t Base() const;
                uintptr_t Limit() const;
        } __attribute__((packed));  // It should be byte perfect

    private:
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        uint16_t CodeSegmentSelector() const;
        uint16_t DataSegmentSelector() const;
};

#endif  // GDT_HPP

