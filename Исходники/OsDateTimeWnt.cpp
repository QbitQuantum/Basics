// Return the current time as an OsTime value
void OsDateTimeWnt::getCurTime(OsTime& rTime)
{
#if WINCE
    typedef union 
    {
        FILETIME  ft;
        uint64_t  int64;
    } g_FILETIME;

    uint64_t ticks ;
    uint64_t freq ;
    static bool       sbInitialized = false ;
    static g_FILETIME sOsFileTime ;
    static uint64_t sLastTicks = 0 ;
    static uint64_t sResetTime = 0 ;

    QueryPerformanceCounter((LARGE_INTEGER*) &ticks) ;
    QueryPerformanceFrequency((LARGE_INTEGER*) &freq) ;

    if (!sbInitialized || sOsFileTime.int64 > sResetTime)
    {
        sbInitialized = true ;
        GetSystemTimeAsFileTime(&sOsFileTime.ft);
        sResetTime = -1 ; // sOsFileTime.int64 + (freq - 1) ;
        sLastTicks = ticks ;
    }
    else
    {
        uint64_t delta = ticks - sLastTicks ;

        sLastTicks = ticks ;
        sOsFileTime.int64 = sOsFileTime.int64 + 
                (((uint64_t) 10000000) * (delta / freq)) + 
                (((uint64_t) 10000000) * (delta % freq)) / freq ;    
        
        SYSTEMTIME si ;
        FileTimeToSystemTime(&sOsFileTime.ft, &si) ;
    }

   OsTime curTime((long)  ((sOsFileTime.int64 - ((uint64_t) 116444736000000000)) / ((uint64_t) 10000000)), 
                  (long) ((sOsFileTime.int64 / ((uint64_t) 10)) % ((uint64_t) 1000000)));
   rTime = curTime;
#else
    typedef union 
    {
        FILETIME   ft;
        uint64_t   int64;
    } g_FILETIME;

    static bool       sbInitialized = false ;
    static g_FILETIME sOsFileTime ;
    static DWORD sLastSystemMSecs = 0 ;

    DWORD systemMSecs = timeGetTime();

    if (!sbInitialized)
    {
        sbInitialized = true ;

        // Set the precision of timings got from timeGetTime.
        timeBeginPeriod(1);
        // Resample time, since we changed the precision.
        systemMSecs = timeGetTime();

        FILETIME sft;
        GetSystemTimeAsFileTime(&sft);
        // Store in a temp and copy over to prevent data type misalignment issues.
        sOsFileTime.ft = sft;
        sLastSystemMSecs = systemMSecs ;
    }
    else
    {
        DWORD delta = systemMSecs - sLastSystemMSecs ;

        sLastSystemMSecs = systemMSecs;
        sOsFileTime.int64 = sOsFileTime.int64 + 
                            10000 * delta;  // convert delta msec to 100ns units
        
        SYSTEMTIME si ;
        FileTimeToSystemTime(&sOsFileTime.ft, &si) ;
    }

   OsTime curTime((long) ((sOsFileTime.int64 - 
                           ((uint64_t) WINDOWSTIME2UNIXTIME * 10000000)) 
                          / ((uint64_t) 10000000)), 
                  (long) ((sOsFileTime.int64 / ((uint64_t) 10)) % 
                          ((uint64_t) 1000000)));
   rTime = curTime;
#endif
}