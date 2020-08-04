#pragma once
#include "Global.h"

namespace Kernel
{
    namespace Memory
    {
        /// The physical memory manager keeps track of all of the usable physical memory in the
        /// system. This is an abstract class.
        class PhysicalMemoryManager
        {
        private:
            /// The size of a single block of allocatable memory.
            size_t blockSize;

            /// The highest maximum block exclusively allowed to be tracked by this instance. This
            /// field uses zero-based indexing.
            size_t highestBlock;

            /// The amount of usable blocks in the system. This includes both allocated and
            /// unallocated blocks.
            size_t totalBlocks = 0;

            /// The total amount of allocated blocks.
            size_t totalAllocatedBlocks = 0;

        public:
            /// Initializes a new instance of PhysicalMemoryManager.
            /// 
            /// @param[in] blockSize The size of a single block of allocatable memory.
            /// @param[in] totalBlocks The total amount of usable blocks of memory in the system.
            PhysicalMemoryManager(size_t blockSize, size_t highestBlock);

            /// When overridden in a derived class, allocates and returns the address of block of
            /// memory. The block that was returned is marked as used until it is freed.
            /// 
            /// @return Returns the physical address to the start of the newly allocated block.
            virtual PhysicalAddress AllocateBlock() = 0;

            /// When overridden in a derived class, frees a block of memory based on its starting
            /// address. If the starting address is not aligned to the block size then the behavior
            /// of this method is undefined.
            /// 
            /// @param[in] value The address to the start of the block to be freed.
            virtual void FreeBlock(PhysicalAddress value) = 0;

            /// When overridden in a derived class, adds a usable block of memory for this instance
            /// to keep track of. When the block is added, it is considered free for allocation. If
            /// the address to the start of the block is not a multiple of the block size, then the
            /// behavior of this method is undefined.
            /// 
            /// @param[in] value The address to the start of the block to add to this system.
            virtual void AddFreeBlock(PhysicalAddress value) = 0;

            /// Gets the block size this instance is using.
            /// 
            /// @return Returns the block size this instance is using.
            size_t GetBlockSize();

            /// Gets the highest maximum block exclusively allowed to be tracked by this instance.
            /// The return value uses zero-based indexing.
            /// 
            /// @return Returns the highest block exclusively allowed to be tracked by this isntance. The value returned uses zero-based indexing.
            size_t GetHighestBlock();

            /// Gets the total amount of usable blocks this instance is tracking.
            /// 
            /// @return Returns the total amount of usable memoroy this instance is keeping track of.
            size_t GetTotalUsableBlocks();

            /// Gets the total amount of free blocks this instance is tracking.
            /// 
            /// @return Returns the total amount of free blocks this instance is tracking.
            size_t GetTotalFreeBlocks();

            /// Gets the total amount of allocated blocks this instance is tracking.
            /// 
            /// @return Returns the total amount of allocated blocks this isntance is keeping track of.
            size_t GetTotalAllocatedBlocks();

            /// Gets the total amount of memory this instance is tracking.
            /// 
            /// @return Returns the total amount of memory this instance is tracking.
            size_t GetTotalMemory();

            /// Gets the total amount of free memory this instance is tracking.
            /// 
            /// @return Returns the total amount of free memory this instance is tracking.
            size_t GetTotalFreeMemory();

            /// Gets the tottal amount of allocated memory this instance is tracking.
            /// 
            /// @return Returns the total amount of allocated memory this instance is tracking.
            size_t GetTotalAllocatedMemory();
        };
    }
}