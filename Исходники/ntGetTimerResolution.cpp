int main()
{
    ULONG Min = ~0;
    ULONG Max = ~0;
    ULONG Cur = ~0;
    NtQueryTimerResolution(&Max, &Min, &Cur);
    printf("NtQueryTimerResolution -> Max=%08luns Min=%08luns Cur=%08luns\n", Min * 100, Max * 100, Cur * 100);

#if 0
    /* figure out the 100ns relative to the 1970 epoc. */
    SYSTEMTIME st;
    st.wYear = 1970;
    st.wMonth = 1;
    st.wDayOfWeek = 4; /* Thor's day. */
    st.wDay = 1;
    st.wHour = 0;
    st.wMinute = 0;
    st.wSecond = 0;
    st.wMilliseconds = 0;

    FILETIME ft;
    if (SystemTimeToFileTime(&st, &ft))
    {
        printf("epoc is %I64u (0x%08x%08x)\n", ft, ft.dwHighDateTime, ft.dwLowDateTime);
        if (FileTimeToSystemTime(&ft, &st))
            printf("unix epoc: %d-%02d-%02d %02d:%02d:%02d.%03d (week day %d)\n",
                st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, st.wDayOfWeek);
        else
            printf("FileTimeToSystemTime failed, lasterr=%d\n", GetLastError());
    }
    else
        printf("SystemTimeToFileTime failed, lasterr=%d\n", GetLastError());

    ft.dwHighDateTime = 0;
    ft.dwLowDateTime = 0;
    if (FileTimeToSystemTime(&ft, &st))
        printf("nt time start: %d-%02d-%02d %02d:%02d:%02d.%03d (week day %d)\n",
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, st.wDayOfWeek);
    else
        printf("FileTimeToSystemTime failed, lasterr=%d\n", GetLastError());
#endif
    return 0;
}