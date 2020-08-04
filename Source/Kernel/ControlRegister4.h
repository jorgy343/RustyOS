#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Registers
    {
        class ControlRegister4
        {
        private:
            // Offsets
            static const int VMEBit = 0;
            static const int PVIBit = 1;
            static const int TSDBit = 2;
            static const int DEBit = 3;
            static const int PSEBit = 4;
            static const int PAEBit = 5;
            static const int MCEBit = 6;
            static const int PGEBit = 7;
            static const int PCEBit = 8;
            static const int OSFXSRBit = 9;
            static const int OSXMMEXCPTBit = 10;
            static const int OSXSAVEBit = 18;

            // Masks
            static const size_t VMEMask = Bits::CreateBitmask<size_t>(VMEBit);
            static const size_t PVIMask = Bits::CreateBitmask<size_t>(PVIBit);
            static const size_t TSDMask = Bits::CreateBitmask<size_t>(TSDBit);
            static const size_t DEMask = Bits::CreateBitmask<size_t>(DEBit);
            static const size_t PSEMask = Bits::CreateBitmask<size_t>(PSEBit);
            static const size_t PAEMask = Bits::CreateBitmask<size_t>(PAEBit);
            static const size_t MCEMask = Bits::CreateBitmask<size_t>(MCEBit);
            static const size_t PGEMask = Bits::CreateBitmask<size_t>(PGEBit);
            static const size_t PCEMask = Bits::CreateBitmask<size_t>(PCEBit);
            static const size_t OSFXSRMask = Bits::CreateBitmask<size_t>(OSFXSRBit);
            static const size_t OSXMMEXCPTMask = Bits::CreateBitmask<size_t>(OSXMMEXCPTBit);
            static const size_t OSXSAVEMask = Bits::CreateBitmask<size_t>(OSXSAVEBit);

        public:
            ControlRegister4() = delete;
            ControlRegister4(const ControlRegister4 &) = delete;
            ControlRegister4 &operator=(const ControlRegister4 &) = delete;

            static bool GetVirtualModeExtensions();
            static void SetVirtualModeExtensions(bool value);
            static void ToggleVirtualModeExtensions();

            static bool GetProtectedModeVirtualInterrupts();
            static void SetProtectedModeVirtualInterrupts(bool value);
            static void ToggleProtectedModeVirtualInterrupts();

            static bool GetTimeStampDisable();
            static void SetTimeStampDisable(bool value);
            static void ToggleTimeStampDisable();

            static bool GetDebuggingExtensions();
            static void SetDebuggingExtensions(bool value);
            static void ToggleDebuggingExtensions();

            static bool GetPageSizeExtensions();
            static void SetPageSizeExtensions(bool value);
            static void TogglePageSizeExtensions();

            static bool GetPhysicalAddressExtensions();
            static void SetPhysicalAddressExtensions(bool value);
            static void TogglePhysicalAddressExtensions();

            static bool GetMachineCheckEnable();
            static void SetMachineCheckEnable(bool value);
            static void ToggleMachineCheckEnable();

            static bool GetPageGlobalEnable();
            static void SetPageGlobalEnable(bool value);
            static void TogglePageGlobalEnable();

            static bool GetPerformanceMonitoringCounterEnable();
            static void SetPerformanceMonitoringCounterEnable(bool value);
            static void TogglePerformanceMonitoringCounterEnable();

            static bool GetOperatingSystemFxsrSupport();
            static void SetOperatingSystemFxsrSupport(bool value);
            static void ToggleOperatingSystemFxsrSupport();

            static bool GetOperatingSystemUnmaskedExceptionSupport();
            static void SetOperatingSystemUnmaskedExceptionSupport(bool value);
            static void ToggleOperatingSystemUnmaskedExceptionSupport();

            static bool GetOperatingSystemXsaveEnable();
            static void SetOperatingSystemXsaveEnable(bool value);
            static void ToggleOperatingSystemXsaveEnable();
        };

        extern "C" size_t GetControlRegister4();
        extern "C" void SetControlRegister4(size_t value);
    }
}