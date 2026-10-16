#pragma once
#include <string>
#include <vector>
#include "../models/frame_state.h"

class TelemetryClient {
public:
    void push(const FrameState& fs);
    std::vector<FrameState> recent() const { return buffer_; }
    double average_fps() const;

private:
    std::vector<FrameState> buffer_;
};