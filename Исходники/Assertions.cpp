static void vprintf_stderr_common(const char* format, va_list args)
{
#if USE(CF) && !OS(WINDOWS)
    if (strstr(format, "%@")) {
        CFStringRef cfFormat = CFStringCreateWithCString(NULL, format, kCFStringEncodingUTF8);

#if COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
        CFStringRef str = CFStringCreateWithFormatAndArguments(NULL, NULL, cfFormat, args);
#if COMPILER(CLANG)
#pragma clang diagnostic pop
#endif
        CFIndex length = CFStringGetMaximumSizeForEncoding(CFStringGetLength(str), kCFStringEncodingUTF8);
        char* buffer = (char*)malloc(length + 1);

        CFStringGetCString(str, buffer, length, kCFStringEncodingUTF8);

#if USE(APPLE_SYSTEM_LOG)
        asl_log(0, 0, ASL_LEVEL_NOTICE, "%s", buffer);
#endif
        fputs(buffer, stderr);

        free(buffer);
        CFRelease(str);
        CFRelease(cfFormat);
        return;
    }

#if USE(APPLE_SYSTEM_LOG)
    va_list copyOfArgs;
    va_copy(copyOfArgs, args);
    asl_vlog(0, 0, ASL_LEVEL_NOTICE, format, copyOfArgs);
    va_end(copyOfArgs);
#endif

    // Fall through to write to stderr in the same manner as other platforms.

#elif HAVE(ISDEBUGGERPRESENT)
    if (IsDebuggerPresent()) {
        size_t size = 1024;

        do {
            char* buffer = (char*)malloc(size);

            if (buffer == NULL)
                break;

            if (vsnprintf(buffer, size, format, args) != -1) {
                OutputDebugStringA(buffer);
                free(buffer);
                break;
            }

            free(buffer);
            size *= 2;
        } while (size > 1024);
    }
#endif
    vfprintf(stderr, format, args);
}