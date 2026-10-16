#include <windows.h>
#include <iostream>
#include <string>
#include "core/optimizer_core.h"
#include "core/config_loader.h"
#include "utils/log_writer.h"

int wmain(int argc, wchar_t** argv) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleW(L"dota2-fps-unlocker :: 2026 build");

    LogWriter::init(L"logs/fps_unlocker.log");

    if (!ConfigLoader::instance().load(L"config/default.toml")) {
        LogWriter::warn(L"config/default.toml missing, using built-in defaults");
    }

    OptimizerCore core;
    if (!core.attach_to_dota()) {
        LogWriter::error(L"unable to locate dota2.exe — launch the game first");
        std::wcerr << L"[!] dota2.exe not found. Start Dota 2 and retry.\n";
        return 1;
    }

    core.apply_preset(ConfigLoader::instance().preset());
    LogWriter::info(L"optimizer running — press F8 to toggle overlay, F9 to restore");

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    core.restore_defaults();
    return 0;
}