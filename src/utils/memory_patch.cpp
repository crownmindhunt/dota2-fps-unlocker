#include "memory_patch.h"
#include <vector>
#include "log_writer.h"

uintptr_t MemoryPatch::find_pattern(HANDLE proc, uintptr_t base, const uint8_t* sig, size_t len) {
    constexpr size_t kScan = 0x800000;
    std::vector<uint8_t> buf(kScan);
    SIZE_T read = 0;
    if (!ReadProcessMemory(proc, (LPCVOID)base, buf.data(), kScan, &read)) {
        LogWriter::warn(L"RPM scan failed");
        return 0;
    }
    for (size_t i = 0; i + len < read; ++i) {
        bool ok = true;
        for (size_t j = 0; j < len; ++j) {
            if (sig[j] == 0x00) continue; // wildcard
            if (buf[i + j] != sig[j]) { ok = false; break; }
        }
        if (ok) return base + i;
    }
    return 0;
}

bool MemoryPatch::write_u32(HANDLE proc, uintptr_t addr, uint32_t value) {
    SIZE_T written = 0;
    return WriteProcessMemory(proc, (LPVOID)addr, &value, sizeof(value), &written);
}

bool MemoryPatch::write_bytes(HANDLE proc, uintptr_t addr, const uint8_t* data, size_t len) {
    SIZE_T written = 0;
    return WriteProcessMemory(proc, (LPVOID)addr, data, len, &written);
}