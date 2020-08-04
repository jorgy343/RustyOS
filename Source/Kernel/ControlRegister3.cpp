#include "ControlRegister3.h"

namespace Kernel
{
    namespace Registers
    {
        bool ControlRegister3::GetPageLevelWriteThrough()
        {
            return GetControlRegister3() & PWTMask;
        }

        void ControlRegister3::SetPageLevelWriteThrough(bool value)
        {
            SetControlRegister3((GetControlRegister3() & ~PWTMask) | (((size_t)value << PWTBit & PWTMask)));
        }

        void ControlRegister3::TogglePageLevelWriteThrough()
        {
            SetPageLevelWriteThrough(!GetPageLevelWriteThrough());
        }

        bool ControlRegister3::GetPageLevelCacheDisable()
        {
            return GetControlRegister3() & PCDMask;
        }

        void ControlRegister3::SetPageLevelCacheDisable(bool value)
        {
            SetControlRegister3((GetControlRegister3() & ~PCDMask) | (((size_t)value << PCDBit & PCDMask)));
        }

        void ControlRegister3::TogglePageLevelCacheDisable()
        {
            SetPageLevelCacheDisable(!GetPageLevelCacheDisable());
        }

        bool ControlRegister3::GetTableBaseAddress()
        {
            return GetControlRegister3() & TableBaseAddressMask;
        }

        void ControlRegister3::SetTableBaseAddress(bool value)
        {
            SetControlRegister3((GetControlRegister3() & ~TableBaseAddressMask) | (((size_t)value << TableBaseAddressStart & TableBaseAddressMask)));
        }

        void ControlRegister3::ToggleTableBaseAddress()
        {
            SetTableBaseAddress(!GetTableBaseAddress());
        }

        bool ControlRegister3::GetPAETableBaseAddresss()
        {
            return GetControlRegister3() & PAETableBaseAddresssMask;
        }

        void ControlRegister3::SetPAETableBaseAddresss(bool value)
        {
            SetControlRegister3((GetControlRegister3() & ~PAETableBaseAddresssMask) | (((size_t)value << PAETableBaseAddressStart & PAETableBaseAddresssMask)));
        }

        void ControlRegister3::TogglePAETableBaseAddresss()
        {
            SetPAETableBaseAddresss(!GetPAETableBaseAddresss());
        }

        bool ControlRegister3::GetPageMaplevel4TableBaseAddress()
        {
            return GetControlRegister3() & PageMaplevel4TableBaseAddressMask;
        }

        void ControlRegister3::SetPageMaplevel4TableBaseAddress(bool value)
        {
            SetControlRegister3((GetControlRegister3() & ~PageMaplevel4TableBaseAddressMask) | (((size_t)value << PageMapLevel4TableBaseAddressStart & PageMaplevel4TableBaseAddressMask)));
        }

        void ControlRegister3::TogglePageMaplevel4TableBaseAddress()
        {
            SetTableBaseAddress(!GetTableBaseAddress());
        }
    }
}