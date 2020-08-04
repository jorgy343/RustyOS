#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Registers
    {
        class ControlRegister0
        {
        private:
            // Offsets
            static const int PEBit = 0;
            static const int MPBit = 1;
            static const int EMBit = 2;
            static const int TSBit = 3;
            static const int ETBit = 4;
            static const int NEBit = 5;
            static const int WPBit = 16;
            static const int AMBit = 18;
            static const int NWBit = 29;
            static const int CDBit = 30;
            static const int PGBit = 31;

            // Masks
            static const size_t PEMask = Bits::CreateBitmask<size_t>(PEBit);
            static const size_t MPMask = Bits::CreateBitmask<size_t>(MPBit);
            static const size_t EMMask = Bits::CreateBitmask<size_t>(EMBit);
            static const size_t TSMask = Bits::CreateBitmask<size_t>(TSBit);
            static const size_t ETMask = Bits::CreateBitmask<size_t>(ETBit);
            static const size_t NEMask = Bits::CreateBitmask<size_t>(NEBit);
            static const size_t WPMask = Bits::CreateBitmask<size_t>(WPBit);
            static const size_t AMMask = Bits::CreateBitmask<size_t>(AMBit);
            static const size_t NWMask = Bits::CreateBitmask<size_t>(NWBit);
            static const size_t CDMask = Bits::CreateBitmask<size_t>(CDBit);
            static const size_t PGMask = Bits::CreateBitmask<size_t>(PGBit);

        public:
            ControlRegister0() = delete;
            ControlRegister0(const ControlRegister0 &) = delete;
            ControlRegister0 &operator=(const ControlRegister0 &) = delete;

            static bool GetProtectionEnabled();
            static void SetProtectionEnabled(bool value);
            static void ToggleProtectionEnabled();

            static bool GetMonitorCoprocessor();
            static void SetMonitorCoprocessor(bool value);
            static void ToggleMonitorCoprocessor();

            static bool GetEmulation();
            static void SetEmulation(bool value);
            static void ToggleEmulation();

            static bool GetTaskSwitched();
            static void SetTaskSwitched(bool value);
            static void ToggleTaskSwitched();

            static bool GetExtensionType();

            static bool GetNumericError();
            static void SetNumericError(bool value);
            static void ToggleNumericError();

            static bool GetWriteProtect();
            static void SetWriteProtect(bool value);
            static void ToggleWriteProtect();

            static bool GetAlignmentMask();
            static void SetAlignmentMask(bool value);
            static void ToggleAlignmentMask();

            static bool GetNotWritethrough();
            static void SetNotWritethrough(bool value);
            static void ToggleNotWritethrough();

            static bool GetCacheDisable();
            static void SetCacheDisable(bool value);
            static void ToggleCacheDisable();

            static bool GetPaging();
            static void SetPaging(bool value);
            static void TogglePaging();
        };

        extern "C" size_t GetControlRegister0();
        extern "C" void SetControlRegister0(size_t value);
    }
}