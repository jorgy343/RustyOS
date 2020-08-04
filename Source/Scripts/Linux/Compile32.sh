#!/bin/sh

# Remove old temp files.
rm -r \
    ../../IntermediateOutput/*.s \
    ../../IntermediateOutput/*.o \
    ../../IntermediateOutput/*.bin \
    ../../IntermediateOutput/*.elf \
    ../../IntermediateOutput/Disassembly/*.s \
    ../../IntermediateOutput/Disassembly/*.o \
    ../../IntermediateOutput/Disassembly/*.bin \
    ../../IntermediateOutput/Disassembly/*.elf \
    2> /dev/null



# Build the boot sector and all assembly files for the crt, kernel, etc.
nasm -Ox "../../BootSector/BootSector.asm" -f bin -o "../../IntermediateOutput/BootSector.bin"
nasm -Ox "../../Kernel/Assembly/KernelEntryPoint.asm" -f elf -o "../../IntermediateOutput/KernelEntryPoint.o"
nasm -Ox "../../Kernel/Assembly/InstallGdt.asm" -f elf -o "../../IntermediateOutput/InstallGdt.o"
nasm -Ox "../../Kernel/Assembly/InstallLdt.asm" -f elf -o "../../IntermediateOutput/InstallLdt.o"
nasm -Ox "../../Kernel/Assembly/InstallIdt.asm" -f elf -o "../../IntermediateOutput/InstallIdt.o"
nasm -Ox "../../Kernel/Assembly/Ports.asm" -f elf -o "../../IntermediateOutput/Ports.o"
nasm -Ox "../../Kernel/Assembly/Registers32.asm" -f elf -o "../../IntermediateOutput/Registers32.o"

cd ../../IntermediateOutput/Disassembly

# Generate the assembly output of all of the source files.
gcc \
    -S -masm=intel -m32 -std=c++0x -Wall \
    -nostdlib -nostartfiles -nodefaultlibs -fno-builtin \
    -fuse-cxa-atexit -fno-use-cxa-get-exception-ptr \
    -fno-exceptions -fno-rtti -fno-stack-protector -fno-threadsafe-statics \
    -O3 -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow \
    ../../Crt/*.cpp ../../Kernel/*.cpp \
    2> /dev/null

cd ../../IntermediateOutput

# Build the crt and kernel.
gcc \
    -c -m32 -std=c++0x -Wall -x c++ \
    -nostdlib -nostartfiles -nodefaultlibs -fno-builtin \
    -fuse-cxa-atexit -fno-use-cxa-get-exception-ptr \
    -fno-exceptions -fno-rtti -fno-stack-protector -fno-threadsafe-statics \
    -O3 -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow \
    ../Crt/*.cpp ../Kernel/*.cpp

gcc \
    -c -m32 -Wall \
    -nostdlib -nostartfiles -nodefaultlibs -fno-builtin \
    -fno-exceptions -fno-stack-protector \
    -O3 -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow \
    ../Intrinsics/*.c

# Link the crt, kernel, and misc. assembly files together to create Kernel.elf.
ld -static -nostdlib -nostartfiles -nodefaultlibs -o Kernel.elf -T ../Scripts/Common/LinkerScript.ld *.o

# Split the boot sector into Stage1 and Stage2. Stage2 goes into the file system.
head -c 512 BootSector.bin > Stage1.bin
tail -c +513 BootSector.bin > FileSystemRoot/Stage2.bin

# Copy the kernel into the file system.
cp Kernel.elf FileSystemRoot/

# Create the file system and then copy the disk image to the Output folder.
mono ../../Tools/Common/Misc/ImageCreator.exe -rootdirectory FileSystemRoot -image DiskImage.bin -bootsector Stage1.bin -sectorcount 2880 -clustersizeinbytes 512
cp DiskImage.bin ../Output/
