#pragma once

#include <vector> // std::vector
#include <string> // std::string
#include <thread> // std::thread

class FileMonitor {
public:
    // `func()` is the function to be called
    // when a file is modified
    FileMonitor(void (*func)(const char *));

    // cleans up threads.
    // luckily when a terminate signal is encountered,
    // the destructor is called by default
    ~FileMonitor();

    // creates the threads for polling files with `stat()`
    void Main();

    // polls with `stat()` for file modifications and
    // calls `func()` when modified
    void MonitorFile(int index);

    std::vector<std::string> files;

    // used by `MonitorFile()`
    bool shouldPoll = true;
private:
    // threading-related
    void CloseThreads(); // joins all threads together
    std::vector<std::thread> threads;
    bool closedThreads = false; // is set to true by `CloseThreads`

    // the function thats called when a file is modified
    void (*func)(const char*);
};
