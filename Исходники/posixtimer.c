void win_timer_init(void)
{
        timerId = timeSetEvent(TIME_INTERVAL,10,timerCb,0,TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
        TimeEvent = CreateEvent(NULL,FALSE,FALSE,NULL);

        late_ticks = 0;

        offset_time = GetTickCount();
        posix_timer_time=0;
}