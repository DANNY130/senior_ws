#ifndef EXAMPLE_3__VISIBILITY_CONTROL_H_
#define EXAMPLE_3__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
    #ifdef __GNUC__
        #define EXAMPLE_3_EXPORT __attribute__ ((dllexport))
        #define EXAMPLE_3_IMPORT __attribute__ ((dllimport))
    #else
        #define EXAMPLE_3_EXPORT __declspec(dllexport)
        #define EXAMPLE_3_IMPORT __declspec(dllimport)
    #endif
    #ifdef EXAMPLE_3_BUILDING_DLL
        #define EXAMPLE_3_PUBLIC EXAMPLE_3_EXPORT
    #else
        #define EXAMPLE_3_PUBLIC EXAMPLE_3_IMPORT
    #endif
    #define EXAMPLE_3_PUBLIC_TYPE EXAMPLE_3_PUBLIC
    #define EXAMPLE_3_LOCAL
#else
    #define EXAMPLE_3_EXPORT __attribute__ ((visibility("default")))
    #define EXAMPLE_3_IMPORT
    #if __GNUC__ >= 4
        #define EXAMPLE_3_PUBLIC __attribute__ ((visibility("default")))
        #define EXAMPLE_3_LOCAL  __attribute__ ((visibility("hidden")))
    #else
        #define EXAMPLE_3_PUBLIC
        #define EXAMPLE_3_LOCAL
    #endif
    #define EXAMPLE_3_PUBLIC_TYPE
#endif

#endif  // EXAMPLE_3__VISIBILITY_CONTROL_H_