#include "MemoryMapEntry.h"

namespace Kernel
{
    namespace Memory
    {
        void MemoryMapEntry::Align(uint64_t alignment)
        {
            uint64_t endingAddress = baseAddress + length;
            uint64_t baseAddressAdjustment = baseAddress % alignment;
            uint64_t endingAddressAdjustment = endingAddress % alignment;

            switch (type)
            {
            case MemoryMapEntryType::Usable:
            case MemoryMapEntryType::AcpiReclaim:
                length = (endingAddress - endingAddressAdjustment) - baseAddress;
                baseAddress += baseAddress + (alignment - baseAddressAdjustment);
                break;

            case MemoryMapEntryType::Reserved:
            case MemoryMapEntryType::AcpiNvs:
            case MemoryMapEntryType::Bad:
            default:
                length = (endingAddress + (alignment - endingAddressAdjustment)) - baseAddress;
                baseAddress += baseAddress - baseAddressAdjustment;
                break;
            }
        }

        PhysicalAddress MemoryMapEntry::GetNativeBaseAddress() const
        {
            return (PhysicalAddress)baseAddress;
        }

        size_t MemoryMapEntry::GetNativeLength() const
        {
            return (size_t)length;
        }

        uint64_t MemoryMapEntry::GetBaseAddress() const
        {
            return baseAddress;
        }

        void MemoryMapEntry::SetBaseAddress(uint64_t value)
        {
            baseAddress = value;
        }

        uint64_t MemoryMapEntry::GetLength() const
        {
            return length;
        }

        void MemoryMapEntry::SetLength(uint64_t value)
        {
            length = value;
        }

        MemoryMapEntryType MemoryMapEntry::GetType() const
        {
            return type;
        }

        void MemoryMapEntry::SetType(MemoryMapEntryType value)
        {
            type = value;
        }

        uint32_t MemoryMapEntry::GetExtendedAttributes() const
        {
            return extendedAttributes;
        }

        void MemoryMapEntry::SetExtendedAttributes(uint32_t value)
        {
            extendedAttributes = value;
        }
    }
}