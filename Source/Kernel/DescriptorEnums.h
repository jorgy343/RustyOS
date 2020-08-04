#pragma once

namespace Kernel
{
    namespace Descriptors
    {
        enum class DescriptorType32
        {
            AvailableTss16 = 0x1,
            Ldt = 0x2,
            BusyTss16 = 0x3,
            CallGate16 = 0x4,
            TaskGate = 0x5,
            InterruptGate16 = 0x6,
            TrapGate16 = 0x7,
            AvailableTss32 = 0x9,
            BusyTss32 = 0xB,
            CallGate32 = 0xC,
            InterruptGate32 = 0xE,
            TrapGate32 = 0xF
        };

        enum class DescriptorType64
        {
            Ldt64 = 0x2,
            AvailableTss64 = 0x9,
            BusyTss64 = 0xB,
            CallGate64 = 0xC,
            InterruptGate64 = 0xE,
            TrapGate64 = 0xF
        };

        enum class AccessLevel
        {
            ExecuteOnly = 0,
            ReadOnly = 0,
            ExecuteAndRead = 1,
            ReadAndWrite = 1
        };

        enum class Conformance
        {
            Nonconforming = 0,
            Conforming = 1
        };

        enum class GrowthDirection
        {
            GrowsUp = 0,
            GrowsDown = 1
        };

        enum class SField
        {
            System = 0,
            User = 1
        };

        enum class LongModeSize
        {
            CompatabilityMode = 0,
            LongMode = 1
        };

        enum class DefaultOperationSize
        {
            Protected16Bit = 0,
            Protected32Bit = 1
        };

        enum class Granularity
        {
            Byte = 0,
            FourKilobyte = 1
        };
    }
}