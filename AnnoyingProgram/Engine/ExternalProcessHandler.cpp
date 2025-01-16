#include "ExternalProcessHandler.h"
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

bool ExternalProcessHandler::is_process_running(const std::wstring& process_name)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_PROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            //std::wcout << L"Found process: " << pe32.szExeFile << std::endl; // Debug output
            if (process_name == pe32.szExeFile) {
                CloseHandle(hProcessSnap);
                return true;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
    return false;
}

void ExternalProcessHandler::terminate_process(const std::wstring& process_name)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_PROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (process_name == pe32.szExeFile) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if (hProcess != NULL) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                    std::wcout << L"Terminated " << process_name << std::endl;
                }
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
}
