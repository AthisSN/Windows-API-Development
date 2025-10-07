#include <iostream>
#include <Windows.h>

int main(){
    STARTUPINFOW si = { 0 };
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = { 0 };

    LPCWSTR application = L"C:\\Windows\\system32\\notepad.exe";

    BOOL result = CreateProcessW(application, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if (result){
        std::cout<<"Process Created!"<<std::endl;
        std::cout<<"PID of notepad.exe: "<<pi.dwProcessId<<std::endl;
    }
    else {
        std::cout<<"Failed to create process.."<<std::endl;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
