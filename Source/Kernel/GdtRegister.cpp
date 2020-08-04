#include "GdtRegister.h"

namespace Kernel
{
    namespace Descriptors
    {
        void GdtRegister::Install()
        {
            InstallGdt(this);
        }

        uint16_t GdtRegister::GetSize()
        {
            return size;
        }

        void GdtRegister::SetSize(uint16_t value)
        {
            size = value;
        }

        LinearAddress GdtRegister::GetAddress()
        {
            return address;
        }

        void GdtRegister::SetAddress(LinearAddress value)
        {
            address = value;
        }
    }
}