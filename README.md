# fmon-1.3
A quick, easy, and multi-threaded<br>
method to poll file modification.

## Supported systems
Unix: Yes
Windows: Yes



# Patch notes
## v1.0: initial version<br>
## v1.1: removed debug conditions<br>
## v1.2: added i686 support, + small bug fixes
## v1.3: removed 1686 support, added windows support



## Project structure
`include/`: `fmon` headers<br>
`src/`: `fmon` source code<br>
`LICENSE`: `fmon`'s GPL3 license<br>
`Makefile`: `fmon`'s very awesome and/or cool build file<br>
`compile_flags.txt`: config for `clangd`



# Program usage
Run `$ fmon -` to monitor filenames from stdin.<br>
Otherwise, run `$ fmon [FILE]...` to monitor FILEs.

#### Make notes
`fmon` is now cross-platform.<br>
When running `make`, append `-e "PLATFORM=[unix|windows]"`<br>
for the platform of your choice.

## Installation
Run `# make clean install` to install `fmon`.

## Uninstallation
Run `# make uninstall` to uninstall `fmon`.



# Library usage
Add `include/fmon.h` and `src/fmon.cpp` to your project source.<br>

## Library Installation
Or run `# make clean lib-install` to install the `fmon` library.

## Library Uninstallation
Run `# make lib-uninstall` to uninstall the `fmon` library.

##### Note:
Make sure to the `-lfmon` compiler flag.

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
