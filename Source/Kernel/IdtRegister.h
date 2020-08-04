#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Descriptors
    {
        /// Represents the IDT CPU register in 32-bit protected mode or 64-bit long mode.
        class IdtRegister
        {
        private:
            /// The size of the IDT minus one.
            /// 
            /// @remark The IDT size is always the actual size of the IDT table in bytes minus one.
            /// We subtract one from the total size because the maximum size is 65536; however,
            /// that cannot be represented in 16 bits because zero takes up one combination of
            /// bits. Because a size of zero does not make sense we simply subtract one from the
            /// actual size.
            uint16_t size = 0;

            /// The linear address of the IDT. This member will be 32 bits big in protected mode
            /// and 64 bits big in long mode.
            LinearAddress address = 0;

        public:
            /// Installs the instance of this IdtRegister into the CPU IDT register. This function
            /// makes a call to lidt to install the IDT and then immediately sets up all of the
            /// segment registers to use the new IDT.
            void Install();

            /// Gets the size of the IDT minus one.
            /// 
            /// @return Returns the size of the IDT minus one.
            /// 
            /// @remark The IDT size is always the actual size of the IDT table in bytes minus one.
            /// We subtract one from the total size because the maximum size is 65536; however,
            /// that cannot be represented in 16 bits because zero takes up one combination of
            /// bits. Because a size of zero does not make sense we simply subtract one from the
            /// actual size.
            uint16_t GetSize();

            /// Sets the size of the IDT minus one.
            /// 
            /// @param[in] value The size of the IDT minus one.
            /// 
            /// @remark The IDT size is always the actual size of the IDT table in bytes minus one.
            /// We subtract one from the total size because the maximum size is 65536; however,
            /// that cannot be represented in 16 bits because zero takes up one combination of
            /// bits. Because a size of zero does not make sense we simply subtract one from the
            /// actual size.
            void SetSize(uint16_t value);

            /// Gets the linear address where the IDT is located.
            /// 
            /// @return Returns the linear address where the IDT is located.
            LinearAddress GetAddress();

            /// Sets the linear address where the IDT is located.
            /// 
            /// @param[in] value The linear address of the IDT.
            void SetAddress(LinearAddress value);
        } __attribute__((packed));

        /// Assembly level function that installs a IDT. This is a low level function that calls
        /// the lidt instruction.
        /// 
        /// @param[in] idtRegister A pointer to an instance of a IdtRegister.
        extern "C" void InstallIdt(IdtRegister* idtRegister);
    }
}