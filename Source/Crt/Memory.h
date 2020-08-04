#pragma once
#include <cstdint>
#include <cstddef>

const void* memchr(const void* source, int value, size_t count);
void* memchr(void* source, int value, size_t count);
int memcmp(const void* source1, const void* source2, size_t count);
void* memset(void* destination, int value, size_t count);
void* memcpy(void* destination, const void* source, size_t count);
void* memmove(void* destination, const void* source, size_t count);