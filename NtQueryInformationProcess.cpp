#include <iostream>
#include <Windows.h>

typedef long NTSTATUS;
typedef void* PVOID;
typedef void* PPEB;
typedef enum _PROCESSINFOCLASS {
    ProcessBasicInformation = 0
} PROCESSINFOCLASS;

typedef struct _MY_PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    PPEB PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    ULONG_PTR InheritedFromUniqueProcessId;
} MY_PROCESS_BASIC_INFORMATION;

typedef NTSTATUS(NTAPI* NtQueryInformationProcess_t)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);

int main(){

    DWORD pid = GetCurrentProcessId();
    std::cout<<"PID: "<<std::endl;

    HANDLE hproc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (hproc){
        std::cout<<"Opening Process"<<std::endl;
    }
    else {
        std::cout<<"Opening Process Failed"<<std::endl;
    }

    HMODULE hntdll = GetModuleHandleW(L"ntdll.dll");
    NtQueryInformationProcess_t NtQueryInformationProcess = (NtQueryInformationProcess_t)GetProcAddress(hntdll, "NtQueryInformationProcess");

    if(NtQueryInformationProcess){
        std::cout<<"NtQueryInformationProcess in Action"<<std::endl;
    }
    else {
        std::cout<<"NtQueryInformation Failed"<<std::endl;
    }

    MY_PROCESS_BASIC_INFORMATION mpi = {};
    ULONG returnLength = 0;
    
    NTSTATUS status = NtQueryInformationProcess(hproc, ProcessBasicInformation, &mpi, sizeof(mpi), &returnLength);
    if (status == 0){
        std::cout<<"PEB Address: "<< mpi.PebBaseAddress<<std::endl;
        std::cout<<"Parent PID: "<<mpi.InheritedFromUniqueProcessId<<std::endl;
    }
    else {
        std::cout<<"NtQueryInformationProcess Failed"<<std::endl;
    }

    CloseHandle(hproc);

    return 0;
}
