#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Graphics
    {
        enum class LengthModifier
        {
            Char,
            Short,
            Int,
            Long,
            LongLong,
            IntMax,
            PointerSize,
            PointerDifference,
            LongDouble
        };
    }
}