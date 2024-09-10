void flext::Sleep(double s)
{
    if(s <= 0) return;
#if FLEXT_OS == FLEXT_OS_WIN
#if defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x400
#if 0
    LARGE_INTEGER liDueTime;
    liDueTime.QuadPart = (LONGLONG)(-1.e7*s);

    // Create a waitable timer.
    HANDLE hTimer = CreateWaitableTimer(NULL,TRUE,NULL);
    if(hTimer) {
        if(SetWaitableTimer(hTimer,&liDueTime,0,NULL,NULL,0))
            // Wait for the timer.
            WaitForSingleObject(hTimer,INFINITE); // != WAIT_OBJECT_0)
        else
            ::Sleep((long)(s*1000.));
        CloseHandle(hTimer);
    }
    else
#else
    LARGE_INTEGER cnt;
    if(perffrq && QueryPerformanceCounter(&cnt)) {
        LONGLONG dst = (LONGLONG)(cnt.QuadPart+perffrq*s);
        for(;;) {
            SwitchToThread(); // while waiting switch to another thread
            QueryPerformanceCounter(&cnt);
            if(cnt.QuadPart > dst) break;
        }
    }
    else
#endif
#endif
        // last resort....
        ::Sleep((long)(s*1000.));
#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH // POSIX
    usleep((long)(s*1000000.));
#elif FLEXT_OS == FLEXT_OS_MAC // that's just for OS9 & Carbon!
    UnsignedWide tick;
    Microseconds(&tick);
    double target = tick.hi*((double)(1L<<((sizeof tick.lo)*4))*(double)(1L<<((sizeof tick.lo)*4)))+tick.lo+s*1.e6; 
    for(;;) {
        // this is just a loop running until the time has passed - stone age (but we yield at least)
        Microseconds(&tick);
        if(target <= tick.hi*((double)(1L<<((sizeof tick.lo)*4))*(double)(1L<<((sizeof tick.lo)*4)))+tick.lo) break;
        YieldToAnyThread(); // yielding surely reduces the timing precision (but we're civilized)
    }
#else
    #error Not implemented
#endif
}