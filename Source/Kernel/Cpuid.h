#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Utility
    {
        class Cpuid
        {
        private:
            // Offsets
            static const int FPUBit = 0;
            static const int VMEBit = 1;
            static const int DEBit = 2;
            static const int PSEBit = 3;
            static const int TSCBit = 4;
            static const int MSRBit = 5;
            static const int PAEBit = 6;

            // Masks


        public:
            Cpuid() = delete;
            Cpuid(const Cpuid &) = delete;
            Cpuid &operator=(const Cpuid &) = delete;
        };
    }
}