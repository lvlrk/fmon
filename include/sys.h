#pragma once

#include <string> // std::string

// OS 'enum'
#define OS_WINDOWS 0
#define OS_UNIX 1

// Architecture 'enum'
#define AR_i686 0   // 32-bit
#define AR_x86_64 1 // 64-bit

// awesome preprocessor jumble :thumbsup:
#if _WIN32 || _WIN64
# define OS OS_WINDOWS
# if _WIN64
#  define AR AR_x86_64
# elif __i686__
#  define AR AR_i686
# endif
#else
# define OS OS_UNIX
# if __x86_64__
#  define AR AR_x86_64
# elif __i686__
#  define AR AR_i686
# endif
#endif

std::string GetOs(); // returns {os}
std::string GetArchitecture(); // returns {architecture}
std::string GetSystem(); // returns {os} ({architecture})
