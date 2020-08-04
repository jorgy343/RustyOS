#include "PhysicalMemoryManager.h"

namespace Kernel
{
    namespace Memory
    {
        PhysicalMemoryManager::PhysicalMemoryManager(size_t blockSize, size_t highestBlock)
            : blockSize(blockSize), highestBlock(highestBlock)
        {
            
        }

        size_t PhysicalMemoryManager::GetBlockSize()
        {
            return blockSize;
        }

        size_t PhysicalMemoryManager::GetHighestBlock()
        {
            return highestBlock;
        }

        size_t PhysicalMemoryManager::GetTotalUsableBlocks()
        {
            return totalBlocks;
        }

        size_t PhysicalMemoryManager::GetTotalFreeBlocks()
        {
            return totalBlocks - totalAllocatedBlocks;
        }

        size_t PhysicalMemoryManager::GetTotalAllocatedBlocks()
        {
            return totalAllocatedBlocks;
        }

        size_t PhysicalMemoryManager::GetTotalMemory()
        {
            return totalBlocks * blockSize;
        }

        size_t PhysicalMemoryManager::GetTotalFreeMemory()
        {
            return (totalBlocks - totalAllocatedBlocks) * blockSize;
        }

        size_t PhysicalMemoryManager::GetTotalAllocatedMemory()
        {
            return totalAllocatedBlocks * blockSize;
        }
    }
}