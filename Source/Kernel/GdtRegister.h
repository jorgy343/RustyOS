#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Descriptors
    {
        /// Represents the GDT CPU register in 32-bit protected mode or 64-bit long mode.
        class GdtRegister
        {
        private:
            /// The size of the GDT minus one.
            /// 
            /// @remark The GDT size is always the actual size of the GDT table in bytes minus one.
            /// We subtract one from the total size because the maximum size is 65536; however,
            /// that cannot be represented in 16 bits because zero takes up one combination of
            /// bits. Because a size of zero does not make sense we simply subtract one from the
            /// actual size.
            uint16_t size = 0;

            /// The linear address of the GDT. This member will be 32 bits big in protected mode
            /// and 64 bits big in long mode.
            LinearAddress address = 0;

        public:
            /// Installs the instance of this GdtRegister into the CPU GDT register. This function
            /// makes a call to lgdt to install the GDT and then immediately sets up all of the
            /// segment registers to use the new GDT.
            void Install();

            /// Gets the size of the GDT minus one.
            /// 
            /// @return Returns the size of the GDT minus one.
            /// 
            /// @remark The GDT size is always the actual size of the GDT table in bytes minus one.
            /// We subtract one from the total size because the maximum size is 65536; however,
            /// that cannot be represented in 16 bits because zero takes up one combination of
            /// bits. Because a size of zero does not make sense we simply subtract one from the
            /// actual size.
            uint16_t GetSize();

            /// Sets the size of the GDT minus one.
            /// 
            /// @param[in] value The size of the GDT minus one.
            /// 
            /// @remark The GDT size is always the actual size of the GDT table in bytes minus one.
            /// We subtract one from the total size because the maximum size is 65536; however,
            /// that cannot be represented in 16 bits because zero takes up one combination of
            /// bits. Because a size of zero does not make sense we simply subtract one from the
            /// actual size.
            void SetSize(uint16_t value);

            /// Gets the linear address where the GDT is located.
            /// 
            /// @return Returns the linear address where the GDT is located.
            LinearAddress GetAddress();

            /// Sets the linear address where the GDT is located.
            /// 
            /// @param[in] value The linear address of the GDT.
            void SetAddress(LinearAddress value);
        } __attribute__((packed));

        /// Assembly level function that installs a GDT. This is a low level function that calls
        /// the lgdt instruction, immediately performs a far jump to load the cs segment with 0x8
        /// and then loads all data segments with 0x10.
        /// 
        /// @param[in] gdtRegister A pointer to an instance of a GdtRegister.
        extern "C" void InstallGdt(GdtRegister* gdtRegister);
    }
}