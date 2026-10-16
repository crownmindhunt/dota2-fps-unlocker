#include "log_writer.h"
#include <windows.h>
#include <cstdio>

static FILE* g_log = nullptr;

void LogWriter::init(const std::wstring& path) {
    _wfopen_s(&g_log, path.c_str(), L"a, ccs=UTF-8");
}

void LogWriter::info(const wchar_t* fmt, ...) {
    va_list a; va_start(a, fmt); write(L"INFO", fmt, a); va_end(a);
}
void LogWriter::warn(const wchar_t* fmt, ...) {
    va_list a; va_start(a, fmt); write(L"WARN", fmt, a); va_end(a);
}
void LogWriter::error(const wchar_t* fmt, ...) {
    va_list a; va_start(a, fmt); write(L"ERR ", fmt, a); va_end(a);
}

void LogWriter::write(const wchar_t* level, const wchar_t* fmt, va_list args) {
    if (!g_log) return;
    SYSTEMTIME st; GetLocalTime(&st);
    fwprintf(g_log, L"[%02d:%02d:%02d] [%ls] ", st.wHour, st.wMinute, st.wSecond, level);
    vfwprintf(g_log, fmt, args);
    fwprintf(g_log, L"\n");
    fflush(g_log);
}