# fmon-1.1
A tool to monitor whether file(s) were modified

## Note:
currently, this program is only available on `linux`

# Files
`build.sh`: Builds the `fmon` program<br>
`clean.sh`: Cleans up the built files (`fmon`, `*.o`, `*.so`)<br>
`install.sh`: Installs the `fmon` library (run as root)<br>
`LICENSE`: `fmon`'s GPL3 license<br>
`src`: `fmon` source code<br>
`uninstall.sh`: Removes the `fmon` library (run as root)

# Program usage
Run<br>
`$ fmon -`<br>
to monitor filenames from stdin.

Otherwise, run<br>
`$ fmon file1 file2 file3 ...`<br>
to monitor file1 file2 and file3, etc.

# API usage
Just add `include/fmon.h` and `src/fmon.cpp` to your project source,<br>
or run<br>
`# ./install.sh`<br>
to install the `fmon` library

Run<br>
`# ./uninstall.sh`<br>
to uninstall the `fmon` library

Example code:
```cpp
#include <iostream> // std::cout
#include <stdexcept> // std::exception
#include <string> // std::string
#include <fmon.h> // FileMonitor

void foo(const char *file) {
    // do stuff with `file`

    // example:
    std::cout << '\'' << file << "' was modified\n";
}

int main() {
    FileMonitor fm(foo);

    std::string file = ""; // your filename here

    // for however many files
    fm.files.push_back(file);

    try {
        fm.Main();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
```

### lvlrk 2023
