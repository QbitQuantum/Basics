int uSetCurProcessWorkingSetSize(usize_t MinWorkingSetSize, usize_t MaxWorkingSetSize, sys_call_error_fun fun)
{
#ifdef _WIN32
    BOOL res = SetProcessWorkingSetSize(
                  GetCurrentProcess(), // handle to the process
                  MinWorkingSetSize,   // minimum working set size
                  MaxWorkingSetSize    // maximum working set size
               );
    if (res == 0)
    {
        sys_call_error("SetProcessWorkingSetSize");
        return 1;
    }
    return 0;
#else
    return 0;
#endif
}