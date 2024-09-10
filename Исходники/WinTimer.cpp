void
setupTimer(Renderer* renderer)
{	
    runningRenderer = renderer;
    if (renderer) {
        CreateTimerQueueTimer(&timerQueueTimer, NULL, statusTimer, 
            NULL, 250, 250, WT_EXECUTEINTIMERTHREAD);
    } else {
        if (timerQueueTimer) {
            DeleteTimerQueueTimer(NULL, timerQueueTimer, INVALID_HANDLE_VALUE);
        }
    }
}