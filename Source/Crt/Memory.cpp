#include "Memory.h"

const void* memchr(const void* source, int value, size_t count)
{
    unsigned char* newSource = (unsigned char*)source;

    while (count-- > 0)
    {
        if (*newSource == (unsigned char)value)
            return source;

        newSource++;
    }

    return 0;
}

void* memchr(void* source, int value, size_t count)
{
    unsigned char* newSource = (unsigned char*)source;

    while (count-- > 0)
    {
        if (*newSource == (unsigned char)value)
            return source;

        newSource++;
    }

    return 0;
}

int memcmp(const void* source1, const void* source2, size_t count)
{
    unsigned char* newSource1 = (unsigned char*)source1;
    unsigned char* newSource2 = (unsigned char*)source2;

    while (count-- > 0 && *newSource1 == *newSource2)
    {
        newSource1++;
        newSource2++;
    }

    return *newSource1 - *newSource2;
}

void* memset(void* destination, int value, size_t count)
{
    unsigned char* newDestination = (unsigned char*)destination;

    while (count-- > 0)
        *newDestination++ = (unsigned char)value;

    return destination;
}

void* memcpy(void* destination, const void* source, size_t count)
{
    unsigned char* newDestination = (unsigned char*)destination;
    unsigned char* newSource = (unsigned char*)source;

    while (count-- > 0)
    {
        *newDestination = *newSource;

        newDestination++;
        newSource++;
    }

    return destination;
}
/*
void* memmove(void* destination, const void* source, size_t count)
{
    unsigned char* newDestination = (unsigned char*)destination;
    unsigned char* newSource = (unsigned char*)source;

    while (count-- > 0)
    {

    }

    return destination;
}
*/