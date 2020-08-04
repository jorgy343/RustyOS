#include "MemoryMap.h"

namespace Kernel
{
    namespace Memory
    {
        void MemoryMap::AddEntry(const MemoryMapEntry* value)
        {
            // We cannot insert more entries then the size of the entries array.
            if (entryCount >= MaxEntries)
                return;

            entries[entryCount++] = *value;

            // Invalidate the memory cache as it may have changed.
            isMemorySizeCacheValid = false;
        }

        void MemoryMap::DeleteEntry(int index)
        {
            // Starting at the index for which we wish to delete an entry, all we have to do is
            // copy the entry found at i + 1 (the entry directly after what we are deleting) into
            // the i entry (the entry we are deleting). We have to do this for all entries that are
            // above the entry we are deleting.
            for (int i = index; i < entryCount - 1 && i + 1 < MaxEntries; ++i)
                entries[i] = entries[i + 1];

            // Decrement the entryCount by one to indicate we deleted an entry.
            entryCount--;

            // Invalidate the memory cache as it may have changed.
            isMemorySizeCacheValid = false;
        }

        void MemoryMap::AlignAllEntries(uint64_t alignment)
        {
            for (int i = 0; i < entryCount; ++i)
                entries[i].Align(alignment);

            // Invalidate the memory cache as it may have changed.
            isMemorySizeCacheValid = false;
        }

        void MemoryMap::InvalidateMemorySizeCache()
        {
            isMemorySizeCacheValid = false;
        }

        size_t MemoryMap::GetMemorySize()
        {
            if (isMemorySizeCacheValid)
            {
                return memorySizeCache;
            }
            else
            {
                memorySizeCache = 0;

                // Sum up the lengths of all usable entries and cache it.
                for (int i = 0; i < entryCount; ++i)
                {
                    if (entries[i].GetType() == MemoryMapEntryType::Usable)
                        memorySizeCache += entries[i].GetNativeLength();
                }

                // The memory size cache is now valid.
                isMemorySizeCacheValid = true;
                return memorySizeCache;
            }
        }

        const MemoryMapEntry* MemoryMap::GetEntryList() const
        {
            return entries;
        }

        int MemoryMap::GetEntryCount() const
        {
            return entryCount;
        }
    }
}