#include <vector>    // std::vector
#include <string>    // std::string
#include <iostream>  // std::cout, std::cerr
#include <stdexcept> // std::exception
#include "fmon.h"    // FileMonitor
#include "util.h"    // GetArgs()
#include "sys.h"     // AR

#if OS == OS_UNIX
#  define PROG "fmon"
#else
#  define PROG "fmon.exe"
#endif

void Modified(const char *file) {
    std::cout << '\'' << file << "' was modified\n";
}

int main(int argc, char **argv) {
    if(argc < 2) {
        std::cerr << "Usage: " << PROG << " [-] [FILE]...\n";

        return 1;
    }

    bool useStdin = false;

    std::vector<std::string> args = GetArgs(argc, argv);
    for(const std::string& arg: args) {
        if(arg == "-") useStdin = true;
    }

    FileMonitor fm(Modified);

    if(!useStdin) {
        for(const std::string& arg: args) fm.files.push_back(arg);
    } else {
        std::cout << PROG << ": reading from stdin\n";

        std::string tmp;

        // read filenames from stdin
        while(std::getline(std::cin, tmp)) {
            fm.files.push_back(tmp);
        }
    }

    try {
        fm.Main();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
