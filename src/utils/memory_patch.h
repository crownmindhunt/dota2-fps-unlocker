#pragma once
#include <windows.h>
#include <cstdint>

class MemoryPatch {
public:
    static uintptr_t find_pattern(HANDLE proc, uintptr_t base, const uint8_t* sig, size_t len);
    static bool write_u32(HANDLE proc, uintptr_t addr, uint32_t value);
    static bool write_bytes(HANDLE proc, uintptr_t addr, const uint8_t* data, size_t len);
};