#include "Descriptor.h"

namespace Kernel
{
    namespace Descriptors
    {
        uint64_t Descriptor::CreateCodeSegment32(uint32_t segmentLimit, uint32_t baseAddress, RingLevel privilegeLevel, Granularity granularity, AccessLevel accessLevel, DefaultOperationSize defaultOperationSize, Conformance conformance, bool isPresent, bool wasAccessed, bool available)
        {
            uint64_t data = 0;

            // segmentLimit
            data = (data & ~Limit1Mask) | (((uint64_t)segmentLimit << Limit1Start) & Limit1Mask);
            data = (data & ~Limit2Mask) | (((uint64_t)segmentLimit << Limit2Start) & Limit2Mask);
            
            // baseAddress
            data = (data & ~Base1Mask) | (((uint64_t)baseAddress << Base1Start) & Base1Mask);
            data = (data & ~Base2Mask) | (((uint64_t)baseAddress << Base2Start) & Base2Mask);
            data = (data & ~Base3Mask) | (((uint64_t)baseAddress << Base3Start) & Base3Mask);

            // wasAccessed
            data = (data & ~AccessedMask) | (((uint64_t)wasAccessed << AccessedBit) & AccessedMask);

            // codeAccessLevel
            data = (data & ~AccessLevelMask) | (((uint64_t)accessLevel << AccessLevelBit) & AccessLevelMask);

            // isConforming
            data = (data & ~ConformingMask) | (((uint64_t)conformance << ConformingBit) & ConformingMask);

            // isExecutable - hard coded
            data = (data & ~ExecutableMask) | (((uint64_t)0x1 << ExecutableBit) & ExecutableMask);

            // descriptorType - hard coded
            data = (data & ~SFieldMask) | (((uint64_t)SField::User << SFieldBit) & SFieldMask);

            // privilegeLevel
            data = (data & ~PrivilegeLevelMask) | (((uint64_t)privilegeLevel << PrivilegeLevelStart) & PrivilegeLevelMask);

            // isPresent
            data = (data & ~PresentMask) | (((uint64_t)isPresent << PresentBit) & PresentMask);

            // available
            data = (data & ~AvailableMask) | (((uint64_t)available << AvailableBit) & AvailableMask);

            // defaultOperationSize
            data = (data & ~DefaultOperationSizeMask) | (((uint64_t)defaultOperationSize << DefaultOperationSizeBit) & DefaultOperationSizeMask);

            // Granularity
            data = (data & ~GranularityMask) | (((uint64_t)granularity << GranularityBit) & GranularityMask);

            return data;
        }

        uint64_t Descriptor::CreateDataSegment32(uint32_t segmentLimit, uint32_t baseAddress, RingLevel privilegeLevel, Granularity granularity, AccessLevel accessLevel, DefaultOperationSize defaultOperationSize, GrowthDirection growthDirection, bool isPresent, bool wasAccessed, bool available)
        {
            uint64_t data = 0;

            // segmentLimit
            data = (data & ~Limit1Mask) | (((uint64_t)segmentLimit << Limit1Start) & Limit1Mask);
            data = (data & ~Limit2Mask) | (((uint64_t)segmentLimit << Limit2Start) & Limit2Mask);

            // baseAddress
            data = (data & ~Base1Mask) | (((uint64_t)baseAddress << Base1Start) & Base1Mask);
            data = (data & ~Base2Mask) | (((uint64_t)baseAddress << Base2Start) & Base2Mask);
            data = (data & ~Base3Mask) | (((uint64_t)baseAddress << Base3Start) & Base3Mask);

            // wasAccessed
            data = (data & ~AccessedMask) | (((uint64_t)wasAccessed << AccessedBit) & AccessedMask);

            // dataAccessLevel
            data = (data & ~AccessLevelMask) | (((uint64_t)accessLevel << AccessLevelBit) & AccessLevelMask);

            // isConforming
            data = (data & ~DirectionMask) | (((uint64_t)growthDirection << DirectionBit) & DirectionMask);

            // isExecutable - hard coded
            data = (data & ~ExecutableMask) | (((uint64_t)0x0 << ExecutableBit) & ExecutableMask);

            // descriptorType - hard coded
            data = (data & ~SFieldMask) | (((uint64_t)SField::User << SFieldBit) & SFieldMask);

            // privilegeLevel
            data = (data & ~PrivilegeLevelMask) | (((uint64_t)privilegeLevel << PrivilegeLevelStart) & PrivilegeLevelMask);

            // isPresent
            data = (data & ~PresentMask) | (((uint64_t)isPresent << PresentBit) & PresentMask);

            // available
            data = (data & ~AvailableMask) | (((uint64_t)available << AvailableBit) & AvailableMask);

            // defaultOperationSize
            data = (data & ~DefaultOperationSizeMask) | (((uint64_t)defaultOperationSize << DefaultOperationSizeBit) & DefaultOperationSizeMask);

            // Granularity
            data = (data & ~GranularityMask) | (((uint64_t)granularity << GranularityBit) & GranularityMask);

            return data;
        }

