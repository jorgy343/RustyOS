OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH("i386")
ENTRY(KernelEntryPoint)

SECTIONS
{
    . = 0xC0000000;
    
    .text ALIGN(4096) :
    {
        *(.text*)
    }
    
    .rodata ALIGN(4096) :
    {
        ConstructorsStart = .;
        *(.ctor*)
        ConstructosEnd = .;

        DestructorsStart = .;
        *(.dtor*)
        DestructosEnd = .;

        *(.rodata*)
    }
    
    .data ALIGN(4096) :
    {
        *(.data*)
    }
    
    .bss ALIGN(4096) :
    {
        *(.bss*)
    }

    /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
    }

    EndOfImage = .;
}