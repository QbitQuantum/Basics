DLL_EXPORT
BOOL FishHang_PulseEvent
(
    const char*  pszFilePosted,   // source file that signalled it
    const int    nLinePosted,     // line number of source file

    HANDLE  hEvent          // handle to event object
)
{
    FISH_THREAD*  pFISH_THREAD;
    FISH_EVENT*   pFISH_EVENT;

    FIXFILENAME(pszFilePosted);

    LockFishHang();

    if (!GetThreadAndEventPtrs(&pFISH_THREAD,&pFISH_EVENT,hEvent))
        FishHangAbort(pszFilePosted,nLinePosted);

    GetSystemTime(&pFISH_EVENT->timeSet);
    GetSystemTime(&pFISH_EVENT->timeReset);

    pFISH_EVENT->pWhoSet      = pFISH_THREAD;
    pFISH_EVENT->pWhoReset    = pFISH_THREAD;
    pFISH_EVENT->pszFileSet   = pszFilePosted;
    pFISH_EVENT->pszFileReset = pszFilePosted;
    pFISH_EVENT->nLineSet     = nLinePosted;
    pFISH_EVENT->nLineReset   = nLinePosted;

    UnlockFishHang();

    return PulseEvent(hEvent);
}