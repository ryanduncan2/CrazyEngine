#ifndef CRAZYENGINE_DEFINES_H_
#define CRAZYENGINE_DEFINES_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64 bit Windows is required."
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define PLATFORM_LINUX 1
    #if defined(__ANDROID__)
    #define PLATFORM_ANDROID 1
    #endif
#elif defined(__unix__)
    #define PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
    #define PLATFORM_POSIX 1
#elif __APPLE__
    #define PLATFORM_APPLE_1
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        #define PLATFORM_IOS 1
        #define PLATFORM_IOS_SIMULATOR 1
    #elif TARGET_OS_IPHONE
        #define PLATFORM_IOS 1
    #elif TARGET_OS_MAC
    #else
        #error "Unknown Apple platform detected."
    #endif
#else
    #error "Unknown platform detected."
#endif

#endif