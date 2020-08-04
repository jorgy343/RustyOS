#pragma once
#include "Global.h"
#include "PhysicalMemoryManager.h"

namespace Kernel
{
    namespace Memory
    {
        class BitmapPhysicalMemoryManager : public PhysicalMemoryManager
        {
        private:


        public:
            BitmapPhysicalMemoryManager(size_t blockSize, size_t highestBlock);
        };
    }
}