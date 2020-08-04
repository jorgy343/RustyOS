#include "ControlRegister2.h"

namespace Kernel
{
    namespace Registers
    {
        size_t ControlRegister2::GetPageFaultLinearAddress()
        {
            return GetControlRegister2();
        }
    }
}