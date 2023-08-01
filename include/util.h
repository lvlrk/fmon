#pragma once

#include <vector> // std::vector
#include <string> // std::string

// for debugging only
// #define USE_THREAD_LIMIT
#ifdef THREAD_LIMIT
#define THREADC 12 // how many threads my cpu can safely access by default
#endif

// returns a `std::vector` from argv
std::vector<std::string> GetArgs(int argc, char **argv);
