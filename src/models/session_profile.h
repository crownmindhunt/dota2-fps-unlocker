#pragma once
#include <string>
#include <vector>
#include "cvar_entry.h"

struct SessionProfile {
    std::wstring name;
    std::wstring hero_hint;
    std::vector<CvarEntry> overrides;
    uint32_t target_fps = 0;
};