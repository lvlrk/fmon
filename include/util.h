#pragma once

#include <vector> // std::vector
#include <string> // std::string

// returns a `std::vector` from argv
std::vector<std::string> GetArgs(int argc, char **argv);
