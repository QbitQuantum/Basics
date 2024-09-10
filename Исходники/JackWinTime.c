SERVER_EXPORT void InitTime()
{
	QueryPerformanceFrequency(&_jack_freq);
    TIMECAPS caps;
    if (timeGetDevCaps(&caps, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
        jack_error("InitTime : could not get timer device");
    } else {
        gPeriod = caps.wPeriodMin;
        if (timeBeginPeriod(gPeriod) != TIMERR_NOERROR) {
            jack_error("InitTime : could not set minimum timer");
            gPeriod = 0;
        } else {
            jack_info("InitTime : multimedia timer resolution set to %d milliseconds", gPeriod);
       }
    }
}