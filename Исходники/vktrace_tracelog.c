void LogGuts(VktraceLogLevel level, const char* fmt, va_list args) {
#if defined(WIN32)
    int requiredLength = _vscprintf(fmt, args) + 1;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_OSX)
    int requiredLength;
    va_list argcopy;
    va_copy(argcopy, args);
    requiredLength = vsnprintf(NULL, 0, fmt, argcopy) + 1;
    va_end(argcopy);
#endif
    static VKTRACE_THREAD_LOCAL BOOL logging = FALSE;

    // Don't recursively log problems found during logging
    if (logging) {
        return;
    }
    logging = TRUE;

    char* message = (char*)vktrace_malloc(requiredLength);
#if defined(WIN32)
    _vsnprintf_s(message, requiredLength, requiredLength - 1, fmt, args);
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_OSX)
    vsnprintf(message, requiredLength, fmt, args);
#endif

    if (s_reportFunc != NULL) {
        s_reportFunc(level, message);
    } else {
#ifdef ANDROID
#include <android/log.h>
        __android_log_print(ANDROID_LOG_INFO, "vktrace", "%s: %s\n", vktrace_LogLevelToString(level), message);
#else
        printf("%s: %s\n", vktrace_LogLevelToString(level), message);
#endif
    }

    vktrace_free(message);
    logging = FALSE;
}