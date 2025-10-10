#include <iostream>
#include <Windows.h>

int main(){
    if (IsDebuggerPresent()){
        std::cout<<"[+] Debugger Detected!"<<std::endl;
        return 1;
    }
    else {
        std::cout<<"[-] No Debugger Detected!"<<std::endl;
    }
    return 0;
}
