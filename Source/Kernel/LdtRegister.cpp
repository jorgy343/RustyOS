#include "LdtRegister.h"

namespace Kernel
{
    namespace Descriptors
    {
        void LdtRegister::Install()
        {
            InstallLdt(selector);
        }

        uint16_t LdtRegister::GetSelector()
        {
            return selector;
        }

        void LdtRegister::SetSelector(uint16_t value)
        {
            selector = value;
        }
    }
}