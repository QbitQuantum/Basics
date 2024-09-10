//-----------------------------------------------------------------------------
// 取得執行緒執行時間
bool GetRunTime(IN unsigned long ulThreadID, OUT __int64 &i64KernelTime, OUT __int64 &i64UserTime)
{
    C_WHandle ccThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, ulThreadID);

    if(ccThread == nullptr)
        return C_NOutput::Instance().Error(ERRORNSTD, __T("thread null"));

    FILETIME tCreateTime, tExitTime, tKernelTime, tUserTime;

    if(GetThreadTimes(static_cast<HANDLE>(ccThread), &tCreateTime, &tExitTime, &tKernelTime, &tUserTime) == FALSE)
        return C_NOutput::Instance().Error(ERRORNSTD, C_ErrorWin(), __T("get thread runtime failed"));

    i64KernelTime = (Int64ShllMod32(tKernelTime.dwHighDateTime, 32) | tKernelTime.dwLowDateTime);
    i64UserTime = (Int64ShllMod32(tUserTime.dwHighDateTime, 32) | tUserTime.dwLowDateTime);

    return true;
}