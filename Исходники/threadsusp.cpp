/*++
Function:

  ResumeThread

See MSDN doc.
--*/
DWORD
PALAPI
ResumeThread(
         IN HANDLE hThread
         )
{
    PAL_ERROR palError;
    CPalThread *pthrResumer;
    DWORD dwSuspendCount = (DWORD)-1;

    PERF_ENTRY(ResumeThread);
    ENTRY("ResumeThread(hThread=%p)\n", hThread);

    pthrResumer = InternalGetCurrentThread();
    palError = InternalResumeThread(
        pthrResumer,
        hThread,
        &dwSuspendCount
        );

    if (NO_ERROR != palError)
    {
        pthrResumer->SetLastError(palError);
        dwSuspendCount = (DWORD) -1;
    }
    else
    {
        _ASSERT_MSG(dwSuspendCount != static_cast<DWORD>(-1), "InternalResumeThread returned success but dwSuspendCount did not change.\n");   
    }

    LOGEXIT("ResumeThread returns DWORD %u\n", dwSuspendCount);
    PERF_EXIT(ResumeThread);
    return dwSuspendCount;
}