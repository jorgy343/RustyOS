#include "ControlRegister0.h"

namespace Kernel
{
    namespace Registers
    {
        bool ControlRegister0::GetProtectionEnabled()
        {
            return GetControlRegister0() & PEMask;
        }

        void ControlRegister0::SetProtectionEnabled(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~PEMask) | (((size_t)value << PEBit & PEMask)));
        }

        void ControlRegister0::ToggleProtectionEnabled()
        {
            SetProtectionEnabled(!GetProtectionEnabled());
        }

        bool ControlRegister0::GetMonitorCoprocessor()
        {
            return GetControlRegister0() & MPMask;
        }

        void ControlRegister0::SetMonitorCoprocessor(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~MPMask) | (((size_t)value << MPBit & MPMask)));
        }

        void ControlRegister0::ToggleMonitorCoprocessor()
        {
            SetMonitorCoprocessor(!GetMonitorCoprocessor());
        }

        bool ControlRegister0::GetEmulation()
        {
            return GetControlRegister0() & EMMask;
        }

        void ControlRegister0::SetEmulation(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~EMMask) | (((size_t)value << EMBit & EMMask)));
        }

        void ControlRegister0::ToggleEmulation()
        {
            SetEmulation(!GetEmulation());
        }

        bool ControlRegister0::GetTaskSwitched()
        {
            return GetControlRegister0() & TSMask;
        }

        void ControlRegister0::SetTaskSwitched(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~TSMask) | (((size_t)value << TSBit & TSMask)));
        }

        void ControlRegister0::ToggleTaskSwitched()
        {
            SetTaskSwitched(!GetTaskSwitched());
        }

        bool ControlRegister0::GetExtensionType()
        {
            return GetControlRegister0() & ETMask;
        }

        bool ControlRegister0::GetNumericError()
        {
            return GetControlRegister0() & NEMask;
        }

        void ControlRegister0::SetNumericError(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~NEMask) | (((size_t)value << NEBit & NEMask)));
        }

        void ControlRegister0::ToggleNumericError()
        {
            SetNumericError(!GetNumericError());
        }

        bool ControlRegister0::GetWriteProtect()
        {
            return GetControlRegister0() & WPMask;
        }

        void ControlRegister0::SetWriteProtect(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~WPMask) | (((size_t)value << WPBit & WPMask)));
        }

        void ControlRegister0::ToggleWriteProtect()
        {
            SetWriteProtect(!GetWriteProtect());
        }

        bool ControlRegister0::GetAlignmentMask()
        {
            return GetControlRegister0() & AMMask;
        }

        void ControlRegister0::SetAlignmentMask(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~AMMask) | (((size_t)value << AMBit & AMMask)));
        }

        void ControlRegister0::ToggleAlignmentMask()
        {
            SetAlignmentMask(!GetAlignmentMask());
        }

        bool ControlRegister0::GetNotWritethrough()
        {
            return GetControlRegister0() & NWMask;
        }

        void ControlRegister0::SetNotWritethrough(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~NWMask) | (((size_t)value << NWBit & NWMask)));
        }

        void ControlRegister0::ToggleNotWritethrough()
        {
            SetNotWritethrough(!GetNotWritethrough());
        }

        bool ControlRegister0::GetCacheDisable()
        {
            return GetControlRegister0() & CDMask;
        }

        void ControlRegister0::SetCacheDisable(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~CDMask) | (((size_t)value << CDBit & CDMask)));
        }

        void ControlRegister0::ToggleCacheDisable()
        {
            SetCacheDisable(!GetCacheDisable());
        }

        bool ControlRegister0::GetPaging()
        {
            return GetControlRegister0() & PGMask;
        }

        void ControlRegister0::SetPaging(bool value)
        {
            SetControlRegister0((GetControlRegister0() & ~PGMask) | (((size_t)value << PGBit & PGMask)));
        }

        void ControlRegister0::TogglePaging()
        {
            SetPaging(!GetPaging());
        }
    }
}