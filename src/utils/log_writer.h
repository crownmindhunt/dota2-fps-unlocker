#pragma once
#include <string>
#include <cstdarg>

class LogWriter {
public:
    static void init(const std::wstring& path);
    static void info(const wchar_t* fmt, ...);
    static void warn(const wchar_t* fmt, ...);
    static void error(const wchar_t* fmt, ...);

private:
    static void write(const wchar_t* level, const wchar_t* fmt, va_list args);
};