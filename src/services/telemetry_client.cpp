#include "telemetry_client.h"
#include <numeric>

void TelemetryClient::push(const FrameState& fs) {
    buffer_.push_back(fs);
    if (buffer_.size() > 512) buffer_.erase(buffer_.begin());
}

double TelemetryClient::average_fps() const {
    if (buffer_.empty()) return 0.0;
    double sum = 0.0;
    for (auto& f : buffer_) sum += f.fps;
    return sum / buffer_.size();
}