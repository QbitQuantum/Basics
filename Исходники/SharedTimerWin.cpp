void stopSharedTimer()
{
#if !OS(WINCE)
    if (timerQueue && timer) {
        DeleteTimerQueueTimer(timerQueue, timer, 0);
        timer = 0;
    }
#endif

    if (timerID) {
        KillTimer(timerWindowHandle, timerID);
        timerID = 0;
    }
}