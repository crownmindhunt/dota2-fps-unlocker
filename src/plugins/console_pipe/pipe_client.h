#pragma once
#include <windows.h>
#include <string>

class PipeClient {
public:
    bool connect();
    bool send(const std::wstring& cmd);
    void disconnect();

private:
    HANDLE pipe_ = INVALID_HANDLE_VALUE;
};