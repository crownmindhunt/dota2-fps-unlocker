#pragma once
#include <windows.h>
#include <string>

class ProcessAttach {
public:
    HANDLE by_name(const std::wstring& exe);
    uintptr_t module_base(const std::wstring& module);
    DWORD pid() const { return pid_; }

private:
    DWORD pid_ = 0;
    HANDLE snap_ = nullptr;
};