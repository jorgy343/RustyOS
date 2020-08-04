#pragma once
#include "Global.h"

namespace Kernel
{
    extern "C" void outb(uint8_t value, uint16_t port);
    extern "C" void outw(uint16_t value, uint16_t port);
    extern "C" void outl(uint32_t value, uint16_t port);

    extern "C" uint8_t inb(uint16_t port);
    extern "C" uint16_t inw(uint16_t port);
    extern "C" uint32_t inl(uint16_t port);
}