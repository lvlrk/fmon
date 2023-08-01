#include "util.h"

std::vector<std::string> GetArgs(int argc, char **argv) {
    std::vector<std::string> args;

    // skip program argument
    for(int i = 1; i < argc; i++) args.push_back(argv[i]);

    return args;
}
