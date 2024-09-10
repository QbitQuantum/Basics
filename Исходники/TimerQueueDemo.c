int _tmain(int argc, _TCHAR **argv)
{
    HANDLE hTimerQueue = CreateTimerQueue();
    HANDLE hTimer = NULL;

    DWORD dwDueTimeInMs = 5000;
    DWORD dwPeriod = 1000;

    if (NULL == hTimerQueue)
    {
        _tperror(_T("Failed to create timer queue."));
        return GetLastError();
    }

    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
        TimerRoutine, (PVOID)GetTickCount(), dwDueTimeInMs, dwPeriod,
        WT_EXECUTEDEFAULT))
    {
        _tperror(_T("Failed to create timer."));
        return GetLastError();
    }

    _tprintf(_T("Call timer routine in %lu seconds...\n"),
        (unsigned long)dwDueTimeInMs / 1000);

    _tprintf(_T("Hit any key to delete the timer queue and cancel all queued timers!\n"));

    while (!_kbhit()) {
    }
    _getch();

    if (!DeleteTimerQueueEx(hTimerQueue, INVALID_HANDLE_VALUE))
    {
        _tprintf(_T("Failed to delete timer queue.\n"));
        return GetLastError();
    }

    _tprintf(_T("Now I think it is time to say goodbye.\n"));

    return 0;
}