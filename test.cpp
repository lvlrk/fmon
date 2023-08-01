#include <iostream> // std::cout
#include <stdexcept> // std::exception
#include <fmon.h> // FileMonitor

void foo(const char *file) {
    // do stuff with `file`

    // example:
    std::cout << '\'' << file << "' was modified\n";
}

int main() {
    FileMonitor fm(foo);

    fm.files.push_back("file1");
    fm.files.push_back("file2");
    fm.files.push_back("file3");
    // ... for however many files

    try {
        fm.Main();
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
