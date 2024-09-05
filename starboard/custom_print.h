#ifndef STARBOARD_CUSTOM_PRINT_H_
#define STARBOARD_CUSTOM_PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(FORCE_DEFAULT_VISIBILITY)
#define MY_EXPORT __attribute__((visibility("default")))
#else
#define MY_EXPORT
#endif

void MY_EXPORT SbCustomPrint(const char* str);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
