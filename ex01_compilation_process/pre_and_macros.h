// Guard against multiple inclusions
#ifndef PRE_AND_MACROS_H
#define PRE_AND_MACROS_H

// Define constants
#define VAR_1 10
#define VAR_2 20

// Function macros
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Some complex macro logic
#if defined(PLATFORM_WINDOWS)
    #define OS_STRING "Windows"
#elif defined(PLATFORM_LINUX)
    #define OS_STRING "Linux"
#else
    #define OS_STRING "Unknown OS"
#endif

#endif // PRE_AND_MACROS_H
