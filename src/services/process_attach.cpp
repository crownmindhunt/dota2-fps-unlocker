#include "process_attach.h"
#include <tlhelp32.h>
#include "../utils/log_writer.h"

HANDLE ProcessAttach::by_name(const std::wstring& exe) {
    snap_ = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap_ == INVALID_HANDLE_VALUE) return nullptr;

    PROCESSENTRY32W pe{ sizeof(pe) };
    HANDLE h = nullptr;
    if (Process32FirstW(snap_, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, exe.c_str()) == 0) {
                pid_ = pe.th32ProcessID;
                h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
                break;
            }
        } while (Process32NextW(snap_, &pe));
    }
    return h;
}

uintptr_t ProcessAttach::module_base(const std::wstring& module) {
    if (!pid_) return 0;
    HANDLE s = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid_);
    if (s == INVALID_HANDLE_VALUE) return 0;

    MODULEENTRY32W me{ sizeof(me) };
    uintptr_t base = 0;
    if (Module32FirstW(s, &me)) {
        do {
            if (_wcsicmp(me.szModule, module.c_str()) == 0) {
                base = reinterpret_cast<uintptr_t>(me.modBaseAddr);
                break;
            }
        } while (Module32NextW(s, &me));
    }
    CloseHandle(s);
    return base;
}