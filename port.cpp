#include "port.hpp"

Port::Port(uint16_t port_number) {
    this->port_number = port_number;
}

Port::~Port() {}



Port8Bit::Port8Bit(uint16_t port_number)
    : Port(port_number) {}

Port8Bit::~Port8Bit() {}

void Port8Bit::Write(uint8_t data) {
    Write8(port_number, data);
}

uint8_t Port8Bit::Read() {
    return Read8(port_number);
}



Port8BitSlow::Port8BitSlow(uint16_t port_number) 
    : Port8Bit(port_number) {}

Port8BitSlow::~Port8BitSlow() {}

void Port8BitSlow::Write(uint8_t data) {
    Write8Slow(port_number, data);
}



Port16Bit::Port16Bit(uint16_t port_number)
    : Port(port_number) {}

Port16Bit::~Port16Bit() {}

void Port16Bit::Write(uint16_t data) {
    Write16(port_number, data);
}

uint16_t Port16Bit::Read() {
    return Read16(port_number);
}



Port32Bit::Port32Bit(uint16_t port_number) 
    : Port(port_number) {}

Port32Bit::~Port32Bit() {}

void Port32Bit::Write(uint32_t data) {
    Write32(port_number, data);
}

uint32_t Port32Bit::Read() {
    return Read32(port_number);
}

