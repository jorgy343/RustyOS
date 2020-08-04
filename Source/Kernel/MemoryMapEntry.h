#pragma once
#include "Global.h"
#include "MemoryMapEntryType.h"

namespace Kernel
{
    namespace Memory
    {
        class MemoryMapEntry
        {
        private:
            uint64_t baseAddress = 0;
            uint64_t length = 0;
            MemoryMapEntryType type = MemoryMapEntryType::Usable;
            uint32_t extendedAttributes = 0;

        public:
            void Align(uint64_t alignment);

            PhysicalAddress GetNativeBaseAddress() const;
            size_t GetNativeLength() const;

            uint64_t GetBaseAddress() const;
            void SetBaseAddress(uint64_t value);

            uint64_t GetLength() const;
            void SetLength(uint64_t value);

            MemoryMapEntryType GetType() const;
            void SetType(MemoryMapEntryType value);

            uint32_t GetExtendedAttributes() const;
            void SetExtendedAttributes(uint32_t value);
        };
    }
}