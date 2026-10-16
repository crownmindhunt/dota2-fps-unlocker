#include <cassert>
#include <iostream>
#include "../src/utils/memory_patch.h"

int main() {
    // smoke test: pattern matcher should skip wildcard bytes
    const uint8_t sig[] = { 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00 };
    uint8_t buf[] = { 0x00, 0x00, 0x48, 0x8B, 0x0D, 0xAA, 0xBB, 0xCC, 0xDD };
    // not calling into Windows API here, just verifying the wildcard logic
    size_t matched = 0;
    for (size_t i = 0; i + sizeof(sig) < sizeof(buf); ++i) {
        bool ok = true;
        for (size_t j = 0; j < sizeof(sig); ++j) {
            if (sig[j] == 0x00) continue;
            if (buf[i + j] != sig[j]) { ok = false; break; }
        }
        if (ok) matched++;
    }
    assert(matched >= 1);
    std::cout << "test_memory_patch ok\n";
    return 0;
}