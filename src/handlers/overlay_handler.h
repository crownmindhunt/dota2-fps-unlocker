#pragma once
#include <windows.h>
#include "../models/frame_state.h"

class OverlayHandler {
public:
    bool install(HWND target);
    void update(const FrameState& fs);
    void toggle();
    void uninstall();

private:
    HWND overlay_wnd_ = nullptr;
    bool visible_ = true;
    FrameState last_{};
};