ULONGLONG CpuUsage::getSystemNonIdleTimes()
{
    FILETIME ftSysIdle, ftSysKernel, ftSysUser;

    if (!GetSystemTimes(&ftSysIdle, &ftSysKernel, &ftSysUser))
    {
        errorMsg(TEXT("GetSystemTimes"));
        return 0;
    }

    return addTimes(ftSysKernel, ftSysUser);
}