#include "ControlRegister4.h"

namespace Kernel
{
    namespace Registers
    {
        bool ControlRegister4::GetVirtualModeExtensions()
        {
            return GetControlRegister4() & VMEMask;
        }

        void ControlRegister4::SetVirtualModeExtensions(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~VMEMask) | (((size_t)value << VMEBit & VMEMask)));
        }

        void ControlRegister4::ToggleVirtualModeExtensions()
        {
            SetVirtualModeExtensions(!GetVirtualModeExtensions());
        }

        bool ControlRegister4::GetProtectedModeVirtualInterrupts()
        {
            return GetControlRegister4() & PVIMask;
        }

        void ControlRegister4::SetProtectedModeVirtualInterrupts(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~PVIMask) | (((size_t)value << PVIBit & PVIMask)));
        }

        void ControlRegister4::ToggleProtectedModeVirtualInterrupts()
        {
            SetProtectedModeVirtualInterrupts(!GetProtectedModeVirtualInterrupts());
        }

        bool ControlRegister4::GetTimeStampDisable()
        {
            return GetControlRegister4() & TSDMask;
        }

        void ControlRegister4::SetTimeStampDisable(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~TSDMask) | (((size_t)value << TSDBit & TSDMask)));
        }

        void ControlRegister4::ToggleTimeStampDisable()
        {
            SetTimeStampDisable(!GetTimeStampDisable());
        }

        bool ControlRegister4::GetDebuggingExtensions()
        {
            return GetControlRegister4() & DEMask;
        }

        void ControlRegister4::SetDebuggingExtensions(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~DEMask) | (((size_t)value << DEBit & DEMask)));
        }

        void ControlRegister4::ToggleDebuggingExtensions()
        {
            SetDebuggingExtensions(!GetDebuggingExtensions());
        }

        bool ControlRegister4::GetPageSizeExtensions()
        {
            return GetControlRegister4() & PSEMask;
        }

        void ControlRegister4::SetPageSizeExtensions(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~PSEMask) | (((size_t)value << PSEBit & PSEMask)));
        }

        void ControlRegister4::TogglePageSizeExtensions()
        {
            SetPageSizeExtensions(!GetPageSizeExtensions());
        }

        bool ControlRegister4::GetPhysicalAddressExtensions()
        {
            return GetControlRegister4() & PAEMask;
        }

        void ControlRegister4::SetPhysicalAddressExtensions(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~PAEMask) | (((size_t)value << PAEBit & PAEMask)));
        }

        void ControlRegister4::TogglePhysicalAddressExtensions()
        {
            SetPhysicalAddressExtensions(!GetPhysicalAddressExtensions());
        }

        bool ControlRegister4::GetMachineCheckEnable()
        {
            return GetControlRegister4() & MCEMask;
        }

        void ControlRegister4::SetMachineCheckEnable(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~MCEMask) | (((size_t)value << MCEBit & MCEMask)));
        }

        void ControlRegister4::ToggleMachineCheckEnable()
        {
            SetMachineCheckEnable(!GetMachineCheckEnable());
        }

        bool ControlRegister4::GetPageGlobalEnable()
        {
            return GetControlRegister4() & PGEMask;
        }

        void ControlRegister4::SetPageGlobalEnable(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~PGEMask) | (((size_t)value << PGEBit & PGEMask)));
        }

        void ControlRegister4::TogglePageGlobalEnable()
        {
            SetPageGlobalEnable(!GetPageGlobalEnable());
        }

        bool ControlRegister4::GetPerformanceMonitoringCounterEnable()
        {
            return GetControlRegister4() & PCEMask;
        }

        void ControlRegister4::SetPerformanceMonitoringCounterEnable(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~PCEMask) | (((size_t)value << PCEBit & PCEMask)));
        }

        void ControlRegister4::TogglePerformanceMonitoringCounterEnable()
        {
            SetPerformanceMonitoringCounterEnable(!GetPerformanceMonitoringCounterEnable());
        }

        bool ControlRegister4::GetOperatingSystemFxsrSupport()
        {
            return GetControlRegister4() & OSFXSRMask;
        }

        void ControlRegister4::SetOperatingSystemFxsrSupport(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~OSFXSRMask) | (((size_t)value << OSFXSRBit & OSFXSRMask)));
        }

        void ControlRegister4::ToggleOperatingSystemFxsrSupport()
        {
            SetOperatingSystemFxsrSupport(!GetOperatingSystemFxsrSupport());
        }

        bool ControlRegister4::GetOperatingSystemUnmaskedExceptionSupport()
        {
            return GetControlRegister4() & OSXMMEXCPTMask;
        }

        void ControlRegister4::SetOperatingSystemUnmaskedExceptionSupport(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~OSXMMEXCPTMask) | (((size_t)value << OSXMMEXCPTBit & OSXMMEXCPTMask)));
        }

        void ControlRegister4::ToggleOperatingSystemUnmaskedExceptionSupport()
        {
            SetOperatingSystemUnmaskedExceptionSupport(!GetOperatingSystemUnmaskedExceptionSupport());
        }

        bool ControlRegister4::GetOperatingSystemXsaveEnable()
        {
            return GetControlRegister4() & OSXSAVEMask;
        }

        void ControlRegister4::SetOperatingSystemXsaveEnable(bool value)
        {
            SetControlRegister4((GetControlRegister4() & ~OSXSAVEMask) | (((size_t)value << OSXSAVEBit & OSXSAVEMask)));
        }

        void ControlRegister4::ToggleOperatingSystemXsaveEnable()
        {
            SetOperatingSystemXsaveEnable(!GetOperatingSystemXsaveEnable());
        }
    }
}