#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Registers
    {
        class ControlRegister3
        {
        private:
            // Offsets
            static const int PWTBit = 3;
            static const int PCDBit = 4;
            static const int TableBaseAddressStart = 12;
            static const int TableBaseAddressEnd = 31;
            static const int PAETableBaseAddressStart = 5;
            static const int PAETableBaseAddressEnd = 31;
            static const int PageMapLevel4TableBaseAddressStart = 12;
            static const int PageMaplevel4TableBaseAddressEnd = 51;

            // Masks
            static const size_t PWTMask = Bits::CreateBitmask<size_t>(PWTBit);
            static const size_t PCDMask = Bits::CreateBitmask<size_t>(PCDBit);
            static const size_t TableBaseAddressMask = Bits::CreateBitmask<size_t>(TableBaseAddressStart, TableBaseAddressEnd);
            static const size_t PAETableBaseAddresssMask = Bits::CreateBitmask<size_t>(PAETableBaseAddressStart, PAETableBaseAddressEnd);
            static const size_t PageMaplevel4TableBaseAddressMask = Bits::CreateBitmask<size_t>(PageMapLevel4TableBaseAddressStart, PageMaplevel4TableBaseAddressEnd);

        public:
            ControlRegister3() = delete;
            ControlRegister3(const ControlRegister3 &) = delete;
            ControlRegister3 &operator=(const ControlRegister3 &) = delete;

            static bool GetPageLevelWriteThrough();
            static void SetPageLevelWriteThrough(bool value);
            static void TogglePageLevelWriteThrough();

            static bool GetPageLevelCacheDisable();
            static void SetPageLevelCacheDisable(bool value);
            static void TogglePageLevelCacheDisable();
            
            static bool GetTableBaseAddress();
            static void SetTableBaseAddress(bool value);
            static void ToggleTableBaseAddress();

            static bool GetPAETableBaseAddresss();
            static void SetPAETableBaseAddresss(bool value);
            static void TogglePAETableBaseAddresss();

            static bool GetPageMaplevel4TableBaseAddress();
            static void SetPageMaplevel4TableBaseAddress(bool value);
            static void TogglePageMaplevel4TableBaseAddress();
        };

        extern "C" size_t GetControlRegister3();
        extern "C" void SetControlRegister3(size_t value);
    }
}