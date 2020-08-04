#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Registers
    {
        class ControlRegister2
        {
        private:
            // Offsets
            static const int PageFaultLinearAddressStart = 0;
            static const int PageFaultLinearAddressEnd = 31;

            // Masks
            static const size_t PageFaultLinearAddressMask = Bits::CreateBitmask<size_t>(PageFaultLinearAddressStart, PageFaultLinearAddressEnd);

        public:
            ControlRegister2() = delete;
            ControlRegister2(const ControlRegister2 &) = delete;
            ControlRegister2 &operator=(const ControlRegister2 &) = delete;

            static size_t GetPageFaultLinearAddress();
        };

        extern "C" size_t GetControlRegister2();
    }
}