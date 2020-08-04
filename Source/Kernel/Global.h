#pragma once
#include <cstdint>
#include <cstddef>

template<char... digits>
struct LiteralToBinary;

template<char value, char... digits>
struct LiteralToBinary<value, digits...>
{
    static_assert(value == '0' || value == '1', "A binary literal can only consist of the characters '0' or '1'.");
    static const int Value = (value - '0') * (1 << sizeof...(digits)) + LiteralToBinary<digits...>::Value;
};

template<char value>
struct LiteralToBinary<value>
{
    static_assert(value == '0' || value == '1', "A binary literal can only consist of the characters '0' or '1'.");
    static const int Value = value - '0';
};

template<char... digits>
constexpr int operator "" _b()
{
    return LiteralToBinary<digits...>::Value;
}

namespace Kernel
{
    typedef void* LogicalAddress;
    typedef void* LinearAddress;
    typedef void* PhysicalAddress;

    enum class RingLevel
    {
        Kernel = 0x0,
        User = 0x3,
        Ring0 = Kernel,
        Ring1 = 0x1,
        Ring2 = 0x2,
        Ring3 = User
    };
}