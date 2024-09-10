void getLocalTime(const time_t* localTime, struct tm* localTM)
{
#if PLATFORM(QT)
#if USE(MULTIPLE_THREADS)
#error Mulitple threads are currently not supported in the Qt/mingw build
#endif
    *localTM = *localtime(localTime);
#elif PLATFORM(WIN_OS)
    #if COMPILER(MSVC7)
    *localTM = *localtime(localTime);
    #else
    localtime_s(localTM, localTime);
    #endif
#else
    localtime_r(localTime, localTM);
#endif
}