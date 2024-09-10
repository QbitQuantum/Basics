BOOL
StartIOManager(void)
{
    HANDLE hExit;
    WorkQueue* wq;
    UINT sleepResolution;
    TIMECAPS timecaps;
    MMRESULT mmresult;

    mmresult = timeGetDevCaps(&timecaps, sizeof(timecaps));
    if (mmresult != MMSYSERR_NOERROR) {
        return false;
    }
    sleepResolution = timecaps.wPeriodMin;
    mmresult = timeBeginPeriod(sleepResolution);
    if (mmresult != MMSYSERR_NOERROR) {
        return false;
    }

    wq = NewWorkQueue();
    if ( !wq ) return false;

    ioMan = (IOManagerState*)malloc(sizeof(IOManagerState));

    if (!ioMan) {
        FreeWorkQueue(wq);
        return false;
    }

    /* A manual-reset event */
    hExit = CreateEvent ( NULL, true, false, NULL );
    if ( !hExit ) {
        FreeWorkQueue(wq);
        free(ioMan);
        return false;
    }

    ioMan->hExitEvent = hExit;
    InitializeCriticalSection(&ioMan->manLock);
    ioMan->workQueue   = wq;
    ioMan->numWorkers  = 0;
    ioMan->workersIdle = 0;
    ioMan->queueSize   = 0;
    ioMan->requestID   = 1;
    InitializeCriticalSection(&ioMan->active_work_lock);
    ioMan->active_work_items = NULL;
    ioMan->sleepResolution = sleepResolution;

    return true;
}