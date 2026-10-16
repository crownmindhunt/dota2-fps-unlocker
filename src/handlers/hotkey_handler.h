#pragma once
#include <windows.h>
#include <functional>
#include <unordered_map>

class HotkeyHandler {
public:
    using Callback = std::function<void()>;

    bool register_key(int vk, Callback cb);
    void pump();

private:
    std::unordered_map<int, Callback> callbacks_;
    std::unordered_map<int, bool> pressed_;
};