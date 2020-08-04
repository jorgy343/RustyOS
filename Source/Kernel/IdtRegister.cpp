#include "IdtRegister.h"

namespace Kernel
{
    namespace Descriptors
    {
        void IdtRegister::Install()
        {
            InstallIdt(this);
        }

        uint16_t IdtRegister::GetSize()
        {
            return size;
        }

        void IdtRegister::SetSize(uint16_t value)
        {
            size = value;
        }

        LinearAddress IdtRegister::GetAddress()
        {
            return address;
        }

        void IdtRegister::SetAddress(LinearAddress value)
        {
            address = value;
        }
    }
}