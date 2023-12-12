#include "gdt.hpp"

GlobalDescriptorTable::GlobalDescriptorTable()
    : nullSegmentSelector(0, 0, 0),
      unusedSegmentSelector(0, 0, 0),
      codeSegmentSelector(0, 64 * 1024 * 1024, 0x9A),
      dataSegmentSelector(0, 64 * 1024 * 1024, 0x92) {
    uint32_t i[2];
    i[1] = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this));
    i[0] = sizeof(GlobalDescriptorTable) << 16;
    asm volatile("lgdt (%0)" : : "p"(((uint8_t*)i) + 2));
}

auto GlobalDescriptorTable::DataSegmentSelector() const -> uint16_t {
    return static_cast<uint16_t>(reinterpret_cast<uintptr_t>(&dataSegmentSelector) -
                                 reinterpret_cast<uintptr_t>(this));
}

auto GlobalDescriptorTable::CodeSegmentSelector() const -> uint16_t {
    return static_cast<uint16_t>(reinterpret_cast<uintptr_t>(&codeSegmentSelector) -
                                 reinterpret_cast<uintptr_t>(this));
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uintptr_t base, uintptr_t limit, uint8_t type) {
    auto* target = reinterpret_cast<uint8_t*>(this);

    if (limit <= 65536) {
        // 16-bit address space
        target[6] = 0x40;
    } else {
        if ((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12) - 1;
        else
            limit = limit >> 12;

        target[6] = 0xC0;
    }

    // Encode the limit
    target[0] = static_cast<uint8_t>(limit & 0xFF);
    target[1] = static_cast<uint8_t>((limit >> 8) & 0xFF);
    target[6] |= static_cast<uint8_t>((limit >> 16) & 0xF);

    // Encode the base
    target[2] = static_cast<uint8_t>(base & 0xFF);
    target[3] = static_cast<uint8_t>((base >> 8) & 0xFF);
    target[4] = static_cast<uint8_t>((base >> 16) & 0xFF);
    target[7] = static_cast<uint8_t>((base >> 24) & 0xFF);

    // Type
    target[5] = type;
}

auto GlobalDescriptorTable::SegmentDescriptor::Base() const -> uintptr_t {
    const uint8_t* target = reinterpret_cast<const uint8_t*>(this);

    uintptr_t result = static_cast<uintptr_t>(target[7]);
    result = (result << 8) + static_cast<uintptr_t>(target[4]);
    result = (result << 8) + static_cast<uintptr_t>(target[3]);
    result = (result << 8) + static_cast<uintptr_t>(target[2]);

    return result;
}

auto GlobalDescriptorTable::SegmentDescriptor::Limit() const -> uintptr_t {
    const auto* target = reinterpret_cast<const uint8_t*>(this);

    auto result = static_cast<uintptr_t>(target[6] & 0xF);
    result = (result << 8) + static_cast<uintptr_t>(target[1]);
    result = (result << 8) + static_cast<uintptr_t>(target[0]);

    if ((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;
}

