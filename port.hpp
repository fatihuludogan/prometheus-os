#ifndef PORT_HPP
#define PORT_HPP

#include "types.hpp"

class Port {
protected:
    Port (uint16_t port_number) : port_number(port_number) {};
    ~Port() = default;
    uint16_t port_number;
};

class Port8Bit : public Port {
public:
    Port8Bit(uint16_t port_number);
    ~Port8Bit() = default;

    virtual uint8_t Read();
    virtual void Write(uint8_t data);

protected:
    static inline uint8_t Read8(uint16_t _port) {
        uint8_t result;
        __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write8(uint16_t _port, uint8_t _data) {
        __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
    }
};

class Port8BitSlow : public Port8Bit {
public:
    Port8BitSlow(uint16_t port_number);
    ~Port8BitSlow() = default;

    virtual void Write(uint8_t data);

protected:
    static inline void Write8Slow(uint16_t _port, uint8_t _data) {
        __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
    }
};

class Port16Bit : public Port {
public:
    Port16Bit(uint16_t port_number);
    ~Port16Bit() = default;

    virtual uint16_t Read();
    virtual void Write(uint16_t data);

protected:
    static inline uint16_t Read16(uint16_t _port) {
        uint16_t result;
        __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write16(uint16_t _port, uint16_t _data) {
        __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
    }
};

class Port32Bit : public Port {
public:
    Port32Bit(uint16_t port_number);
    ~Port32Bit() = default;

    virtual uint32_t Read();
    virtual void Write(uint32_t data);

protected:
    static inline uint32_t Read32(uint16_t _port) {
        uint32_t result;
        __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write32(uint16_t _port, uint32_t _data) {
        __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
    }
};

#endif  // PORT_HPP

