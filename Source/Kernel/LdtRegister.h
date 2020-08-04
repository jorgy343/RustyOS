#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Descriptors
    {
        /// Represents the LDT CPU register in 32-bit protected mode.
        class LdtRegister
        {
        private:
            /// The selector of the LDT register.
            uint16_t selector = 0;

        public:
            /// Installs the instance of this LdtRegister into the CPU LDT register. This function
            /// makes a call to lldt to install the LDT.
            void Install();

            /// Gets the selector of the LDT register.
            uint16_t GetSelector();

            /// Sets the selecto rof the LDT register.
            /// 
            /// @param[in] value The selector of the LDT register.
            void SetSelector(uint16_t value);
        };

        /// Assembly level function that installs a LDT. This is a low level function that calls
        /// the lldt instruction.
        /// 
        /// @param[in] selector The selector to set the LDT to.
        extern "C" void InstallLdt(uint16_t selector);
    }
}