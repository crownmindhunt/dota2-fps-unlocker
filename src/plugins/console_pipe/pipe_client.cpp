#include "pipe_client.h"
#include "../../utils/log_writer.h"

bool PipeClient::connect() {
    pipe_ = CreateFileW(L"\\\\.\\pipe\\dota2_console", GENERIC_WRITE, 0,
                        nullptr, OPEN_EXISTING, 0, nullptr);
    return pipe_ != INVALID_HANDLE_VALUE;
}

bool PipeClient::send(const std::wstring& cmd) {
    if (pipe_ == INVALID_HANDLE_VALUE) return false;
    DWORD written = 0;
    return WriteFile(pipe_, cmd.c_str(), (DWORD)(cmd.size() * sizeof(wchar_t)), &written, nullptr);
}

void PipeClient::disconnect() {
    if (pipe_ != INVALID_HANDLE_VALUE) CloseHandle(pipe_);
    pipe_ = INVALID_HANDLE_VALUE;
}