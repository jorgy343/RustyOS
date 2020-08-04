#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Memory
    {
        enum class MemoryMapEntryType
        {
            Usable = 1,
            Reserved = 2,
            AcpiReclaim = 3,
            AcpiNvs = 4,
            Bad = 5
        };
    }
}