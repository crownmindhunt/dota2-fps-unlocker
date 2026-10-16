#include "hotkey_handler.h"

bool HotkeyHandler::register_key(int vk, Callback cb) {
    callbacks_[vk] = std::move(cb);
    pressed_[vk] = false;
    return true;
}

void HotkeyHandler::pump() {
    for (auto& [vk, cb] : callbacks_) {
        bool down = (GetAsyncKeyState(vk) & 0x8000) != 0;
        if (down && !pressed_[vk]) cb();
        pressed_[vk] = down;
    }
}