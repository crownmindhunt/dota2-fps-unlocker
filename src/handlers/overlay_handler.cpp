#include "overlay_handler.h"
#include "../utils/log_writer.h"

bool OverlayHandler::install(HWND target) {
    overlay_wnd_ = target;
    LogWriter::info(L"overlay handler installed on hwnd=0x%p", (void*)target);
    return overlay_wnd_ != nullptr;
}

void OverlayHandler::update(const FrameState& fs) {
    if (!visible_) return;
    last_ = fs;
    // draw path is delegated to the DirectComposition hook in plugins/overlay_render
}

void OverlayHandler::toggle() {
    visible_ = !visible_;
    LogWriter::info(L"overlay toggled %s", visible_ ? L"ON" : L"OFF");
}

void OverlayHandler::uninstall() {
    overlay_wnd_ = nullptr;
}