#pragma once
#include "Global.h"
#include "Bits.h"

namespace Kernel
{
    namespace Registers
    {
        class ModelSpecificRegister
        {
        public:
            ModelSpecificRegister() = delete;
            ModelSpecificRegister(const ModelSpecificRegister &) = delete;
            ModelSpecificRegister &operator=(const ModelSpecificRegister &) = delete;

            static uint64_t GetValue(uint32_t address);
            static void SetValue(uint32_t address, uint64_t value);
        };

        extern "C" uint64_t GetModelSpecificRegister(uint32_t address);
        extern "C" void SetModelSpecificRegister(uint32_t address, uint64_t value);
    }
}