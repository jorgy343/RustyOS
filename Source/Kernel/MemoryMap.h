#pragma once
#include "Global.h"
#include "MemoryMapEntryType.h"
#include "MemoryMapEntry.h"

namespace Kernel
{
    namespace Memory
    {
        class MemoryMap
        {
        public:
            static const int MaxEntries = 64;

        private:
            MemoryMapEntry entries[MaxEntries];
            int entryCount = 0;

            bool isMemorySizeCacheValid = true;
            size_t memorySizeCache = 0;

        public:
            void AddEntry(const MemoryMapEntry* value);
            void DeleteEntry(int index);

            void AlignAllEntries(uint64_t alignment);

            void InvalidateMemorySizeCache();
            size_t GetMemorySize();

            const MemoryMapEntry* GetEntryList() const;
            int GetEntryCount() const;
        };
    }
}