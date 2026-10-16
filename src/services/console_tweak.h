#pragma once
#include <string>

class ConsoleTweak {
public:
    bool set_cvar(const std::wstring& name, const std::wstring& value);
    bool unset_cvar(const std::wstring& name);

private:
    bool dispatch(const std::wstring& cmd);
};