# fmon-1.2
A quick, easy, and multi-threaded<br>
method to poll file modification.

## Supported systems
```
               +-----------+-----------+
               |           |           |
               |  x86_64   |   i686    |
               | (64-bit)  | (32-bit)  |
               |           |           |
+--------------+-----------+-----------+
|              |           |           |
|     Unix     |    Yes    |    Yes    |
|              |           |           |
+--------------+-----------+-----------+
|              |           |           |
|    Windows   |     No    |    No     |
|              | (Not yet) | (Not yet) |
|              |           |           |
+--------------+-----------+-----------+
```



# Patch notes
* v1.0:   initial version<br>
* v1.1: - remove debug conditions<br>
* v1.2: - add i686 support<br>
        + small bug fixes



## Project structure
`include/`: `fmon` headers<br>
`src/`: `fmon` source code<br>
`LICENSE`: `fmon`'s GPL3 license<br>
`Makefile`: `fmon`'s very awesome and/or cool build file<br>
`compile_flags.txt`: config for `clangd`



# Program usage
Run `$ fmon -` to monitor filenames from stdin.<br>
Otherwise, run `$ fmon [FILE]...` to monitor FILEs.

##### Note for 32-bit building
To use the 32-bit version of the program/library,<br>
append 32 to the makefile target, or the actual `fmon` command.

Example:<br>
`$ make install32` To install the 32-bit `fmon32` program.<br>
`# make lib-install32` To install the 32-bit `fmon` library.<br>

`$ fmon32` To run fmon in 32-bit mode.



## Installation
Run `# make clean install` to install `fmon`.

## Uninstallation
Run `# make uninstall` to uninstall `fmon`.



# Library usage
Add `include/fmon.h` and `src/fmon.cpp` to your project source.<br>

##### Note:
If you are compiling with the 32-bit version,<br>
make sure to use the flag `-lfmon32` instead of `-lfmon`.

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
