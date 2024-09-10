Int64
strToInt64(const char* s, char** endptr, int base)
{
#if defined(_WIN32)
#   ifdef __MINGW32__
    return strToInt64Impl(s, endptr, base);
#   else
    return _strtoi64(s, endptr, base);
#   endif
#elif defined(ICE_64)
    return strtol(s, endptr, base);
#elif defined(__hpux)
    return __strtoll(s, endptr, base);
#else
    return strtoll(s, endptr, base);
#endif
}