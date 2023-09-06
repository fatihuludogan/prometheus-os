#ifndef TYPES_HPP
#define TYPES_HPP

/**
  * @file types.hpp
  * @brief This header defines fixed-size integer types for improved portability and readability.
  */

// Define fixed-size integer types manually based on common bit sizes.
typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int int64_t;
typedef unsigned long long int uint64_t;

// Ensure the sizes match common conventions
static_assert(sizeof(int8_t) == 1, "int8_t size mismatch");
static_assert(sizeof(uint8_t) == 1, "uint8_t size mismatch");

static_assert(sizeof(int16_t) == 2, "int16_t size mismatch");
static_assert(sizeof(uint16_t) == 2, "uint16_t size mismatch");

static_assert(sizeof(int32_t) == 4, "int32_t size mismatch");
static_assert(sizeof(uint32_t) == 4, "uint32_t size mismatch");

static_assert(sizeof(int64_t) == 8, "int64_t size mismatch");
static_assert(sizeof(uint64_t) == 8, "uint64_t size mismatch");

#endif // TYPES_HPP

