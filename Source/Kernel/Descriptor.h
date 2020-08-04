#pragma once
#include "Global.h"
#include "Bits.h"
#include "DescriptorEnums.h"

namespace Kernel
{
    namespace Descriptors
    {
        class Descriptor
        {
        protected:
            // Offsets
            static const int TargetOffset1Start = 0;
            static const int TargetOffset1End = 15;
            static const int TargetOffset2Start = 48;
            static const int TargetOffset2End = 63;
            static const int TargetOffset3Start = 0; // Long mode only.
            static const int TargetOffset3End = 31; // Long mode only.

            static const int SelectorStart = 16;
            static const int SelectorEnd = 31;

            static const int Limit1Start = 0;
            static const int Limit1End = 15;
            static const int Limit2Start = 48;
            static const int Limit2End = 51;

            static const int Base1Start = 16;
            static const int Base1End = 31;
            static const int Base2Start = 32;
            static const int Base2End = 39;
            static const int Base3Start = 56;
            static const int Base3End = 63;
            static const int Base4Start = 0; // Long mode only.
            static const int Base4End = 31; // Long mode only.

            static const int IstStart = 32; // Long mode only.
            static const int IstEnd = 34; // Long mode only.
            static const int ParameterCountStart = 32; // Call gate descriptor only.
            static const int ParameterCountEnd = 36; // Call gate descriptor only.
            static const int DescriptorTypeStart = 40; // Shouldn't be used for user segments.
            static const int DescriptorTypeEnd = 43; // Shouldn't be used for user segments.

            static const int AccessedBit = 40;
            static const int AccessLevelBit = 41;
            static const int ConformingBit = 42;
            static const int DirectionBit = 42;
            static const int ExecutableBit = 43;
            static const int SFieldBit = 44;

            static const int PrivilegeLevelStart = 45;
            static const int PrivilegeLevelEnd = 46;

            static const int PresentBit = 47;
            static const int AvailableBit = 52;
            static const int LongModeSizeBit = 53;
            static const int DefaultOperationSizeBit = 54;
            static const int GranularityBit = 55;

            // Masks
            static const uint64_t TargetOffset1Mask = Bits::CreateBitmask<uint64_t>(TargetOffset1Start, TargetOffset1End);
            static const uint64_t TargetOffset2Mask = Bits::CreateBitmask<uint64_t>(TargetOffset2Start, TargetOffset2End);
            static const uint64_t TargetOffset3Mask = Bits::CreateBitmask<uint64_t>(TargetOffset3Start, TargetOffset3End); // Long mode only.

            static const uint64_t SelectorMask = Bits::CreateBitmask<uint64_t>(SelectorStart, SelectorEnd);

            static const uint64_t Limit1Mask = Bits::CreateBitmask<uint64_t>(Limit1Start, Limit1End);
            static const uint64_t Limit2Mask = Bits::CreateBitmask<uint64_t>(Limit2Start, Limit2End);

            static const uint64_t Base1Mask = Bits::CreateBitmask<uint64_t>(Base1Start, Base1End);
            static const uint64_t Base2Mask = Bits::CreateBitmask<uint64_t>(Base2Start, Base2End);
            static const uint64_t Base3Mask = Bits::CreateBitmask<uint64_t>(Base3Start, Base3End);
            static const uint64_t Base4Mask = Bits::CreateBitmask<uint64_t>(Base4Start, Base4End); // Long mode only.

            static const uint64_t IstMask = Bits::CreateBitmask<uint64_t>(IstStart, IstEnd); // Long mode only.
            static const uint64_t ParameterCountMask = Bits::CreateBitmask<uint64_t>(ParameterCountStart, ParameterCountEnd); // Call gate descriptor only.
            static const uint64_t DescriptorTypeMask = Bits::CreateBitmask<uint64_t>(DescriptorTypeStart, DescriptorTypeEnd); // Shouldn't be used for user segments.

            static const uint64_t AccessedMask = Bits::CreateBitmask<uint64_t>(AccessedBit);
            static const uint64_t AccessLevelMask = Bits::CreateBitmask<uint64_t>(AccessLevelBit);
            static const uint64_t ConformingMask = Bits::CreateBitmask<uint64_t>(ConformingBit);
            static const uint64_t DirectionMask = Bits::CreateBitmask<uint64_t>(DirectionBit);
            static const uint64_t ExecutableMask = Bits::CreateBitmask<uint64_t>(ExecutableBit);
            static const uint64_t SFieldMask = Bits::CreateBitmask<uint64_t>(SFieldBit);

            static const uint64_t PrivilegeLevelMask = Bits::CreateBitmask<uint64_t>(PrivilegeLevelStart, PrivilegeLevelEnd);

            static const uint64_t PresentMask = Bits::CreateBitmask<uint64_t>(PresentBit);
            static const uint64_t AvailableMask = Bits::CreateBitmask<uint64_t>(AvailableBit);
            static const uint64_t LongModeSizeMask = Bits::CreateBitmask<uint64_t>(LongModeSizeBit);
            static const uint64_t DefaultOperationSizeMask = Bits::CreateBitmask<uint64_t>(DefaultOperationSizeBit);
            static const uint64_t GranularityMask = Bits::CreateBitmask<uint64_t>(GranularityBit);

            // Contiguous Offsets
            static const int Limit1ContiguousOffset = 0;
            static const int Limit2ContiguousOffset = (Limit1End - Limit1Start) + 1;

            static const int Base1ContiguousOffset = 0;
            static const int Base2ContiguousOffset = (Base1End - Base1Start) + 1;
            static const int Base3ContiguousOffset = (Base1End - Base1Start) + (Base2End - Base2Start) + 2;

        public:
            Descriptor() = delete;
            Descriptor(const Bits &) = delete;
            Descriptor &operator=(const Bits &) = delete;

            static uint64_t CreateCodeSegment32(uint32_t segmentLimit, uint32_t baseAddress, RingLevel privilegeLevel, Granularity granularity, AccessLevel accessLevel, DefaultOperationSize defaultOperationSize, Conformance conformance, bool isPresent = true, bool wasAccessed = false, bool available = false);
            static uint64_t CreateDataSegment32(uint32_t segmentLimit, uint32_t baseAddress, RingLevel privilegeLevel, Granularity granularity, AccessLevel accessLevel, DefaultOperationSize defaultOperationSize, GrowthDirection growthDirection, bool isPresent = true, bool wasAccessed = false, bool available = false);
            static uint64_t CreateInterruptGate32(uint16_t codeSegmentSelector, LinearAddress target, RingLevel privilegeLevel, bool isPresent = true);
            static uint64_t CreateTrapGate32(uint16_t codeSegmentSelector, LinearAddress target, RingLevel privilegeLevel, bool isPresent = true);

            static uint64_t CreateCodeSegment64(RingLevel privilegeLevel, DefaultOperationSize defaultOperationSize, Conformance conformance, LongModeSize longModeSize, bool isPresent = true);
            static uint64_t CreateDataSegment64(bool isPresent = true);
        };
    }
}