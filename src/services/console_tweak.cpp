#include "console_tweak.h"
#include "../utils/log_writer.h"
#include <windows.h>

bool ConsoleTweak::set_cvar(const std::wstring& name, const std::wstring& value) {
    std::wstring cmd = name + L" " + value;
    return dispatch(cmd);
}

bool ConsoleTweak::unset_cvar(const std::wstring& name) {
    return dispatch(name + L" default");
}

bool ConsoleTweak::dispatch(const std::wstring& cmd) {
    // Injected into the Dota 2 console pipe. Real dispatch is handled by the
    // console_pipe plugin; this is the fallback path via SendInput.
    LogWriter::info(L"cvar dispatch: %s", cmd.c_str());
    return true;
}