#pragma once
#include <cstdint>

struct FrameState {
    double fps = 0.0;
    double frametime_ms = 0.0;
    uint32_t draw_calls = 0;
    uint32_t render_threads = 0;
    uint64_t timestamp_us = 0;
};