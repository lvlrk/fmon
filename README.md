# fmon-1.0
A tool to monitor whether file(s) were modified

Note: currently, this program is only available on `linux`

# Files
`build.sh`: Builds the `fmon` program
`clean.sh`: Cleans up the built files (`fmon`, `*.o`, `*.so`)
`install.sh`: Installs the `fmon` library (run as root)
`LICENSE`: `fmon`'s GPL3 license
`src`: `fmon` source code
`uninstall.sh`: Removes the `fmon` library (run as root)

# Program usage
Run
`$ fmon -`
to monitor filenames from stdin.

Otherwise, run
`$ fmon file1 file2 file3 ...`
to monitor file1 file2 and file3, etc.

# API usage
Just add `include/fmon.h` and `src/fmon.cpp` to your project source,
or run
`# ./install.sh`
to install the `fmon` library

Run
`# ./uninstall.sh`
to uninstall the `fmon` library

Example code:
```cpp
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
```
# lvlrk 2023
