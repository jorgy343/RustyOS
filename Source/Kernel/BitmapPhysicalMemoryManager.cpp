#include "BitmapPhysicalMemoryManager.h"

namespace Kernel
{
    namespace Memory
    {
        BitmapPhysicalMemoryManager::BitmapPhysicalMemoryManager(size_t blockSize, size_t highestBlock)
            : PhysicalMemoryManager(blockSize, highestBlock)
        {

        }
    }
}