#include <iostream>
#include <Windows.h>

int main(){

    SIZE_T size = 1024;
    
    LPVOID mem = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if(mem){
        std::cout<<"Memory Allocation Successful!"<<std::endl;
        std::cout<<"Memory Allocated at: "<<mem<<std::endl;

        VirtualFree(mem, 0, MEM_RELEASE);
    }
    else {
        std::cout<<"Memory Allocation Failed"<<std::endl;
    }
    return 0;
}
