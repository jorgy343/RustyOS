#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Registers
    {
        class FlagsRegister
        {
        private:
            // Offsets
            static const int CFBit = 0;
            static const int PFBit = 2;
            static const int AFBit = 4;
            static const int ZFBit = 6;
            static const int SFBit = 7;
            static const int TFBit = 8;
            static const int IFBit = 9;
            static const int DFBit = 10;
            static const int OFBit = 11;
            static const int IOPLBit = 12;
            static const int NTBit = 14;
            static const int RFBit = 16;
            static const int VMBit = 17;
            static const int ACBit = 18;
            static const int VIFBit = 19;
            static const int VIPBit = 20;
            static const int IDBit = 21;

            // Masks
            static const size_t CFMask = Bits::CreateBitmask<size_t>(CFBit);
            static const size_t PFMask = Bits::CreateBitmask<size_t>(PFBit);
            static const size_t AFMask = Bits::CreateBitmask<size_t>(AFBit);
            static const size_t ZFMask = Bits::CreateBitmask<size_t>(ZFBit);
            static const size_t SFMask = Bits::CreateBitmask<size_t>(SFBit);
            static const size_t TFMask = Bits::CreateBitmask<size_t>(TFBit);
            static const size_t IFMask = Bits::CreateBitmask<size_t>(IFBit);
            static const size_t DFMask = Bits::CreateBitmask<size_t>(DFBit);
            static const size_t OFMask = Bits::CreateBitmask<size_t>(OFBit);
            static const size_t IOPLMask = Bits::CreateBitmask<size_t>(IOPLBit);
            static const size_t NTMask = Bits::CreateBitmask<size_t>(NTBit);
            static const size_t RFMask = Bits::CreateBitmask<size_t>(RFBit);
            static const size_t VMMask = Bits::CreateBitmask<size_t>(VMBit);
            static const size_t ACMask = Bits::CreateBitmask<size_t>(ACBit);
            static const size_t VIFMask = Bits::CreateBitmask<size_t>(VIFBit);
            static const size_t VIPMask = Bits::CreateBitmask<size_t>(VIPBit);
            static const size_t IDMask = Bits::CreateBitmask<size_t>(IDBit);

        public:
            FlagsRegister() = delete;
            FlagsRegister(const FlagsRegister &) = delete;
            FlagsRegister &operator=(const FlagsRegister &) = delete;

            bool GetCarryFlag();
            void SetCarryFlag(bool value);
            void ToggleCarryFlag();

            void SetParityFlag(bool value);
            bool GetParityFlag();
            void ToggleParityFlag();

            bool GetAuxiliaryFlag();
            void SetAuxiliaryFlag(bool value);
            void ToggleAuxiliaryFlag();

            bool GetZeroFlag();
            void SetZeroFlag(bool value);
            void ToggleZeroFlag();

            bool GetSignFlag();
            void SetSignFlag(bool value);
            void ToggleSignFlag();

            bool GetTrapFlag();
            void SetTrapFlag(bool value);
            void ToggleTrapFlag();

            bool GetInterruptFlag();
            void SetInterruptFlag(bool value);
            void ToggleInterruptFlag();

            bool GetDirectionFlag();
            void SetDirectionFlag(bool value);
            void ToggleDirectionFlag();

            bool GetOverflowFlag();
            void SetOverflowFlag(bool value);
            void ToggleOverflowFlag();

            bool GetIOPrivilegeLevel();
            void SetIOPrivilegeLevel(bool value);
            void ToggleIOPrivilegeLevel();

            bool GetNestedTask();
            void SetNestedTask(bool value);
            void ToggleNestedTask();

            bool GetResumeFlag();
            void SetResumeFlag(bool value);
            void ToggleResumeFlag();

            bool GetVirtual8086Mode();
            void SetVirtual8086Mode(bool value);
            void ToggleVirtual8086Mode();

            bool GetAlignmentCheck();
            void SetAlignmentCheck(bool value);
            void ToggleAlignmentCheck();

            bool GetVirtualInterruptFlag();
            void SetVirtualInterruptFlag(bool value);
            void ToggleVirtualInterruptFlag();

            bool GetVirtualInterruptPending();
            void SetVirtualInterruptPending(bool value);
            void ToggleVirtualInterruptPending();

            bool GetIDFlag();
            void SetIDFlag(bool value);
            void ToggleIDFlag();
        };

        extern "C" size_t GetFlags();
        extern "C" void SetFlags(size_t value);
    }
}