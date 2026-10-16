#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "models/frame_state.h"
#include "services/process_attach.h"
#include "services/console_tweak.h"

enum class Preset { Competitive, Streaming, Potato };

class OptimizerCore {
public:
    OptimizerCore();
    ~OptimizerCore();

    bool attach_to_dota();
    void apply_preset(Preset p);
    void restore_defaults();

    FrameState sample_frame();
    bool patch_render_threads(uint32_t threads);

private:
    ProcessAttach attach_;
    ConsoleTweak tweaks_;
    HANDLE dota_handle_ = nullptr;
    uintptr_t base_addr_ = 0;
    Preset last_preset_ = Preset::Competitive;
    std::vector<std::wstring> applied_cvars_;
};