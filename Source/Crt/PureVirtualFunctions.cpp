// Although it is very difficult to get the compiler to generate these functions, there are rare
// cases in which it can happen. This functions must be defined in order for the linker to not
// complain about missing symbols.

extern "C" void __cxa_pure_virtual()
{
    // Hang the system.
    for (;;);
}