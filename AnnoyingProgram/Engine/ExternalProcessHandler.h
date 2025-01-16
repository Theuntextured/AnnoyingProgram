#pragma once

#define TH32CS_PROCESS 0x00000002

#include <string>

class ExternalProcessHandler
{
public:
    static bool is_process_running(const std::wstring& process_name);

    static void terminate_process(const std::wstring& process_name);
};
