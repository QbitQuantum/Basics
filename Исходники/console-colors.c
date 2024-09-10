static int Write(FILE *stream, const char *format, va_list ap) {
#if defined(_WIN32) && !defined(__MINGW32__)
    return vfprintf_s(stream, format, ap);
#else
    return vfprintf(stream, format, ap);
#endif
}