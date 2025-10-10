#include <iostream>
#include <Windows.h>

int main(){

    int OG_VALUE = 1920;
    std::cout<<"The Original Value is: "<<OG_VALUE<<std::endl;

    DWORD pid = GetCurrentProcessId();
    std::cout<<"Process PID: "<<pid<<std::endl;

    HANDLE hproc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if(hproc){
        std::cout<<"Opening Process"<<std::endl;
    }
    else{
        std::cout<<"Opening Process Failed"<<std::endl;
    }

    int read = 0;
    SIZE_T byteread = 0;
    
    if(ReadProcessMemory(hproc, &OG_VALUE, &read, sizeof(read), &byteread)){
        std::cout<<"ReadProcessMemory: " << read << " (" << byteread << " bytes) " <<std::endl;
    }
    else {
        std::cout<<"ReadProcessMemory Failed"<<std::endl;
    }

    int NEW_VALUE = 2033;
    SIZE_T byteswritten = 0;

    if(WriteProcessMemory(hproc, &OG_VALUE, &NEW_VALUE, sizeof(NEW_VALUE), &byteswritten)){
        std::cout<<"WriteProcessMemory Wrote: "<<byteswritten<<" bytes" <<std::endl;
        std::cout<<"New Value: "<<OG_VALUE<<std::endl;
    }
    else {
        std::cout<<"Failed to Write"<<std::endl;
    }

    CloseHandle(hproc);
    return 0;
}
