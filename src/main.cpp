#include <vector> // std::vector
#include <string> // std::string
#include <iostream> // std::cout, std::cerr
#include <stdexcept> // std::exception
#include "fmon.h" // FileMonitor
#include "util.h" // GetArgs() [USE_THREAD_LIMIT, THREADC]

void Modified(const char *file) {
    std::cout << '\'' << file << "' was modified\n";
}

int main(int argc, char **argv) {
    // usage screen
    if(argc < 2) {
        std::cerr << "Usage: fmon [-] [FILE]...\n";
// for debugging only
#ifdef USE_THREAD_LIMIT
        std::cerr << "note: only <thread count> files can be monitored\n";
#endif

        return 1;
    }

// for debugging only
#ifdef USE_THREAD_LIMIT
    if(argc > THREADC + 1) {
        std::cerr << "fmon error: argument count exceeds thread count (" << THREADC << ")\n";

        return 1;
    }
#endif
    bool useStdin = false;

    std::vector<std::string> args = GetArgs(argc, argv);
    for(const std::string& arg: args) {
        if(arg == "-") useStdin = true;
    }

    FileMonitor fm(Modified);

    if(!useStdin) {
        for(const std::string& arg: args) fm.files.push_back(arg);
    } else {
        std::cout << "fmon: reading from stdin\n";

        std::string tmp;

        // read filenames from stdin
        while(std::getline(std::cin, tmp)) {
            fm.files.push_back(tmp);
        }
    }

    try {
        fm.Main();
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}
