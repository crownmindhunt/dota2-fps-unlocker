#pragma once
#include <string>

struct CvarEntry {
    std::wstring name;
    std::wstring value;
    std::wstring default_value;
    bool is_cheat_protected = false;
    bool is_user_locked = false;
};