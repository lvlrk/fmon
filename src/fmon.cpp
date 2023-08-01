#include <stdexcept> // std::runtime_error
#include <chrono> // std::chrono::seconds()
#include <sys/stat.h> // struct stat, stat() (windows: struct _stat -> stat, _stat() - > stat())
#include "fmon.h"

#if _WIN32 || _WIN64
#define stat _stat
#else
#include <sys/stat.h> // struct stat, stat()
#endif

FileMonitor::FileMonitor(void (*func)(const char*)):
func{func} {}

FileMonitor::~FileMonitor() {
    // uses `closedThreads` so we don't
    // accidentally 'close' the threads twice!
    if(!closedThreads) CloseThreads();
}

void FileMonitor::Main() {
    // we use classic for loops instead of ranged for loops because
    // `FileMonitor::MonitorFile` takes in the index of the filename
    // instead of a `std::string`
    for(int i = 0; i < files.size(); i++) {
        // weird `std::thread` constructor
        // because member functions aren't static
        threads.push_back(std::thread(&FileMonitor::MonitorFile, this, i));
    }
}

void FileMonitor::MonitorFile(int index) {
    if(index > files.size() - 1)
        throw std::runtime_error("MonitorFile(): bad index");
    if(files[index] == "") return;

    struct stat st;
    int mtime, pMtime;

    if(stat(files[index].c_str(), &st) == -1)
        throw std::runtime_error("MonitorFile(): bad initial stat '" +
                                 files[index] + '\'');
    mtime = st.st_mtime;

    while(shouldPoll) {
        pMtime = mtime;

        std::this_thread::sleep_for(pollDelay);

        if(stat(files[index].c_str(), &st) == -1)
            throw std::runtime_error("MonitorFile(): bad stat '" +
                                     files[index] + '\'');
        mtime = st.st_mtime;

        if(pMtime != mtime) {
            func(files[index].c_str());

            // set `pMtime` to `mtime` so `func` isnt called twice!
            pMtime = mtime;
        }
    }
}

void FileMonitor::CloseThreads() {
    for(std::thread& thread: threads) thread.join();
}