        uint64_t Descriptor::CreateCodeSegment64(RingLevel privilegeLevel, DefaultOperationSize defaultOperationSize, Conformance conformance, LongModeSize longModeSize, bool isPresent)
        {
            uint64_t data = 0;

            // isConforming
            data = (data & ~ConformingMask) | (((uint64_t)conformance << ConformingBit) & ConformingMask);

            // privilegeLevel
            data = (data & ~PrivilegeLevelMask) | (((uint64_t)privilegeLevel << PrivilegeLevelStart) & PrivilegeLevelMask);

            // isPresent
            data = (data & ~PresentMask) | (((uint64_t)isPresent << PresentBit) & PresentMask);

            // longModeSize
            data = (data & ~LongModeSizeMask) | (((uint64_t)longModeSize << LongModeSizeBit) & LongModeSizeMask);

            // defaultOperationSize
            data = (data & ~DefaultOperationSizeMask) | (((uint64_t)defaultOperationSize << DefaultOperationSizeBit) & DefaultOperationSizeMask);

            return data;
        }

        uint64_t Descriptor::CreateDataSegment64(bool isPresent)
        {
            uint64_t data = 0;

            // isPresent
            data = (data & ~PresentMask) | (((uint64_t)isPresent << PresentBit) & PresentMask);

            return data;
        }

        uint64_t Descriptor::CreateInterruptGate32(uint16_t codeSegmentSelector, LinearAddress target, RingLevel privilegeLevel, bool isPresent)
        {
            uint64_t data = 0;

            // codeSegmentSelector
            data = (data & ~SelectorMask) | (((uint64_t)codeSegmentSelector << SelectorStart) & SelectorMask);

            // target
            data = (data & ~TargetOffset1Mask) | (((uint64_t)target << TargetOffset1Start) & TargetOffset1Mask);
            data = (data & ~TargetOffset2Mask) | (((uint64_t)target << TargetOffset2Start) & TargetOffset2Mask);

            // type - hard coded
            data = (data & ~DescriptorTypeMask) | (((uint64_t)DescriptorType32::InterruptGate32 << DescriptorTypeStart) & DescriptorTypeMask);

            // descriptorType - hard coded
            data = (data & ~SFieldMask) | (((uint64_t)SField::System << SFieldBit) & SFieldMask);

            // isPresent
            data = (data & ~PresentMask) | (((uint64_t)isPresent << PresentBit) & PresentMask);

            return data;
        }

        uint64_t Descriptor::CreateTrapGate32(uint16_t codeSegmentSelector, LinearAddress target, RingLevel privilegeLevel, bool isPresent)
        {
            uint64_t data = 0;

            // codeSegmentSelector
            data = (data & ~SelectorMask) | (((uint64_t)codeSegmentSelector << SelectorStart) & SelectorMask);

            // target
            data = (data & ~TargetOffset1Mask) | (((uint64_t)target << TargetOffset1Start) & TargetOffset1Mask);
            data = (data & ~TargetOffset2Mask) | (((uint64_t)target << TargetOffset2Start) & TargetOffset2Mask);

            // type - hard coded
            data = (data & ~DescriptorTypeMask) | (((uint64_t)DescriptorType32::TrapGate32 << DescriptorTypeStart) & DescriptorTypeMask);

            // descriptorType - hard coded
            data = (data & ~SFieldMask) | (((uint64_t)SField::System << SFieldBit) & SFieldMask);

            // isPresent
            data = (data & ~PresentMask) | (((uint64_t)isPresent << PresentBit) & PresentMask);

            return data;
        }
    }
}