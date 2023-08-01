#include "sys.h"

std::string GetOs() {
    if(OS == OS_WINDOWS) return "Windows";
    else if(OS == OS_UNIX) return "Unix";
    else return "(undefined)";
}

std::string GetArchitecture() {
    if(AR == AR_i686) return "i686 32-bit";
    else if(AR == AR_x86_64) return "x86_64 64-bit";
    else return "(undefined)";
}

std::string GetSystem() {
    return GetOs() + " (" + GetArchitecture() + ')';
}
