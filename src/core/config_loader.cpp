#include "config_loader.h"
#include <fstream>
#include <sstream>
#include "utils/log_writer.h"

ConfigLoader& ConfigLoader::instance() {
    static ConfigLoader c;
    return c;
}

bool ConfigLoader::load(const std::wstring& path) {
    std::wifstream in(path);
    if (!in.is_open()) return false;

    std::wstring line;
    while (std::getline(in, line)) {
        auto eq = line.find(L'=');
        if (eq == std::wstring::npos || line[0] == L'#') continue;
        std::wstring key = line.substr(0, eq);
        std::wstring val = line.substr(eq + 1);
        kv_[key] = val;
    }

    auto it = kv_.find(L"preset");
    if (it != kv_.end()) {
        if (it->second == L"streaming") preset_ = Preset::Streaming;
        else if (it->second == L"potato") preset_ = Preset::Potato;
    }
    LogWriter::info(L"config loaded (%zu keys)", kv_.size());
    return true;
}