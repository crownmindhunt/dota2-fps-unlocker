#pragma once
#include <string>
#include <unordered_map>
#include "optimizer_core.h"

class ConfigLoader {
public:
    static ConfigLoader& instance();

    bool load(const std::wstring& path);
    Preset preset() const { return preset_; }
    const std::unordered_map<std::wstring, std::wstring>& raw() const { return kv_; }

private:
    ConfigLoader() = default;
    std::unordered_map<std::wstring, std::wstring> kv_;
    Preset preset_ = Preset::Competitive;
};