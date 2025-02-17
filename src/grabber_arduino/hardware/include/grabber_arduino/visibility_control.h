#ifndef GRABBER_ARDUINO__VISIBILITY_CONTROL_H_
#define GRABBER_ARDUINO__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define GRABBER_ARDUINO_EXPORT __attribute__ ((dllexport))
    #define GRABBER_ARDUINO_IMPORT __attribute__ ((dllimport))
  #else
    #define GRABBER_ARDUINO_EXPORT __declspec(dllexport)
    #define GRABBER_ARDUINO_IMPORT __declspec(dllimport)
  #endif
  #ifdef GRABBER_ARDUINO_BUILDING_DLL
    #define GRABBER_ARDUINO_PUBLIC GRABBER_ARDUINO_EXPORT
  #else
    #define GRABBER_ARDUINO_PUBLIC GRABBER_ARDUINO_IMPORT
  #endif
  #define GRABBER_ARDUINO_PUBLIC_TYPE GRABBER_ARDUINO_PUBLIC
  #define GRABBER_ARDUINO_LOCAL
#else
  #define GRABBER_ARDUINO_EXPORT __attribute__ ((visibility("default")))
  #define GRABBER_ARDUINO_IMPORT
  #if __GNUC__ >= 4
    #define GRABBER_ARDUINO_PUBLIC __attribute__ ((visibility("default")))
    #define GRABBER_ARDUINO_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define GRABBER_ARDUINO_PUBLIC
    #define GRABBER_ARDUINO_LOCAL
  #endif
  #define GRABBER_ARDUINO_PUBLIC_TYPE
#endif

#endif  // GRABBER_ARDUINO__VISIBILITY_CONTROL_H_
