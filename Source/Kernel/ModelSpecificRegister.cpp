#include "ModelSpecificRegister.h"

namespace Kernel
{
    namespace Registers
    {
        uint64_t ModelSpecificRegister::GetValue(uint32_t address)
        {
            return GetModelSpecificRegister(address);
        }

        void ModelSpecificRegister::SetValue(uint32_t address, uint64_t value)
        {
            SetModelSpecificRegister(address, value);
        }
    }
}