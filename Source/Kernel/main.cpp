#include "main.h"

extern size_t EndOfImage;

Console console;

GdtRegister gdtRegister;
uint64_t gdtDescriptorTable[3];

MemoryMap memoryMap;

int main()
{
    // Setup the GDT.
    gdtDescriptorTable[0] = 0;
    gdtDescriptorTable[1] = Descriptor::CreateCodeSegment32(0xFFFFF, 0x0, RingLevel::Kernel, Granularity::FourKilobyte, AccessLevel::ExecuteOnly, DefaultOperationSize::Protected32Bit, Conformance::Conforming);
    gdtDescriptorTable[2] = Descriptor::CreateDataSegment32(0xFFFFF, 0x0, RingLevel::Kernel, Granularity::FourKilobyte, AccessLevel::ReadAndWrite, DefaultOperationSize::Protected32Bit, GrowthDirection::GrowsUp);

    gdtRegister = GdtRegister();
    gdtRegister.SetSize(sizeof(uint64_t) * 3 - 1);
    gdtRegister.SetAddress(gdtDescriptorTable);
    gdtRegister.Install();

    // Setup the memory map.
    int memoryMapEntryCount = *((int*)0x600);

    for (int i = 0; i < memoryMapEntryCount; ++i)
        memoryMap.AddEntry((MemoryMapEntry*)(0x608 + i * sizeof(MemoryMapEntry)));

    memoryMap.AlignAllEntries(4096);

    // Setup the physical memory manager.


    // Test some miscellaneous stuff.
    console.Clear();
    console.PrintFormatted("End of Image = %p\nAnd 5 = %d\n\n", &EndOfImage, 0);

    bool testBool = Convert::ToBool("True");
    console.PrintFormatted("gdgfdgdg %hhd %% %d %p  %hhi sdffsd\n\n", (long long)8089063202527182853, (int)testBool, &memoryMap, Convert::ToSignedChar("-17", 10));

    for (int i = 0; i < memoryMap.GetEntryCount(); ++i)
        console.PrintFormatted("Start: %llX  Length: %llX\n", memoryMap.GetEntryList()[i].GetBaseAddress(), memoryMap.GetEntryList()[i].GetLength());

    return 1;
}