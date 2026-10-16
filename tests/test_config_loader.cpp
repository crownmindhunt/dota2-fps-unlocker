#include <cassert>
#include <iostream>
#include <fstream>
#include "../src/core/config_loader.h"

int main() {
    std::wofstream f(L"test_cfg.toml");
    f << L"preset = streaming\n";
    f << L"render_threads = 6\n";
    f.close();

    auto& cfg = ConfigLoader::instance();
    assert(cfg.load(L"test_cfg.toml"));
    assert(cfg.preset() == Preset::Streaming);
    assert(cfg.raw().at(L"render_threads") == L"6");

    std::cout << "test_config_loader ok\n";
    return 0;
}