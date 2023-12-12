#include "port.hpp"

Port8Bit::Port8Bit(uint16_t port_number)
    : Port(port_number) {}

void Port8Bit::Write(uint8_t data) {
    Write8(port_number, data);
}

auto Port8Bit::Read() -> uint8_t{
    return Read8(port_number);
}

Port8BitSlow::Port8BitSlow(uint16_t port_number) 
    : Port8Bit(port_number) {}

void Port8BitSlow::Write(uint8_t data) {
    Write8Slow(port_number, data);
}

Port16Bit::Port16Bit(uint16_t port_number)
    : Port(port_number) {}

void Port16Bit::Write(uint16_t data) {
    Write16(port_number, data);
}

auto Port16Bit::Read() -> uint16_t {
    return Read16(port_number);
}

Port32Bit::Port32Bit(uint16_t port_number) 
    : Port(port_number) {}


void Port32Bit::Write(uint32_t data) {
    Write32(port_number, data);
}

auto Port32Bit::Read() -> uint32_t {
    return Read32(port_number);
}

