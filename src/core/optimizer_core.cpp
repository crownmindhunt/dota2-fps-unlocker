#include "optimizer_core.h"
#include "utils/log_writer.h"
#include "utils/memory_patch.h"

OptimizerCore::OptimizerCore() = default;

OptimizerCore::~OptimizerCore() {
    if (dota_handle_) CloseHandle(dota_handle_);
}

bool OptimizerCore::attach_to_dota() {
    dota_handle_ = attach_.by_name(L"dota2.exe");
    if (!dota_handle_) return false;
    base_addr_ = attach_.module_base(L"client.dll");
    LogWriter::info(L"attached to dota2.exe, client.dll base = 0x%p", (void*)base_addr_);
    return base_addr_ != 0;
}

void OptimizerCore::apply_preset(Preset p) {
    last_preset_ = p;
    switch (p) {
        case Preset::Competitive:
            tweaks_.set_cvar(L"fps_max", L"0");
            tweaks_.set_cvar(L"r_threaded_particles", L"1");
            tweaks_.set_cvar(L"net_graph", L"1");
            patch_render_threads(8);
            break;
        case Preset::Streaming:
            tweaks_.set_cvar(L"fps_max", L"144");
            tweaks_.set_cvar(L"r_dynamic_portraits", L"0");
            break;
        case Preset::Potato:
            tweaks_.set_cvar(L"fps_max", L"60");
            tweaks_.set_cvar(L"r_lod", L"2");
            tweaks_.set_cvar(L"r_debug_overlay", L"0");
            break;
    }
    LogWriter::info(L"preset applied");
}

void OptimizerCore::restore_defaults() {
    for (auto& c : applied_cvars_) {
        tweaks_.unset_cvar(c);
    }
    applied_cvars_.clear();
}

bool OptimizerCore::patch_render_threads(uint32_t threads) {
    // candidate byte pattern for thread count in client.dll (2026 schema)
    const uint8_t sig[] = { 0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x89, 0x41, 0x58 };
    auto addr = MemoryPatch::find_pattern(dota_handle_, base_addr_, sig, sizeof(sig));
    if (!addr) {
        LogWriter::warn(L"render thread signature not found — schema drift?");
        return false;
    }
    return MemoryPatch::write_u32(dota_handle_, addr + 0x58, threads);
}