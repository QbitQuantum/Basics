static void CALLBACK TimerCallback(
    __inout     PTP_CALLBACK_INSTANCE instance,
    __inout_opt PVOID                 context,
    __inout     PTP_TIMER             timer
    )
{
    MI_Result result = MI_RESULT_FAILED;
    Perf_Indication_Self* self;
    Perf_Indication indicationInstance = {{0}};

    if(!context)
    {
        return;
    }

    self = (Perf_Indication_Self*)context;

    result = Perf_Indication_Construct(&indicationInstance, self->indicationContext);
    if(result != MI_RESULT_OK)
        return;

    result = FillInstance(self->indicationContext, &indicationInstance.__instance, self->keyCounter++);
    if(result != MI_RESULT_OK)
        return;

    Perf_Indication_Post(&indicationInstance, self->indicationContext, 0, 0);
    Perf_Indication_Destruct(&indicationInstance);

    if(self->shutdownCalled != MI_TRUE)
    {    
        // Clean up the previous timer. Do not do a WaitForThreadpoolTimerCallbacks as this will hang.
        // Instead directly call CloseThreadPoolTimer. This asynchronously closes the timer when outstanding calls are done.
        // As the timer settings are for 1 event only, there will be no outstanding calls, but only the current call.
        SetThreadpoolTimer(self->indicationTimer, NULL, 0, 0);
        CloseThreadpoolTimer(self->indicationTimer);

        FILETIME now;
        ZeroMemory(&now, sizeof(FILETIME));

        self->indicationTimer = CreateThreadpoolTimer(TimerCallback, self, NULL);
        SetThreadpoolTimer(self->indicationTimer, &now, 0, 1);
    }
}