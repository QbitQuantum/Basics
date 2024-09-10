RTDECL(int) RTTimeSet(PCRTTIMESPEC pTime)
{
    FILETIME    FileTime;
    SYSTEMTIME  SysTime;
    if (FileTimeToSystemTime(RTTimeSpecGetNtFileTime(pTime, &FileTime), &SysTime))
    {
        if (SetSystemTime(&SysTime))
            return VINF_SUCCESS;
    }
    return RTErrConvertFromWin32(GetLastError());
}