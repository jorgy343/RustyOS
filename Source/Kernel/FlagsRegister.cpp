#include "FlagsRegister.h"

namespace Kernel
{
    namespace Registers
    {
        bool FlagsRegister::GetCarryFlag()
        {
            return GetFlags() & CFMask;
        }

        void FlagsRegister::SetCarryFlag(bool value)
        {
            SetFlags((GetFlags() & ~CFMask) | (((size_t)value << CFBit & CFMask)));
        }

        void FlagsRegister::ToggleCarryFlag()
        {
            SetCarryFlag(!GetCarryFlag());
        }

        bool FlagsRegister::GetParityFlag()
        {
            return GetFlags() & PFMask;
        }

        void FlagsRegister::SetParityFlag(bool value)
        {
            SetFlags((GetFlags() & ~PFMask) | (((size_t)value << PFBit & PFMask)));
        }

        void FlagsRegister::ToggleParityFlag()
        {
            SetParityFlag(!GetParityFlag());
        }

        bool FlagsRegister::GetAuxiliaryFlag()
        {
            return GetFlags() & AFMask;
        }

        void FlagsRegister::SetAuxiliaryFlag(bool value)
        {
            SetFlags((GetFlags() & ~AFMask) | (((size_t)value << AFBit & AFMask)));
        }

        void FlagsRegister::ToggleAuxiliaryFlag()
        {
            SetAuxiliaryFlag(!GetAuxiliaryFlag());
        }

        bool FlagsRegister::GetZeroFlag()
        {
            return GetFlags() & ZFMask;
        }

        void FlagsRegister::SetZeroFlag(bool value)
        {
            SetFlags((GetFlags() & ~ZFMask) | (((size_t)value << ZFBit & ZFMask)));
        }

        void FlagsRegister::ToggleZeroFlag()
        {
            SetZeroFlag(!GetZeroFlag());
        }

        bool FlagsRegister::GetSignFlag()
        {
            return GetFlags() & SFMask;
        }

        void FlagsRegister::SetSignFlag(bool value)
        {
            SetFlags((GetFlags() & ~SFMask) | (((size_t)value << SFBit & SFMask)));
        }

        void FlagsRegister::ToggleSignFlag()
        {
            SetSignFlag(!GetSignFlag());
        }

        bool FlagsRegister::GetTrapFlag()
        {
            return GetFlags() & TFMask;
        }

        void FlagsRegister::SetTrapFlag(bool value)
        {
            SetFlags((GetFlags() & ~TFMask) | (((size_t)value << TFBit & TFMask)));
        }

        void FlagsRegister::ToggleTrapFlag()
        {
            SetTrapFlag(!GetTrapFlag());
        }

        bool FlagsRegister::GetInterruptFlag()
        {
            return GetFlags() & IFMask;
        }

        void FlagsRegister::SetInterruptFlag(bool value)
        {
            SetFlags((GetFlags() & ~IFMask) | (((size_t)value << IFBit & IFMask)));
        }

        void FlagsRegister::ToggleInterruptFlag()
        {
            SetInterruptFlag(!GetInterruptFlag());
        }

        bool FlagsRegister::GetDirectionFlag()
        {
            return GetFlags() & DFMask;
        }

        void FlagsRegister::SetDirectionFlag(bool value)
        {
            SetFlags((GetFlags() & ~DFMask) | (((size_t)value << DFBit & DFMask)));
        }

        void FlagsRegister::ToggleDirectionFlag()
        {
            SetDirectionFlag(!GetDirectionFlag());
        }

        bool FlagsRegister::GetOverflowFlag()
        {
            return GetFlags() & OFMask;
        }

        void FlagsRegister::SetOverflowFlag(bool value)
        {
            SetFlags((GetFlags() & ~OFMask) | (((size_t)value << OFBit & OFMask)));
        }

        void FlagsRegister::ToggleOverflowFlag()
        {
            SetOverflowFlag(!GetOverflowFlag());
        }

        bool FlagsRegister::GetIOPrivilegeLevel()
        {
            return GetFlags() & IOPLMask;
        }

        void FlagsRegister::SetIOPrivilegeLevel(bool value)
        {
            SetFlags((GetFlags() & ~IOPLMask) | (((size_t)value << IOPLBit & IOPLMask)));
        }

        void FlagsRegister::ToggleIOPrivilegeLevel()
        {
            SetIOPrivilegeLevel(!GetIOPrivilegeLevel());
        }

        bool FlagsRegister::GetNestedTask()
        {
            return GetFlags() & NTMask;
        }

        void FlagsRegister::SetNestedTask(bool value)
        {
            SetFlags((GetFlags() & ~NTMask) | (((size_t)value << NTBit & NTMask)));
        }

        void FlagsRegister::ToggleNestedTask()
        {
            SetNestedTask(!GetNestedTask());
        }

        bool FlagsRegister::GetResumeFlag()
        {
            return GetFlags() & RFMask;
        }

        void FlagsRegister::SetResumeFlag(bool value)
        {
            SetFlags((GetFlags() & ~RFMask) | (((size_t)value << RFBit & RFMask)));
        }

        void FlagsRegister::ToggleResumeFlag()
        {
            SetResumeFlag(!GetResumeFlag());
        }

        bool FlagsRegister::GetVirtual8086Mode()
        {
            return GetFlags() & VMMask;
        }

        void FlagsRegister::SetVirtual8086Mode(bool value)
        {
            SetFlags((GetFlags() & ~VMMask) | (((size_t)value << VMBit & VMMask)));
        }

        void FlagsRegister::ToggleVirtual8086Mode()
        {
            SetVirtual8086Mode(!GetVirtual8086Mode());
        }

        bool FlagsRegister::GetAlignmentCheck()
        {
            return GetFlags() & ACMask;
        }

        void FlagsRegister::SetAlignmentCheck(bool value)
        {
            SetFlags((GetFlags() & ~ACMask) | (((size_t)value << ACBit & ACMask)));
        }

        void FlagsRegister::ToggleAlignmentCheck()
        {
            SetAlignmentCheck(!GetAlignmentCheck());
        }

        bool FlagsRegister::GetVirtualInterruptFlag()
        {
            return GetFlags() & VIFMask;
        }

        void FlagsRegister::SetVirtualInterruptFlag(bool value)
        {
            SetFlags((GetFlags() & ~VIFMask) | (((size_t)value << VIFBit & VIFMask)));
        }

        void FlagsRegister::ToggleVirtualInterruptFlag()
        {
            SetVirtualInterruptFlag(!GetVirtualInterruptFlag());
        }

        bool FlagsRegister::GetVirtualInterruptPending()
        {
            return GetFlags() & VIPMask;
        }

        void FlagsRegister::SetVirtualInterruptPending(bool value)
        {
            SetFlags((GetFlags() & ~VIPMask) | (((size_t)value << VIPBit & VIPMask)));
        }

        void FlagsRegister::ToggleVirtualInterruptPending()
        {
            SetVirtualInterruptPending(!GetVirtualInterruptPending());
        }

        bool FlagsRegister::GetIDFlag()
        {
            return GetFlags() & IDMask;
        }

        void FlagsRegister::SetIDFlag(bool value)
        {
            SetFlags((GetFlags() & ~IDMask) | (((size_t)value << IDBit & IDMask)));
        }

        void FlagsRegister::ToggleIDFlag()
        {
            SetIDFlag(!GetIDFlag());
        }
    }
}