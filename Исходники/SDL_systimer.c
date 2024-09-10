static void
SDL_SetSystemTimerResolution(const UINT uPeriod)
{
#ifndef __WINRT__
    static UINT timer_period = 0;

    if (uPeriod != timer_period) {
        if (timer_period) {
            timeEndPeriod(timer_period);
        }

        timer_period = uPeriod;

        if (timer_period) {
            timeBeginPeriod(timer_period);
        }
    }
#endif
}