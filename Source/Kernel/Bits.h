#pragma once
#include "Global.h"

namespace Kernel
{
    class Bits
    {
    public:
        Bits() = delete;
        Bits(const Bits &) = delete;
        Bits &operator=(const Bits &) = delete;

        template <typename T>
        static constexpr T CreateBitmask(int x)
        {
            return ((T)1 << x);
        }

        template <typename T>
        static constexpr T CreateBitmask(int x, int y)
        {
            return ((((T)1 << (y - x + 1)) - 1) << x);
        }
    };
}